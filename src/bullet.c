/*----------------------------------------------------------------------
 *
 * Desc: all Bullet AND Blast - related functions.
 *	 
 *
 *----------------------------------------------------------------------*/

/* 
 *
 *   Copyright (c) 1994, 2002 Johannes Prix
 *   Copyright (c) 1994, 2002 Reinhard Prix
 *
 *
 *  This file is part of Freedroid
 *
 *  Freedroid is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Freedroid is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Freedroid; see the file COPYING. If not, write to the 
 *  Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
 *  MA  02111-1307  USA
 *
 */
#define _bullet_c

#include "system.h"

#include "defs.h"
#include "struct.h"
#include "global.h"
#include "proto.h"

/* Distances for hitting a druid */
#define MORE		4
#define DRUIDHITDIST2		(DRUIDRADIUSX+MORE)*(DRUIDRADIUSY+MORE)


/*@Function============================================================
@Desc: this function moves all the bullets according to their speeds.

NEW: this function also takes into accoung the current framerate.

@Ret: keiner

@Int: keiner
* $Function----------------------------------------------------------*/

void
MoveBullets (void)
{

  /* lokale Variablen der Funktion: */
  int i;
  Bullet CurBullet;

  /* Bewegung der Bullets */
  for (CurBullet = AllBullets, i = 0; i < MAXBULLETS; CurBullet++, i++)
    {
      if (CurBullet->type == OUT)
	continue;

      CurBullet->pos.x += CurBullet->speed.x * Frame_Time ();
      CurBullet->pos.y += CurBullet->speed.y * Frame_Time ();

      CurBullet->time_in_frames++;
      CurBullet->time_in_seconds += Frame_Time();

      /*
         UM ZU VERHINDERN, DASS DIE BULLETS, DIE ETWAS TREFFEN, NICHT MEHR
         DARGESTELLT WERDEN, PASSIERT DIE BULLETKOLLISIONSABFRAGE ERST NACH
         DER ZUSAMMENSTELLUNG DES INTERNFENSTERS. jp, 23.5.94 */

      /* Kollisionen mit Mauern und Druids checken UND behandeln */
      //          CheckBulletCollisions(i);

    }				/* for */
}				// void MoveBullets(void)


/*@Function============================================================
@Desc: Diese Funktion loescht das Bullet mit der uebergebenen Nummer

@Ret: 
@Int:
* $Function----------------------------------------------------------*/
void
DeleteBullet (int Bulletnummer)
{
  Bullet CurBullet = &AllBullets[Bulletnummer];

  /* Das Bullet loeschen */
  CurBullet->type = OUT;
  CurBullet->time_in_seconds = 0;
  CurBullet->time_in_frames = 0;
  CurBullet->mine = FALSE;

  /* Blast erzeugen: type BULLETBLAST */
  StartBlast (CurBullet->pos.x, CurBullet->pos.y, BULLETBLAST);
}

/*@Function============================================================
@Desc: StartBlast(): erzeugt einen Blast type an x/y

@Ret: void
@Int:
* $Function----------------------------------------------------------*/
void
StartBlast (int x, int y, int type)
{
  int i;
  Blast NewBlast;

  /* Position des naechsten freien Blasts herausfinden */
  for (i = 0; i < MAXBLASTS; i++)
    if (AllBlasts[i].type == OUT)
      break;

  /* keinen gefunden: nimm den ersten */
  if (i == MAXBLASTS)
    i = 0;

  /* Get Pointer to it: more comfortable */
  NewBlast = &(AllBlasts[i]);

  /* Einen Blast an x/y erzeugen */
  NewBlast->PX = x;
  NewBlast->PY = y;

  NewBlast->type = type;
  NewBlast->phase = 0;


  if (type == DRUIDBLAST)
    {
      DruidBlastSound ();
    }

}				/* StartBlast */

