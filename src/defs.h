 /*=@Header==============================================================
 * $Source$
 *
 * @Desc: all the define-constants and macroes
 * 	
 * $Revision$
 * $State$
 *
 * $Author$
 *
 * $Log$
 * Revision 1.4  1994/06/19 16:17:44  prix
 * Sat May 21 07:52:34 1994: neues Rahmenbild
 * Sat May 21 11:40:01 1994: Wait_after_killed von 20 auf 35
 * Sat May 21 11:55:23 1994: wait_after_killed von 35 auf 25
 *
 * Revision 1.3  1993/05/23  21:03:10  prix
 * Sun May 23 07:43:22 1993: Laufkonstanten hinzugefuegt
 * Sun May 23 16:29:09 1993: added druid related defines
 *
 * Revision 1.2  1993/05/22  21:58:10  rp
 * added MAXMAPLINES
 *
 * Revision 1.1  1993/05/22  20:55:51  rp
 * Initial revision
 *
 *
 *-@Header------------------------------------------------------------*/

#ifndef _defs_h
#define _defs_h

#ifdef WARNALL
#include "warnall.h"
#endif
#include "colodefs.h"

// **********************************************************************
//

#define MEMDEBUG


// **********************************************************************

#define PARA64 						TRUE

#define TRUE (1==1)
#define FALSE (1==0)

#define ERR 	-1
#define OK		0



/* Konstanten fuer die Dateinamen */
#define SHIPNAME	".\\daten\\ship1"
#define PALBILD	".\\daten\\palbild.lbm"
#define COLORFILE ".\\daten\\levels.col"
#define BLOCKBILD1 ".\\daten\\block.lbm"
#define BLOCKBILD2 ""
#define TITELBILD1 ".\\daten\\title.lbm"
#define RAHMENBILD1 ".\\daten\\rahmen.lbm"
#define PARAPLUSRAHMENBILD ".\\daten\\plusrah1.lbm"
#define BLASTBILD ".\\daten\\blast.lbm"
#define BULLETBILD ".\\daten\\bullet.lbm"
#define INFLUENCEBILD ".\\daten\\influ.lbm"
#define DATA70ZEICHENSATZ ".\\daten\\para8x8.fnt"
#define DIGITBILD ".\\daten\\digits.lbm"
#define ENEMYBILD ".\\daten\\enemy.lbm"
#define SEITENANSICHTBILD ".\\daten\\ship.lbm"
#define EL_BLOCKS_FILE 		".\\daten\\ship2.lbm"
#define FONTBILD ".\\daten\\parafont.lbm"
#define CONSOLENBILD ".\\daten\\console.lbm"
#define ROBOTPICTUREBILD ".\\daten\\robots.lbm"
#define SHIELDPICTUREBILD ".\\daten\\shield.lbm"

/* Konstanten die unmittelbar die Hardware betreffen */
#define SCREENADDRESS		0xa000	/* screen - data */
#define RETRACEWARTEPERIODE 5
#define SCREENBREITE 320
#define SCREENHOEHE 200
#define SCREENLEN				320
#define SCREENHEIGHT			200

/* Dimensionen von Bloecken und Bildern */

/* Rahmen */
#define RAHMENBREITE		SCREENBREITE
#define RAHMENHOEHE		32

/* Menu in Konsole */
#define MENUITEMHEIGHT 77
#define MENUITEMLENGTH 50
#define MENUITEMMEM (MENUITEMLENGTH * MENUITEMHEIGHT)

/* Ship-Elevator Picture */
#define NUM_EL_BLOCKS	17

#define EL_BLOCK_LEN		8
#define EL_BLOCK_HEIGHT	8
#define EL_BLOCK_MEM 	EL_BLOCK_LEN * EL_BLOCK_HEIGHT

#define ELEVATOR_LEN		38
#define ELEVATOR_HEIGHT	12

/* Konstanten die die Ausmasse von maps und Arrays beeinflussen */
#define BLOCKBREITE 32
#define BLOCKHOEHE 32
#define BLOCKMEM  BLOCKBREITE*BLOCKHOEHE


#define VIEWBREITE 9
#define VIEWHOEHE 4
#define INTERNBREITE 11			/* 11 */
#define INTERNHOEHE 5

#define BULLETSPEEDINFLUENCE 2

#define DIRECTIONS 8

#define ALLCLASSNAMES 11
#define ALLSHIPS 4

#define NUMBEROFS 5+12*BLOCKBREITE
#define ENEMYPHASES 8

#define WAIT_LEVELEMPTY		18		/* warte bevor Graufaerben */
#define WAIT_AFTER_KILLED	25		/* warte, bevor Spiel aus */
#define WAIT_SHIPEMPTY	20
#define WAIT_TRANSFERMODE	5		/* warte, bevor in Transfermode schalten */

/* Soundblasterkonstanten */
#define SBCHANNELS 7

/* Nummern der Schilder */
enum _shields {
	SHIELD0=0,
	SHIELD1,
	SHIELD2,
	SHIELD3
};

/* Richtungsdefinitionen (fuer die Einstellung der Schussrichtung) */
enum _directions {
	OBEN=0,
	RECHTSOBEN,
	RECHTS,
	RECHTSUNTEN,
	UNTEN,
	LINKSUNTEN,
	LINKS,
	LINKSOBEN,
	CENTER,
	LIGHT	/* special: checking passability for light, not for a checkpos */
};

/* Diese Konstanten geben die Groesse des unsichtbaren Bereiches links,rechts
	und oberhalb des Userfensters an. */
#define USERFENSTERLINKS (BLOCKBREITE/2+10)  /* 32 */  /* 32+16 */
#define USERFENSTERRECHTS (BLOCKBREITE/2+10) /* 32 */  /* 32+16 */
#define USERFENSTEROBEN BLOCKHOEHE/2  /* 25 */

