/*----------------------------------------------------------------------
 *
 * Desc: the paraplus initialisation routines
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
#define _init_c

#include "system.h"

#include "defs.h"
#include "struct.h"
#include "global.h"
#include "proto.h"
#include "text.h"
#include "ship.h"


/* Scroll- Fenster */
#define SCROLLSTARTX		USERFENSTERPOSX
#define SCROLLSTARTY		SCREENHOEHE

void Init_Game_Data(void);


/*@Function============================================================
@Desc: This function loads all the constant variables of the game from
       a dat file, that should be optimally human readable.

@Ret: 
* $Function----------------------------------------------------------*/
void
Get_Robot_Data ( void* DataPointer )
{
  int RobotIndex = 0;
  char *RobotPointer;
  char *ValuePointer;  // we use ValuePointer while RobotPointer stays still to allow for
                       // interchanging of the order of appearance of parameters in the game.dat file
  int StringLength;
#define ROBOT_SECTION_BEGIN_STRING "*** Start of Robot Data Section: ***" 
#define NEW_ROBOT_BEGIN_STRING "** Start of new Robot: **" 
#define DROIDNAME_BEGIN_STRING "Droidname: "
#define MAXSPEED_BEGIN_STRING "Maximum speed of this droid: "
#define CLASS_BEGIN_STRING "Class of this droid: "
#define ACCELERATION_BEGIN_STRING "Maximum acceleration of this droid: "
#define MAXENERGY_BEGIN_STRING "Maximum energy of this droid: "
#define LOSEHEALTH_BEGIN_STRING "Rate of energyloss under influence control: "
#define GUN_BEGIN_STRING "Weapon type this droid uses: "
#define AGGRESSION_BEGIN_STRING "Aggression rate of this droid: "
#define FLASHIMMUNE_BEGIN_STRING "Is this droid immune to disruptor blasts? "
#define SCORE_BEGIN_STRING "Score gained for destroying one of this type: "
  if ( (RobotPointer = strstr ( DataPointer , ROBOT_SECTION_BEGIN_STRING ) ) == NULL)
    {
      printf("\n\nBegin of Robot Data Section not found...\n\nTerminating...\n\n");
      Terminate(ERR);
    }
  else
    {
      printf("\n\nBegin of Robot Data Section found. Good.  Starting to read Robot data...\n\n");
      fflush(stdout);
    }

  while ( (RobotPointer = strstr ( RobotPointer, NEW_ROBOT_BEGIN_STRING )) != NULL)
    {
      printf("\n\nFound another Robot specification entry!  Lets add that to the others!");
      RobotPointer ++; // to avoid doubly taking this entry

      // Now we read in the Name of this droid.  We consider as a name the rest of the
      // line with the DROIDNAME_BEGIN_STRING until the "\n" is found.
      if ( (ValuePointer = strstr ( RobotPointer, DROIDNAME_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO DROIDNAME FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen (DROIDNAME_BEGIN_STRING);
	  StringLength = strstr (ValuePointer , "\n") - ValuePointer;
	  Druidmap[RobotIndex].druidname = malloc ( StringLength + 1 );
	  strncpy ( (char*) Druidmap[RobotIndex].druidname , ValuePointer , StringLength );
	  Druidmap[RobotIndex].druidname[StringLength]=0;
	  printf("\nDroidname found!  It reads: %s" , Druidmap[RobotIndex].druidname );
	}

      // Now we read in the maximal speed this droid can go. 
      if ( (ValuePointer = strstr ( RobotPointer, MAXSPEED_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO MAXSPEED ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( MAXSPEED_BEGIN_STRING );
	  sscanf ( ValuePointer , "%lf" , &Druidmap[RobotIndex].maxspeed );
	  printf("\nDroid maximum speed found!  It reads: %f" , Druidmap[RobotIndex].maxspeed );
	}

      // Now we read in the class of this droid.
      if ( (ValuePointer = strstr ( RobotPointer, CLASS_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO CLASS ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( CLASS_BEGIN_STRING );
	  sscanf ( ValuePointer , "%d" , &Druidmap[RobotIndex].class );
	  printf("\nDroid class entry found!  It reads: %d" , Druidmap[RobotIndex].class );
	}

      // Now we read in the maximal acceleration this droid can go. 
      if ( (ValuePointer = strstr ( RobotPointer, ACCELERATION_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO ACCELERATION ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( ACCELERATION_BEGIN_STRING );
	  sscanf ( ValuePointer , "%lf" , &Druidmap[RobotIndex].accel );
	  printf("\nDroid maximum acceleration found!  It reads: %f" , Druidmap[RobotIndex].accel );
	}

      // Now we read in the maximal energy this droid can store. 
      if ( (ValuePointer = strstr ( RobotPointer, MAXENERGY_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO MAXENERGY ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( MAXENERGY_BEGIN_STRING );
	  sscanf ( ValuePointer , "%lf" , &Druidmap[RobotIndex].maxenergy );
	  printf("\nDroid maximum energy found!  It reads: %f" , Druidmap[RobotIndex].maxenergy );
	}

      // Now we read in the lose_health rate.
      if ( (ValuePointer = strstr ( RobotPointer, LOSEHEALTH_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO LOSE_HEALTH ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( LOSEHEALTH_BEGIN_STRING );
	  sscanf ( ValuePointer , "%lf" , &Druidmap[RobotIndex].lose_health );
	  printf("\nDroid lose_health entry found!  It reads: %f" , Druidmap[RobotIndex].lose_health );
	}

      // Now we read in the class of this droid.
      if ( (ValuePointer = strstr ( RobotPointer, GUN_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO GUN ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( GUN_BEGIN_STRING );
	  sscanf ( ValuePointer , "%d" , &Druidmap[RobotIndex].gun );
	  printf("\nDroid gun entry found!  It reads: %d" , Druidmap[RobotIndex].gun );
	}

      // Now we read in the aggression rate of this droid.
      if ( (ValuePointer = strstr ( RobotPointer, AGGRESSION_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO AGGRESSION ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( AGGRESSION_BEGIN_STRING );
	  sscanf ( ValuePointer , "%d" , &Druidmap[RobotIndex].aggression );
	  printf("\nDroid aggression rate entry found!  It reads: %d" , Druidmap[RobotIndex].aggression );
	}

      // Now we read in the flash immunity of this droid.
      if ( (ValuePointer = strstr ( RobotPointer, FLASHIMMUNE_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO FLASHIMMUNE ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( FLASHIMMUNE_BEGIN_STRING );
	  sscanf ( ValuePointer , "%d" , &Druidmap[RobotIndex].flashimmune );
	  printf("\nDroid flashimmune entry found!  It reads: %d" , Druidmap[RobotIndex].flashimmune );
	}

      // Now we score to be had for destroying one droid of this type
      if ( (ValuePointer = strstr ( RobotPointer, SCORE_BEGIN_STRING )) == NULL )
	{
	  printf("\nERROR! NO SCORE ENTRY FOUND! TERMINATING!");
	  Terminate(ERR);
	}
      else
	{
	  ValuePointer += strlen ( SCORE_BEGIN_STRING );
	  sscanf ( ValuePointer , "%d" , &Druidmap[RobotIndex].score );
	  printf("\nDroid score entry found!  It reads: %d" , Druidmap[RobotIndex].score );
	}



      // Now we're potentially ready to process the next droid.  Therefore we proceed to
      // the next number in the Droidmap array.
      RobotIndex++;
    }
  

  printf("\n\nThat must have been the last robot.  We're done here.");


} // int Init_Game_Data ( void )

/*@Function============================================================
@Desc: This function loads all the constant variables of the game from
       a dat file, that should be optimally human readable.

@Ret: 
* $Function----------------------------------------------------------*/
void
Init_Game_Data (void)
{
  struct stat stbuf;
  FILE *DataFile;
  char *Data;
  char *EndPointer;
  char filename[]=MAP_DIR "game.dat";
#define END_OF_GAME_DAT_STRING "*** End of game.dat File ***"

  printf("\nint Init_Game_Data ( void ) called.");
  printf("\nint Init_Game_Data ( void ): The filename is: %s" , filename );

  /* Read the whole game data to memory */
  if ((DataFile = fopen (filename, "r")) == NULL)
    {
      DebugPrintf ("\nint Init_Game_Data( void ): Error opening file.... ");
      Terminate(ERR);
    }
  else
    {
      printf("\nOpening game.dat file succeeded...");
    }

  if (fstat (fileno (DataFile), &stbuf) == EOF)
    {
      printf
	("\nint Init_Game_Data ( void ): Error fstat-ing File....");
      Terminate(ERR);
    }
  else
    {
      printf("\nfstating game.dat file succeeded...");
    }

  if ((Data = (char *) malloc (stbuf.st_size + 64*2)) == NULL)
    {
      DebugPrintf ("\nint Init_Game_Data ( char * constantsname ) : Out of Memory? ");
      Terminate(ERR);
    }

  fread ( Data, (size_t) 64, (size_t) (stbuf.st_size / 64 +1 ), DataFile);

  printf("\nReading dat file succeeded... Adding a 0 at the end of read data....");

  if ( (EndPointer = strstr( Data , END_OF_GAME_DAT_STRING ) ) == NULL )
    {
      printf("\nERROR!  END OF GAME.DAT STRING NOT FOUND!  Terminating...");
      Terminate(ERR);
    }
  else
    {
      EndPointer[0]=0; // we want to handle the file like a string, even if it is not zero
                       // terminated by nature.  We just have to add the zero termination.
    }

  printf("\n\nvoid Init_Game_Data: The content of the read file: \n%s" , Data );

  Get_Robot_Data ( Data );

  // free ( Data ); DO NOT FREE THIS AREA UNLESS YOU REALLOCATE MEMORY FOR THE
  // DROIDNAMES EVERY TIME!!!

} // int Init_Game_Data ( void )

/* -----------------------------------------------------------------
 * This function is for stability while working with the SVGALIB, which otherwise would
 * be inconvenient if not dangerous in the following respect:  When SVGALIB has switched to
 * graphic mode and has grabbed the keyboard in raw mode and the program gets stuck, the 
 * console will NOT be returned to normal, the keyboard will remain useless and login from
 * outside and shutting down or reseting the console will be the only way to avoid a hard
 * reset!
 * Therefore this function is introduced.  When Paradroid starts up, the operating system is
 * instructed to generate a signal ALARM after a specified time has passed.  This signal will
 * be handled by this function, which in turn restores to console to normal and resets the
 * yiff sound server access if applicable. (All this is done via calling Terminate
 * of course.) 
 * -----------------------------------------------------------------*/
static void
timeout (int sig)
{
  DebugPrintf
    ("\n\nstatic void timeout(int sig): Automatic termination NOW!!");
  Terminate (0);
}				/* timeout */

char copyright[] = "\nCopyright (C) 2002 Johannes Prix, Reinhard Prix\n\
Freedroid comes with NO WARRANTY to the extent permitted by law.\n\
You may redistribute copies of Freedroid\n\
under the terms of the GNU General Public License.\n\
For more information about these matters, see the file named COPYING.\n";


char usage_string[] =
  "Usage: freedroid [-v|--version] \n\
                    [-q|--nosound] \n\
                    [-s|--sound] \n\
                    [-t|--timeout=SECONDS] \n\
                    [-f|--fullscreen] [-w|--window]\n\
                    [-j|--sensitivity]\n\
                    [-d|--debug=LEVEL]\n\
\n\
Report bugs to freedroid@??? (sorry, havent got one yet ;)\n";

/* -----------------------------------------------------------------
 *  parse command line arguments and set global switches 
 *  exit on error, so we don't need to return success status
 * -----------------------------------------------------------------*/
void
parse_command_line (int argc, char *const argv[])
{
  int c;
  int timeout_time;		/* timeout to restore text-mode */

  static struct option long_options[] = {
    {"version", 0, 0, 'v'},
    {"help", 	0, 0, 'h'},
    {"nosound", 0, 0, 'q'},
    {"sound", 	0, 0, 's'},
    {"timeout", 1, 0, 't'},
    {"debug", 	2, 0, 'd'},
    {"window",  0, 0, 'w'},
    {"fullscreen",0,0,'f'},
    {"sensitivity",1,0,'j'},
    { 0, 	0, 0,  0}
  };

  //   sound_on=TRUE;

  while (1)
    {
      c = getopt_long (argc, argv, "vqst:h?d::wfj:", long_options, NULL);
      if (c == -1)
	break;

      switch (c)
	{
	  /* version statement -v or --version
	   * following gnu-coding standards for command line interfaces */
	case 'v':
	  printf ("\n%s %s  \n", PACKAGE, VERSION); 
	  printf (copyright);
	  exit (0);
	  break;

	case 'h':
	case '?':
	  printf (usage_string);
	  exit (0);
	  break;

	case 'q':
	  sound_on = FALSE;
	  break;

	case 's':
	  sound_on = TRUE;
	  break;

	case 't':
	  timeout_time = atoi (optarg);
	  if (timeout_time > 0)
	    {
	      signal (SIGALRM, timeout);
	      alarm (timeout_time);	/* Terminate after some seconds for safety. */
	    }
	  break;
	case 'j':
	  joy_sensitivity = atoi (optarg);
	  if (joy_sensitivity < 0 || joy_sensitivity > 32)
	    {
	      printf ("\nJoystick sensitivity must lie in the range [0;32]\n");
	      Terminate(ERR);
	    }
	  break;

	case 'd':
	  if (!optarg) 
	    debug_level = 1;
	  else
	    debug_level = atoi (optarg);
	  break;

	case 'f':
	  fullscreen_on = TRUE;
	  break;
	case 'w':
	  fullscreen_on = FALSE;
	  break;

	default:
	  printf ("\nOption %c not implemented yet! Ignored.", c);
	  break;
	}			/* switch(c) */
    }				/* while(1) */
}				/* parse_command_line */


/*-----------------------------------------------------------------
 * @Desc: Startwerte fuer neues Spiel einstellen 
 * 
 * @Ret: 
 *
 *-----------------------------------------------------------------*/
void
InitNewGame (void)
{
  int i;

  DebugPrintf ("\nvoid InitNewGame(void): real function call confirmed...");

  printf("\nA new game is being initialized...");

  Activate_Conservative_Frame_Computation();

  LastBlastHit = 0;
  LastGotIntoBlastSound = 2;
  LastRefreshSound = 2;
  PlusExtentionsOn = FALSE;
  ThisMessageTime = 0;
  Draw_Framerate=TRUE;
  Draw_Energy=FALSE;


  /*
   * Die Punkte wieder auf 0 setzen
   */
  RealScore = 0;
  ShowScore = 0;

  /* L"oschen der Messagequeue */
  KillQueue ();
  InsertMessage (" Game on!  Good Luck,,.");

  /* Alle Bullets und Blasts loeschen */
  for (i = 0; i < MAXBULLETS; i++)
    {
      AllBullets[i].type = OUT;
      AllBullets[i].mine = FALSE;
    }

  DebugPrintf ("\nvoid InitNewGame(void): All bullets have been deleted...");

  for (i = 0; i < MAXBLASTS; i++)
    {
      AllBlasts[i].phase = OUT;
      AllBlasts[i].type = OUT;
    }

  DebugPrintf ("\nvoid InitNewGame(void): All blasts have been deleted...");

  /* Alle Levels wieder aktivieren */
  for (i = 0; i < curShip.num_levels; i++)
    curShip.AllLevels[i]->empty = FALSE;

  DebugPrintf
    ("\nvoid InitNewGame(void): All levels have been set to 'active'...");

  
  i = MyRandom (3);  /* chose one out of 4 possible start positions */
  switch (i)
    {
    case 0:
      CurLevel = curShip.AllLevels[4];
  Me.pos.x = 1;
  Me.pos.y = 1;
      break;

    case 1:
      CurLevel = curShip.AllLevels[5];
  Me.pos.x = 3;
  Me.pos.y = 1;
      break;

    case 2:
      CurLevel = curShip.AllLevels[6];
  Me.pos.x = 2;
  Me.pos.y = 1;
      break;

    case 3:
      CurLevel = curShip.AllLevels[7];
  Me.pos.x = 2;
  Me.pos.y = 1;
      break;

    default:
      printf
	("\n InitNewGame(): MyRandom() failed  Terminating...\n");
      Terminate (ERR);
      break;
    } /* switch */

  // printf("\nvoid InitNewGame(void): Starting point for the influencer has been set...:\n");
  // printf ("%f,%f", Me.pos.x, Me.pos.y);

  /* Alertcolor auf Gruen zurueckschalten */
  Alert = 0;

  /* Enemys initialisieren */
  if (GetCrew (SHIPNAME) == ERR)
    {
      printf
	("\nInitNewGame(): ERROR: Initialization of enemys failed...");
      Terminate (-1);
    }


  /* Introduction und Title */
  Title ();

  DebugPrintf
    ("\nvoid InitNewGame(void): The title signaton has been successfully displayed...:");

  /* Farben des aktuellen Levels einstellen */
  SetLevelColor (CurLevel->color); 

  /* set correct Influ color */
  SetPalCol (INFLUENCEFARBWERT, Mobilecolor.rot, Mobilecolor.gruen,
	       Mobilecolor.blau);

  /* Den Banner fuer das Spiel anzeigen */
  ClearGraphMem();
  DisplayBanner (NULL, NULL,  BANNER_FORCE_UPDATE );

  SetTextColor (FONT_WHITE, FONT_RED);
  InitBars = TRUE;

  Switch_Background_Music_To (COMBAT_BACKGROUND_MUSIC_SOUND);

  // Now that the briefing and all that is done,
  // the influence structure can be initialized for
  // the new mission:
  Me.type = DRUID001;
  Me.speed.x = 0;
  Me.speed.y = 0;
  Me.energy = Druidmap[DRUID001].maxenergy;
  Me.health = Me.energy;	/* start with max. health */
  Me.autofire = FALSE;
  Me.status = MOBILE;
  Me.phase = 0;

  printf("done."); // this matches the printf at the beginning of this function
  fflush(stdout);
  
  return;

} /* InitNewGame */

/*-----------------------------------------------------------------
 * @Desc: This function initializes the whole Freedroid game.
 * 
 * THIS MUST NOT BE CONFUSED WITH INITNEWGAME, WHICH
 * ONLY INITIALIZES A NEW MISSION FOR THE GAME.
 *  
 * 
 *  
 *-----------------------------------------------------------------*/
void
InitFreedroid (void)
{
  struct timeval timestamp;

  Overall_Average=0.041;
  SkipAFewFrames = 0;

  Init_Video ();

  Init_Audio ();
  
  Init_Joy ();

  // The default should be, that no rescaling of the
  // combat window at all is done.
  CurrentCombatScaleFactor = 1;

  /* 
   * Initialise random-number generator in order to make 
   * level-start etc really different at each program start
   */
  gettimeofday(&timestamp, NULL);
  srand((unsigned int) timestamp.tv_sec); /* yes, we convert long->int here! */

  /* initialize the high score values */
  /* 
   * this really should be read from disk here, 
   * but for the moment we just start from zero 
   * each time
   */
  highscores = NULL;

  Draw_Framerate=FALSE;
  HideInvisibleMap = FALSE;	/* Hide invisible map-parts. Para-extension!! */

  Init_Druidmap ();   /* initialise some global text variables */

  MinMessageTime = 55;
  MaxMessageTime = 850;

  /* Color values for the function SetColors */
  Transfercolor.gruen = 13;
  Transfercolor.blau = 13;
  Transfercolor.rot = 63;
  Mobilecolor.gruen = 63;
  Mobilecolor.blau = 63;
  Mobilecolor.rot = 63;

  GameAdapterPresent = FALSE;	/* start with this */

  if (LoadShip (SHIPNAME) == ERR)
    {
      printf ("Error in LoadShip\n");
      Terminate (ERR);
    }

  CurLevel = NULL; // please leave this here BEFORE InitPictures

  /* Now fill the pictures correctly to the structs */
  if (!InitPictures ())
    {		
      printf("\n Error in InitPictures reported back...\n");
      Terminate(ERR);
    }

  /* Init the Takeover- Game */
  InitTakeover ();

  Init_Game_Data ( );

  // Initialisieren der Schildbilder
  //  GetShieldBlocks ();

  return;
} /* InitFreedroid() */

/*-----------------------------------------------------------------
 *
 * a bit stupid: here we initialise the global druid-descriptions
 *
 *-----------------------------------------------------------------*/
void
Init_Druidmap (void)
{

  Druidmap[DRUID001].notes =
    "robot activity influence device. This helmet is self-powered and will control any robot for a short time. Lasers are turret-mounted. ";
  Druidmap[DRUID123].notes =
    "simpe rubbish diposal robot. Common device in most space craft to maintain a clean ship. ";
  Druidmap[DRUID139].notes =
    "created by Dr. Masternak to clean up large heaps of rubbish. Its large scoop is used to collect rubbish. It is then crushed internally. ";
  Druidmap[DRUID247].notes =
    "light duty servant robot. One of the first to use the anti-grav system. ";
  Druidmap[DRUID249].notes =
    "cheaper version of the anti-grav servant robot. ";
  Druidmap[DRUID296].notes =
    "this robot is used mainly for serving drinks. A tray is mounted on the head. Built by Orchard and Marsden Enterprises. ";
  Druidmap[DRUID302].notes =
    "common device for moving small packages. Clamp is mounted on the lower body. ";
  Druidmap[DRUID329].notes =
    "early type messenger robot. Large wheels impede motion on small craft.an";
  Druidmap[DRUID420].notes =
    "slow maintenance robot. Confined to drive maintenance during flight. ";
  Druidmap[DRUID476].notes =
    "ship maintenance robot. Fitted with multiple arms to carry out repairs to the ship efficiently. All craft built after the Jupiter-incident are supplied with a team of these. ";
  Druidmap[DRUID493].notes =
    "slave maintenance droid. Standard version will carry its own toolbox. ";
  Druidmap[DRUID516].notes =
    "early crew droid. Able to carry out simple flight checks only. No longer supplied. ";
  Druidmap[DRUID571].notes =
    "standard crew droid. Supplied with the ship. ";
  Druidmap[DRUID598].notes =
    "a highly sophisticated device. Able to control the Robo-Freighter on its own. ";
  Druidmap[DRUID614].notes =
    "low security sentinel droid. Used to protect areas of the ship from intruders. A slow but sure device. ";
  Druidmap[DRUID615].notes =
    "sophisticated sentinel droid. Only 2000 built by the Nicholson Company. these are now very rare.";
  Druidmap[DRUID629].notes =
    "low sentinel droid. Lasers are built into the turret. These are mounted on a small tank body. May be fitted with an auto-cannon on-the Gillen version. ";
  Druidmap[DRUID711].notes =
    "heavy duty battle droid. Disruptor is built into the head. One of the first in service with the Military. ";
  Druidmap[DRUID742].notes =
    "this version is the one mainly used by the Military. ";
  Druidmap[DRUID751].notes =
    "very heavy duty battle droid. Only a few have so far entered service. These are the most powerful battle units ever built. ";
  Druidmap[DRUID821].notes =
    "a very reliable anti-grav unit is fitted into this droid. It will patrol the ship and eliminate intruders as soon as detected by powerful sensors. ";
  Druidmap[DRUID834].notes =
    "early type anti-grav security droid. Fitted with an over-driven anti-grav unit. This droid is very fast but is not reliable. ";
  Druidmap[DRUID883].notes =
    "this droid was designed from archive data. For some unknown reason it instils great fear in Human adversaries. ";
  Druidmap[DRUID999].notes =
    "experimental command cyborg. Fitted with a new tipe of brain. Mounted on a security droid anti-grav unit for convenience. warning: the influence device may not control a primode brain for long. ";

  return;

} /* Init_Textvars () */



/*-----------------------------------------------------------------
 * @Desc: Diese Prozedur ist fuer die Introduction in das Spiel
 *  verantwortlich. Im Moment beschrankt sich ihre Funktion auf das
 *  Laden und anzeigen eines Titelbildes, das dann ausgeblendet wird.
 * 
 *-----------------------------------------------------------------*/
void
Title (void)
{
  int ScrollEndLine = USERFENSTERPOSY;	/* Endpunkt des Scrollens */

  // STRANGE!! This command will be silently ignored by SDL?
  // WHY?? DONT KNOW!!!
  // Play_Sound ( CLASSICAL_BEEP_BEEP_BACKGROUND_MUSIC );

  // Play_Sound ( CLASSICAL_BEEP_BEEP_BACKGROUND_MUSIC );
  Switch_Background_Music_To ( CLASSICAL_BEEP_BEEP_BACKGROUND_MUSIC );
  // Switch_Background_Music_To ( COMBAT_BACKGROUND_MUSIC_SOUND );

  SDL_SetClipRect ( ne_screen, NULL );
  DisplayImage ( NE_TITLE_PIC_FILE );

  PrepareScaledSurface(TRUE);

  while (!SpacePressed ());
  while (SpacePressed());

  Me.status=BRIEFING;

  // ClearGraphMem ();
  // DisplayBanner (NULL, NULL,  BANNER_FORCE_UPDATE ); 

  // SetTextColor (FONT_BLACK, FONT_RED);

  SetCurrentFont( FPS_Display_BFont );

  ScrollText (TitleText1, SCROLLSTARTX, SCROLLSTARTY, ScrollEndLine);
  ScrollText (TitleText2, SCROLLSTARTX, SCROLLSTARTY, ScrollEndLine);
  ScrollText (TitleText3, SCROLLSTARTX, SCROLLSTARTY, ScrollEndLine);
  ScrollText (TitleText4, SCROLLSTARTX, SCROLLSTARTY, ScrollEndLine);

  ClearGraphMem ();
  DisplayBanner (NULL, NULL,  BANNER_FORCE_UPDATE ); 
  SDL_Flip( ne_screen );

  return;

} /* Title() */

/*@Function============================================================
@Desc: Diese Prozedur ist fuer die Introduction in das Spiel verantwortlich. Im
   Moment beschr�nkt sich ihre Funktion auf das Laden und anzeigen eines
   Titelbildes, das dann ausgeblendet wird.

@Ret: keiner
@Int: keiner
* $Function----------------------------------------------------------*/
void
EndTitle (void)
{
  int ScrollEndLine = USERFENSTERPOSY;	/* Endpunkt des Scrollens */

  DebugPrintf ("\nvoid EndTitle(void): real function call confirmed...:");

  Switch_Background_Music_To (CLASSICAL_BEEP_BEEP_BACKGROUND_MUSIC);

  DisplayBanner (NULL, NULL,  BANNER_FORCE_UPDATE );

  SetTextColor (FONT_BLACK, FONT_RED);

  ScrollText (EndTitleText1, SCROLLSTARTX, SCROLLSTARTY, ScrollEndLine);
  ScrollText (EndTitleText2, SCROLLSTARTX, SCROLLSTARTY, ScrollEndLine);

  while ( SpacePressed() );

} /* EndTitle() */

/*@Function============================================================
@Desc: Diese Funktion Sprengt den Influencer und beendet das Programm

@Ret: 
@Int:
* $Function----------------------------------------------------------*/
void
ThouArtDefeated (void)
{
  int j;
  int now;

  DebugPrintf ("\nvoid ThouArtDefeated(void): Real function call confirmed.");
  Me.status = TERMINATED;
  ThouArtDefeatedSound ();
  ExplodeInfluencer ();

  now=SDL_GetTicks();

  while ( SDL_GetTicks()-now < 1000 * WAIT_AFTER_KILLED )
    {
      Assemble_Combat_Picture ( DO_SCREEN_UPDATE );
      DisplayBanner (NULL, NULL,  0 );
      ExplodeBlasts ();
      MoveBullets ();
      MoveEnemys ();

      for (j = 0; j < MAXBULLETS; j++)
	CheckBulletCollisions (j);
      RotateBulletColor ();
    }

#ifdef NEW_ENGINE

#else
  /* Ein Flimmer zieht "uber den Schirm */
  Flimmern (4);  /* type 4 flimmer */
#endif

  Debriefing ();

  /* Soundblaster soll keine Toene mehr spucken */
  //PORT sbfm_silence();

  GameOver = TRUE;

  DebugPrintf
    ("\nvoid ThouArtDefeated(void): Usual end of function reached.");
  printf("\n\n DefeatedDone \n\n");
}				// void ThouArtDefeated(void)

/*@Function============================================================
@Desc: 

@Ret: 
@Int:
* $Function----------------------------------------------------------*/
void
ThouArtVictorious (void)
{
  ShipEmptyCounter = WAIT_SHIPEMPTY;
  GameOver = TRUE;		/*  */

  ClearUserFenster ();
  getchar_raw ();
}


/* 
----------------------------------------------------------------------
@Desc: This function does the mission debriefing.  If the score was
very good or very bad, player will be asked for this name and the 
highscore list will be updated.

@Ret: 
@Int:
----------------------------------------------------------------------
*/
void
Debriefing (void)
{
  char *tmp_name;
  Hall_entry new, tmp;
  int DebriefColor;
  int count;
  

  return;  // until this works properly


  DebriefColor = FONT_WHITE;
  Me.status = DEBRIEFING;
  SetUserfenster ( DebriefColor );	// KON_BG_COLOR


  count = 1;
  if ( (tmp = highscores) != NULL)
    while (tmp->next) { count++; tmp = tmp->next;}  /* tmp now points to lowest! */
  else
    count = 0;  /* first entry */
 
  if ( (count == MAX_HIGHSCORES) && (RealScore <= tmp->score) )
    return; /* looser! ;) */
      
  /* else: prepare a new entry */
  new = MyMalloc (sizeof(hall_entry));
  new->score = RealScore;
  new->next = new->prev = NULL;
  DisplayText ("Great Score !", User_Rect.x, User_Rect.y, &User_Rect);
  DisplayText ("\nEnter your name: ", User_Rect.x, User_Rect.y, &User_Rect);
  PrepareScaledSurface(TRUE);
  tmp_name = GetString (MAX_NAME_LEN, 2);
  strcpy (new->name, tmp_name);
  free (tmp_name);

  if (!highscores)  /* hey, you're the first one ! */
    highscores = new;
  else   /* link in the new entry */
    {
      count ++;
      tmp = highscores;
      while ( tmp->score >= RealScore )
	tmp = tmp->next;
      ((Hall_entry)(tmp->prev))->next = new;
      new->prev = tmp->prev;
      new->next = tmp;
    }

  /* now check the length of our new highscore list.
   * if longer than MAX_HIGHSCORES */
  tmp = highscores;
  while (tmp->next) tmp = tmp->next; /* find last entry */

  if ( count > MAX_HIGHSCORES ) /* the last one drops out */
    {
      ((Hall_entry)(tmp->prev))->next = NULL;
      free (tmp);
    }
  
  return;

} /* Debriefing() */

#undef _init_c