/*@Function============================================================
@Desc: Diese Funktion zaehlt die Phasen aller Explosionen weiter
@Ret: keiner
@Int: keiner
* $Function----------------------------------------------------------*/
void
ExplodeBlasts (void)
{
  int i;
  Blast CurBlast = AllBlasts;

  for (i = 0; i < MAXBLASTS; i++, CurBlast++)
    if (CurBlast->type != OUT)
      {

	/* Druidblasts sind gefaehrlich !! */
	if (CurBlast->type == DRUIDBLAST)
	  CheckBlastCollisions (i);

	// CurBlast->phase++;
	CurBlast->phase += Frame_Time () * BLASTPHASES_PER_SECOND;
	if (((int) rintf (CurBlast->phase)) >=
	    Blastmap[CurBlast->type].phases)
	  DeleteBlast (i);
      }				/* if */
}				/* ExplodeBlasts */

/*@Function============================================================
@Desc: Einen eizelnen Blast ausloeschen

@Ret: keiner
@Int:
* $Function----------------------------------------------------------*/
void
DeleteBlast (int Blastnummer)
{
  AllBlasts[Blastnummer].type = OUT;
}

/*@Function============================================================
@Desc: 

@Ret: 
@Int:
* $Function----------------------------------------------------------*/
int
GetDirection (point robo, point bul)
{

  if ((robo.x < bul.x) && (robo.y > bul.y))
    return 0;
  if ((robo.x < bul.x) && (robo.y < bul.y))
    return 1;
  if ((robo.x > bul.x) && (robo.y < bul.y))
    return 2;
  if ((robo.x > bul.x) && (robo.y > bul.y))
    return 3;
  if ((robo.x == bul.x) && (robo.y == bul.y))
    {
      DebugPrintf (" Center hit directy!");
      getchar ();
    }
  return 0;
}

/*@Function============================================================
@Desc: CheckBulletCollisions(int num)
			checkt Collisions des Bullets Num mit Hintergrund && Druids

@Ret: void
@Int:
* $Function----------------------------------------------------------*/
void
CheckBulletCollisions (int num)
{
  int i;
  int level = CurLevel->levelnum;
  long xdist, ydist;
  Bullet CurBullet = &AllBullets[num];
  static int FBTZaehler = 0;

  switch (CurBullet->type)
    {
      // Never do any collision checking if the bullet is OUT already...
    case OUT:
      return;
      break;
      
      // Next we handle the case that the bullet is of type FLASH
    case FLASH:
      // if the flash is over, just delete it and return
      if ( CurBullet->time_in_frames > FLASH_DURATION_IN_FRAMES )
	{
	  CurBullet->time_in_frames = 0;
	  CurBullet->time_in_seconds = 0;
	  CurBullet->type = OUT;
	  CurBullet->mine = FALSE;
	  return;
	}
      
      // if the flash is not yet over, do some checking for who gets
      // hurt by it.  
      // Two different methode for doing this are available:
      // The first but less elegant Method is just to check for
      // flash immunity, for distance and visiblity.
      // The second and more elegant method is to recursively fill
      // out the room where the flash-maker is in and to hurt all
      // robots in there except of course for those immune.
      
      for (i = 0; i < MAX_ENEMYS_ON_SHIP; i++)
	{
	  if ( IsVisible (&Feindesliste[i].pos) &
	       (!Druidmap[Feindesliste[i].type].flashimmune) )
	    {
	      Feindesliste[i].energy -= Bulletmap[FLASH].damage / 2;
	    }
	}
      
      if (!InvincibleMode && !Druidmap[Me.type].flashimmune)
	Me.energy -= Bulletmap[FLASH].damage / 2;
      
      return;
      break;
    default:
      
      /* Kollision der Bullets mit dem Hintergrund feststellen */
      if (IsPassable (CurBullet->pos.x, CurBullet->pos.y, CENTER) != CENTER)
	{
	  DeleteBullet (num);
	  return;			/* Bullet ist hin */
	}
      
      /* Influence getroffen ?? */
      xdist = Me.pos.x - CurBullet->pos.x;
      ydist = Me.pos.y - CurBullet->pos.y;
      if ((xdist * xdist + ydist * ydist) < DRUIDHITDIST2)
	{
	  GotHitSound ();
	  
	  if (!InvincibleMode)
	    Me.energy -= Bulletmap[CurBullet->type].damage;	/* Energie verlieren */
	  
	  // The bullet has hit.  The damage has been calculated.  Now it can be disabled.
	  // ATTENTION!  These instructions belong here and must not be moved up.
	  CurBullet->type = OUT;
	  CurBullet->mine = FALSE;
	  return;			/* Bullet ist hin */
	}
      
      /* Alle Enemys checken */
      for (i = 0; i < NumEnemys; i++)
	{
	  if (Feindesliste[i].Status == OUT || Feindesliste[i].levelnum != level)
	    continue;
	  
	  xdist = CurBullet->pos.x - Feindesliste[i].pos.x;
	  ydist = CurBullet->pos.y - Feindesliste[i].pos.y;
	  
	  if ((xdist * xdist + ydist * ydist) < DRUIDHITDIST2)
	    {
	      Feindesliste[i].energy -= Bulletmap[CurBullet->type].damage;
	      if (!CurBullet->mine)
		{
		  FBTZaehler++;
		}
	      CurBullet->type = OUT;
	      CurBullet->mine = FALSE;
	      break;		/* Schleife beenden */
	    }			/* if getroffen */
	  
	}				/* for Feindesliste */
      return;
      break;
    } // switch ( Bullet-Type )
} /* CheckBulletCollisions */
  
