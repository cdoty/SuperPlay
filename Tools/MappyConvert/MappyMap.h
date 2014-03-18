/* DirectX Header file for mappydx R11 */
/* (C)2002 Robin Burrows  -  rburrows@bigfoot.com */

#pragma once

#include <windows.h>

#define MER_NONE 0		/* All the horrible things that can go wrong */
#define MER_OUTOFMEM 1
#define MER_MAPLOADERROR 2
#define MER_NOOPEN 3
#define MER_MAPTOONEW 4

#define AN_END -1			/* Animation types, AN_END = end of anims */
#define AN_NONE 0			/* No anim defined */
#define AN_LOOPF 1		/* Loops from start to end, then jumps to start etc */
#define AN_LOOPR 2		/* As above, but from end to start */
#define AN_ONCE 3			/* Only plays once */
#define AN_ONCEH 4		/* Only plays once, but holds end frame */
#define AN_PPFF 5			/* Ping Pong start-end-start-end-start etc */
#define AN_PPRR 6			/* Ping Pong end-start-end-start-end etc */
#define AN_PPRF 7			/* Used internally by playback */
#define AN_PPFR 8			/* Used internally by playback */
#define AN_ONCES 9		/* Used internally by playback */

#define MTRANSPR 0xFF	/* 8bit RED transparency value for high/true colour */
#define MTRANSPG 0x00	/* 8bit GREEN transparency value for high/true colour */
#define MTRANSPB 0xFF	/* 8bit BLUE transparency value for high/true colour */

typedef struct {				/* Structure for data blocks */
long bgoff, fgoff;			/* offsets from start of graphic blocks */
long fgoff2, fgoff3; 		/* more overlay blocks */
unsigned long int user1, user2;	/* user long data */
unsigned short int user3, user4;	/* user short data */
unsigned char user5, user6, user7;	/* user byte data */
unsigned char tl : 1;				/* bits for collision detection */
unsigned char tr : 1;
unsigned char bl : 1;
unsigned char br : 1;
unsigned char trigger : 1;			/* bit to trigger an event */
unsigned char unused1 : 1;
unsigned char unused2 : 1;
unsigned char unused3 : 1;
} BLKSTR;

typedef struct {		/* Animation control structure */
signed char antype;	/* Type of anim, AN_? */
signed char andelay;	/* Frames to go before next frame */
signed char ancount;	/* Counter, decs each frame, till 0, then resets to andelay */
signed char anuser;	/* User info */
long int ancuroff;	/* Points to current offset in list */
long int anstartoff;	/* Points to start of blkstr offsets list, AFTER ref. blkstr offset */
long int anendoff;	/* Points to end of blkstr offsets list */
} ANISTR;

extern int maperror;		/* Set to a MER_ error if something wrong happens */
extern short int mapwidth, mapheight, mapblockwidth, mapblockheight, mapdepth;
extern short int mapblockstrsize, mapnumblockstr, mapnumblockgfx;
extern short int * mappt;
extern short int ** maparraypt;
extern unsigned char * mapcmappt;
extern BYTE * mapblockgfxpt;
extern char * mapblockstrpt;
extern ANISTR * mapanimstrpt;
extern ANISTR * mapanimstrendpt;
extern PALETTEENTRY mappept[256];
extern short int * mapmappt[8];
extern short int ** mapmaparraypt[8];
extern int * mapanimseqpt;
extern int mapblockgapx, mapblockgapy, mapblockstaggerx, mapblockstaggery, mapclickmask;
extern int maptype;
extern int maptrans8, maptransred, maptransgreen, maptransblue;

void MapFreeMem (void);
int MapLoad (char *);
int MapDecode (unsigned char *);
void MapInitAnims (void);
void MapUpdateAnims (void);
int MapGenerateYLookup (void);
int MapChangeLayer (int);
int MapLoadMAR (char *, int);
int MapDecodeMAR (unsigned char *, int);
int MapGetBlockID (int, int);
BLKSTR * MapGetBlock (int, int);