#define USERFENSTERBREITE ((INTERNBREITE-1)*BLOCKBREITE-20)  /* (288-32) */
#define USERFENSTERHOEHE ((INTERNHOEHE-1)*BLOCKHOEHE)     /* 112 */
#define USERFENSTERPOSX ( (SCREENBREITE-USERFENSTERBREITE) / 2)
#define USERFENSTERPOSY ( (SCREENHOEHE-USERFENSTERHOEHE) )
#define USERFENSTERUNTEN USERFENSTEROBEN+USERFENSTERHOEHE

/* Koordinaten der Bloecke die isoliert werden sollen */
#define INFLUENCEBLOCKPOSITIONX 0
#define INFLUENCEBLOCKPOSITIONY 0 /* BLOCKHOEHE */
#define BULLETBLOCKPOSITIONY 0 /* (BLOCKHOEHE*4) */
#define BLASTBLOCKPOSITIONY 0 /* (BLOCKHOEHE*3) */

#define STARTENERGIE 100
#define ENERGIEBALKENBREITE 15
#define MAXENERGIEBALKENLAENGE 160
#define ENERGIEPOSY 180

#define CORNERHOEHE 3
#define CORNERBREITE 3
#define CORNERRECHTS 22
#define CORNERLINKS 10
#define CORNEROBEN 8
#define CORNERUNTEN 18

/* Maximale Anzahl von ... */

#define BLOCKANZAHL 43

#define ALLDRUIDTYPES		25		/* number of druid-models that exist */
#define ALLBULLETTYPES		4		/* number of bullet-types */
#define ALLBLASTTYPES		2     /* number of different exposions */

#define MAXBULLETS		10		/* maximum possible Bullets in the air */
#define MAXBLASTS			5		/* max. possible Blasts visible */
#define AGGRESSIONMAX  100

/* Map-related defines:
	WARNING leave them here, they are required in struct.h
*/
#define MAX_WP_CONNECTIONS 4
#define MAXMAPLINES 50
#define ALLLEVELS			18
#define MAX_LEVELS_ON_SHIP		20

#define MAX_ENEMYS_ON_SHIP		150

#define ALLELEVATORS		30
#define MAXWAYPOINTS 30
#define MAX_DOORS_ON_LEVEL 20
#define MAX_REFRESHES_ON_LEVEL	10

#define WAIT_COLLISION		9		/* enemy bleibt nach coll. stehen */

/* Macros */
#define GrobX (Me.pos.x / BLOCKBREITE)
#define GrobY (Me.pos.y / BLOCKHOEHE)
#define FeinX (Me.pos.x%BLOCKBREITE)
#define FeinY (Me.pos.y%BLOCKHOEHE)

#define CLFeinY ((Me.pos.y+BLOCKHOEHE/2) % BLOCKHOEHE)
#define CLGrobY ((Me.pos.y+BLOCKHOEHE/2) / BLOCKHOEHE)
#define CLFeinX ((Me.pos.x+BLOCKBREITE/2) % BLOCKHOEHE)
#define CLGrobX ((Me.pos.x+BLOCKBREITE/2) / BLOCKHOEHE)

#define SpeedX (Me.speed.x)
#define SpeedY (Me.speed.y)

#define SwapScreen() MyMemcpy(RealScreen, InternalScreen, SCREENLEN*SCREENHEIGHT)

#define BREMSDREHUNG 3 		/* warte 3*, bevor Influencer weitergedreht wird */

/* Wegstossgeschw. von Tueren u.ae. */
#define PUSHSPEED 2

/* Schusstypen */
enum _bullets {
	PULSE,
	SINGLE_PULSE,
	MILITARY,
	FLASH
};


/* Explosionstypen */
enum _explosions {
	BULLETBLAST,
	DRUIDBLAST,
	OWNBLAST
};

#define BLINKENERGY 25 

/* Druidtypen */
enum _druids {
	DRUID001 = 0,		/* You will know why are the numbers there, when you */
	DRUID123 = 1,		/* enter the crew of a level !! */
	DRUID139 = 2,
	DRUID247 = 3,
	DRUID249 = 4,
	DRUID296 = 5,
	DRUID302 = 6,
	DRUID329 = 7,
	DRUID420 = 8,
	DRUID476 = 9,
	DRUID493 =10,
	DRUID516 =11,
	DRUID571 =12,
	DRUID598 =13,
	DRUID614 =14,
	DRUID615 =15,
	DRUID629 =16,
	DRUID711 =17,
	DRUID742 =18,
	DRUID751 =19,
	DRUID821 =20,
	DRUID834 =21,
	DRUID883 =22,
	DRUID999 =23,
	DEBUG_ENEMY = 24
};

/* Status- Werte der Druids */
enum _status {
	MOBILE,
	TRANSFERMODE,
	WEAPON,
	CAPTURED,
	COMPLETE,
	REJECTED,
	CONSOLE,
	DEBRIEFING,
	TERMINATED,
	PAUSE,
	CHEESE
};


/* Dimensionen der Druids (fuer NotPassable() and CheckEnemyCollsion() ) */
#define DRUIDRADIUSX		10
#define DRUIDRADIUSY		10
#define DRUIDRADIUSXY	7

/* Dimension eines Blasts */
#define BLASTRADIUS		BLOCKBREITE/3
#define BLASTDAMAGE		5

#define DECKCOMPLETEBONUS 500

/* Tastaturgeschwindigkeiten */
#define TYPEMATIC_SLOW 127
#define TYPEMATIC_FAST 0
#define TYPEMATIC_TAKEOVER 92             /* For the takeover-game */

#define OUT			TERMINATED		/* Type fuer inaktive Dinge */

#endif