/*@Function============================================================
  @Desc: CheckBlastCollsions(int num)
  checkt Collisionen des Blasts num mit Bullets und Druids
  UND reagiert darauf
  
  LastBlastHit: Diese Variable dient dazu, doppelte Messages zu unter-
  dr"ucken. Blasts schaden mehrere Phasen lang. Der Z"ahler LastBlastHit
  gibt den Zeitabstand zur letzten Verletzung durch Blasts an.
  Er wird in der Hauptschleife erh"oht.
  @Ret: void 
  @Int:
  * $Function----------------------------------------------------------*/
void
CheckBlastCollisions (int num)
{
  int i;
  int level = CurLevel->levelnum;
  Blast CurBlast = &(AllBlasts[num]);
  static int RHBZaehler = 0;

  /* check Blast-Bullet Collisions and kill hit Bullets */
  for (i = 0; i < MAXBULLETS; i++)
    {
      if (AllBullets[i].type == OUT)
	continue;
      if (CurBlast->phase > 4)
	break;

      if (abs (AllBullets[i].pos.x - CurBlast->PX) < BLASTRADIUS)
	if (abs (AllBullets[i].pos.y - CurBlast->PY) < BLASTRADIUS)
	  {
	    /* KILL Bullet silently */
	    AllBullets[i].type = OUT;
	    AllBullets[i].mine = FALSE;
	  }

    }				/* for */

  /* Check Blast-Enemy Collisions and smash energy of hit enemy */
  for (i = 0; i < NumEnemys; i++)
    {
      if ((Feindesliste[i].Status == OUT)
	  || (Feindesliste[i].levelnum != level))
	continue;

      if (abs (Feindesliste[i].pos.x - CurBlast->PX) <
	  BLASTRADIUS + DRUIDRADIUSX)
	if (abs (Feindesliste[i].pos.y - CurBlast->PY) <
	    BLASTRADIUS + DRUIDRADIUSY)
	  {
	    /* drag energy of enemy */
	    Feindesliste[i].energy -= BLASTDAMAGE * Frame_Time ();
	    printf (" Robot hit by Blast %d.\n", RHBZaehler++);
	  }

      if (Feindesliste[i].energy < 0)
	Feindesliste[i].energy = 0;

    }				/* for */

  /* Check influence-Blast collisions */
  if ((Me.status != OUT) && (abs (Me.pos.x - CurBlast->PX) < DRUIDRADIUSX))
    if (abs (Me.pos.y - CurBlast->PY) < DRUIDRADIUSY)
      {
	if (!InvincibleMode)
	  {
	    Me.energy -= BLASTDAMAGE * Frame_Time ();
	    if ((PlusExtentionsOn) && (LastBlastHit > 5))
	      InsertMessage ("Blast hit me! OUCH!");
	    LastBlastHit = 0;
	  }
	// In order to avoid a new sound EVERY frame we check for how long the previous blast 
	// lies back in time.  LastBlastHit is a float, that counts SECONDS real-time !!
	if (LastGotIntoBlastSound > 1.2)
	  {
	    GotIntoBlastSound ();
	    LastGotIntoBlastSound = 0;
	  }
      }

}				/* CheckBlastCollisions */

#undef _bullet_c
