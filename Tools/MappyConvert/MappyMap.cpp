/* (C)2002 Robin Burrows - rburrows@bigfoot.com
 * This is Release 11B, 7/5/2002 - for Mappy FMP maps with DirectX SDK
 */

#include <stdio.h>
#include <stdlib.h>

#include "MappyMap.h"

/* All global variables used by Mappy playback are here */
int maperror;		/* Set to a MER_ error if something wrong happens */
short int mapwidth, mapheight, mapblockwidth, mapblockheight, mapdepth;
short int mapblockstrsize, mapnumblockstr, mapnumblockgfx;
short int * mappt = NULL;
short int ** maparraypt = NULL;
unsigned char * mapcmappt = NULL;
BYTE * mapblockgfxpt = NULL;
char * mapblockstrpt = NULL;
ANISTR * mapanimstrpt = NULL;
ANISTR * mapanimstrendpt;
short int * mapmappt[8] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
short int ** mapmaparraypt[8] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
/* Added in release 7 */
char mapnovctext[80];
int * mapanimseqpt;
int mapblockgapx, mapblockgapy, mapblockstaggerx, mapblockstaggery, mapclickmask;
int maptype, mapislsb, mapaltdepth;
char * mapaltblockgfxpt = NULL;
int maptrans8, maptransred, maptransgreen, maptransblue;
/* End of Mappy globals */

void MapFreeMem(void)
{
	int i;

	for (i=0;i<8;i++) { if (mapmappt[i]!=NULL) { free (mapmappt[i]); mapmappt[i] = NULL; } }
	mappt = NULL;
	for (i=0;i<8;i++) { if (mapmaparraypt[i]!=NULL) { free (mapmaparraypt[i]); mapmaparraypt[i] = NULL; } }
	maparraypt = NULL;
	if (mapcmappt!=NULL) { free (mapcmappt); mapcmappt = NULL; }
	if (mapblockgfxpt!=NULL) { free (mapblockgfxpt); mapblockgfxpt = NULL; }
	if (mapaltblockgfxpt!=NULL) { free (mapaltblockgfxpt); mapaltblockgfxpt = NULL; }
	if (mapblockstrpt!=NULL) { free (mapblockstrpt); mapblockstrpt = NULL; }
	if (mapanimstrpt!=NULL) { free (mapanimstrpt); mapanimstrpt = NULL; }
	if (mapanimseqpt!=NULL) { free (mapanimseqpt); mapanimseqpt = NULL; }

	mapnovctext[0] = 0;
}

int MapGenerateYLookup (void)
{
	int i, j;

	for (i=0;i<8;i++) {
		if (mapmaparraypt[i]!=NULL) { free (mapmaparraypt[i]); mapmaparraypt[i] = NULL; }
		if (mapmappt[i]!=NULL) {
			mapmaparraypt[i] = (short int **) malloc (mapheight*sizeof(short int *));
			if (mapmaparraypt[i] == NULL) return -1;
			for (j=0;j<mapheight;j++) mapmaparraypt[i][j] = (mapmappt[i]+(j*mapwidth));
			if (mapmappt[i] == mappt) maparraypt = mapmaparraypt[i];
		}
	}
	return 0;
}

static int MEClickmask (int x, int y, int xory)
{
unsigned char * cmgfxpt;

	if (mapblockgfxpt == NULL) return 0;

	cmgfxpt = (unsigned char *) mapblockgfxpt;
	x %= mapblockgapx; y %= mapblockgapy;

	if (x >= mapblockwidth && xory == 0) return 0;
	if (x >= mapblockwidth && xory == 1) {
		if (y < mapblockstaggery) return -1;
		else return 1;
	}
	if (y >= mapblockheight && xory == 1) return 1;
	if (y >= mapblockheight && xory == 0) {
		if (x < mapblockstaggerx) return -1;
		else return 0;
	}

	cmgfxpt += (mapblockwidth*mapblockheight*((mapdepth+1)/8)*mapclickmask);
	switch (mapdepth) {
		case 8:
			if (cmgfxpt[(y*mapblockwidth)+x] == maptrans8) {
				if (x < (mapblockwidth/2) && xory == 0) return -1;
				if (x >= (mapblockwidth/2) && xory == 0) return 0;
				if (y < (mapblockheight/2) && xory == 1) return -1;
				if (y >= (mapblockheight/2) && xory == 1) return 1;
			}
			return 0;
		case 15:
			if (cmgfxpt[((y*mapblockwidth)+x)*2] == (((maptransred>>1)&0x7C)|((maptransgreen>>6)&0x03)) &&
				cmgfxpt[((y*mapblockwidth)+x)*2+1] == (((maptransgreen<<2)&0xE0)|((maptransblue>>3)&0x1F))) {
				if (x < (mapblockwidth/2) && xory == 0) return -1;
				if (x >= (mapblockwidth/2) && xory == 0) return 0;
				if (y < (mapblockheight/2) && xory == 1) return -1;
				if (y >= (mapblockheight/2) && xory == 1) return 1;
			}
			return 0;
		case 16:
			if (cmgfxpt[((y*mapblockwidth)+x)*2] == (((maptransred)&0xF8)|((maptransgreen>>5)&0x07)) &&
				cmgfxpt[((y*mapblockwidth)+x)*2+1] == (((maptransgreen<<3)&0xE0)|((maptransblue>>3)&0x1F))) {
				if (x < (mapblockwidth/2) && xory == 0) return -1;
				if (x >= (mapblockwidth/2) && xory == 0) return 0;
				if (y < (mapblockheight/2) && xory == 1) return -1;
				if (y >= (mapblockheight/2) && xory == 1) return 1;
			}
			return 0;
		case 24:
			if (cmgfxpt[((y*mapblockwidth)+x)*3] == maptransred &&
				cmgfxpt[((y*mapblockwidth)+x)*3+1] == maptransgreen &&
				cmgfxpt[((y*mapblockwidth)+x)*3+2] == maptransblue) {
				if (x < (mapblockwidth/2) && xory == 0) return -1;
				if (x >= (mapblockwidth/2) && xory == 0) return 0;
				if (y < (mapblockheight/2) && xory == 1) return -1;
				if (y >= (mapblockheight/2) && xory == 1) return 1;
			}
			return 0;
		case 32:
			if (cmgfxpt[((y*mapblockwidth)+x)*4+1] == maptransred &&
				cmgfxpt[((y*mapblockwidth)+x)*4+2] == maptransgreen &&
				cmgfxpt[((y*mapblockwidth)+x)*4+3] == maptransblue) {
				if (x < (mapblockwidth/2) && xory == 0) return -1;
				if (x >= (mapblockwidth/2) && xory == 0) return 0;
				if (y < (mapblockheight/2) && xory == 1) return -1;
				if (y >= (mapblockheight/2) && xory == 1) return 1;
			}
			return 0;
	}
	return 0;
}

BLKSTR * MapGetBlock (int x, int y)
{
short int * mymappt;
ANISTR * myanpt;

	if (maparraypt!= NULL) {
		mymappt = maparraypt[y]+x;
	} else {
		mymappt = mappt;
		mymappt += x;
		mymappt += y*mapwidth;
	}
	if (*mymappt>=0) return ((BLKSTR*) mapblockstrpt) + *mymappt;
	else { myanpt = mapanimstrendpt + *mymappt;
		return ((BLKSTR *) mapblockstrpt) + mapanimseqpt[myanpt->ancuroff]; }
}

int MapChangeLayer (int newlyr)
{
	if (newlyr<0 || newlyr>7 || mapmappt[newlyr] == NULL) return -1;
	mappt = mapmappt[newlyr]; maparraypt = mapmaparraypt[newlyr];
	return newlyr;
}

int MapGetBlockID (int blid, int usernum)
{
int i;
BLKSTR * myblkpt;

	myblkpt = (BLKSTR *) mapblockstrpt;
	if (myblkpt == NULL) return -1;

	for (i=0;i<mapnumblockstr;i++) {
		switch (usernum) {
			case 1:
				if (myblkpt[i].user1 == (unsigned int) blid) return i;
				break;
			case 2:
				if (myblkpt[i].user2 == (unsigned int) blid) return i;
				break;
			case 3:
				if (myblkpt[i].user3 == blid) return i;
				break;
			case 4:
				if (myblkpt[i].user4 == blid) return i;
				break;
			case 5:
				if (myblkpt[i].user5 == blid) return i;
				break;
			case 6:
				if (myblkpt[i].user6 == blid) return i;
				break;
			case 7:
				if (myblkpt[i].user7 == blid) return i;
				break;
		}
	}

	return -1;
}

int MapDecodeMAR (unsigned char * mrpt, int marlyr)
{
int i, j;
short int * mymarpt;

	if (marlyr < 0 || marlyr > 7) return -1;

	if (mapmappt[marlyr] == NULL)
		mapmappt[marlyr] = (short int *) malloc (mapwidth*mapheight*sizeof(short int));

	memcpy (mapmappt[marlyr], mrpt, (mapwidth*mapheight*sizeof(short int)));

	mymarpt = mapmappt[marlyr];
	j = 0; for (i=0;i<(mapwidth*mapheight);i++) { if (mymarpt[i]&0xF) j = 1; }
	if (j == 0) {
		for (i=0;i<(mapwidth*mapheight);i++) {
			if (mymarpt[i] >= 0) mymarpt[i] /= 32;
			else mymarpt[i] /= 16;
		}
	}

	return 0;
}

int MapLoadMAR (char * mname, int marlyr)
{
int i, j;
short int * mymarpt;
FILE * marfpt;

	if (marlyr < 0 || marlyr > 7) return -1;

	marfpt = fopen (mname, "rb");
	if (marfpt==NULL) { return -1; }

	if (mapmappt[marlyr] == NULL)
		mapmappt[marlyr] = (short int *) malloc (mapwidth*mapheight*sizeof(short int));

	if (fread (mapmappt[marlyr], 1, (mapwidth*mapheight*sizeof(short int)), marfpt) !=
		(mapwidth*mapheight*sizeof(short int))) { fclose (marfpt); return -1; }

	fclose (marfpt);

	mymarpt = mapmappt[marlyr];
	j = 0; for (i=0;i<(mapwidth*mapheight);i++) { if (mymarpt[i]&0xF) j = 1; }
	if (j == 0) {
		for (i=0;i<(mapwidth*mapheight);i++) {
			if (mymarpt[i] >= 0) mymarpt[i] /= 32;
			else mymarpt[i] /= 16;
		}
	}

	return 0;
}

void MapInitAnims (void)
{
ANISTR * myanpt;
	if (mapanimstrpt==NULL) return;
	myanpt = (ANISTR *) mapanimstrendpt; myanpt--;
	while (myanpt->antype!=-1)
	{
		if (myanpt->antype==AN_PPFR) myanpt->antype = AN_PPFF;
		if (myanpt->antype==AN_PPRF) myanpt->antype = AN_PPRR;
		if (myanpt->antype==AN_ONCES) myanpt->antype = AN_ONCE;
		if ((myanpt->antype==AN_LOOPR) || (myanpt->antype==AN_PPRR))
		{
		myanpt->ancuroff = myanpt->anstartoff;
		if ((myanpt->anstartoff)!=(myanpt->anendoff)) myanpt->ancuroff=(myanpt->anendoff)-1;
		} else {
		myanpt->ancuroff = myanpt->anstartoff;
		}
		myanpt->ancount = myanpt->andelay;
		myanpt--;
	}
}

void MapUpdateAnims (void)
{
ANISTR * myanpt;

	if (mapanimstrpt==NULL) return;
	myanpt = (ANISTR *) mapanimstrendpt; myanpt--;
	while (myanpt->antype!=-1)
	{
		if (myanpt->antype!=AN_NONE) { myanpt->ancount--; if (myanpt->ancount<0) {
		myanpt->ancount = myanpt->andelay;
		if (myanpt->antype==AN_LOOPF)
		{
			if (myanpt->anstartoff!=myanpt->anendoff) { myanpt->ancuroff++;
			if (myanpt->ancuroff==myanpt->anendoff) myanpt->ancuroff = myanpt->anstartoff;
		} }
		if (myanpt->antype==AN_LOOPR)
		{
			if (myanpt->anstartoff!=myanpt->anendoff) { myanpt->ancuroff--;
			if (myanpt->ancuroff==((myanpt->anstartoff)-1))
				myanpt->ancuroff = (myanpt->anendoff)-1;
		} }
		if (myanpt->antype==AN_ONCE)
		{
			if (myanpt->anstartoff!=myanpt->anendoff) { myanpt->ancuroff++;
			if (myanpt->ancuroff==myanpt->anendoff) { myanpt->antype = AN_ONCES;
				myanpt->ancuroff = myanpt->anstartoff; }
		} }
		if (myanpt->antype==AN_ONCEH)
		{
			if (myanpt->anstartoff!=myanpt->anendoff) {
			if (myanpt->ancuroff!=((myanpt->anendoff)-1)) myanpt->ancuroff++;
		} }
		if (myanpt->antype==AN_PPFF)
		{
			if (myanpt->anstartoff!=myanpt->anendoff) { myanpt->ancuroff++;
			if (myanpt->ancuroff==myanpt->anendoff) { myanpt->ancuroff -= 2;
			myanpt->antype = AN_PPFR;
			if (myanpt->ancuroff<myanpt->anstartoff) myanpt->ancuroff++; }
		} } else {
		if (myanpt->antype==AN_PPFR)
		{
			if (myanpt->anstartoff!=myanpt->anendoff) { myanpt->ancuroff--;
			if (myanpt->ancuroff==((myanpt->anstartoff)-1)) { myanpt->ancuroff += 2;
			myanpt->antype = AN_PPFF;
			if (myanpt->ancuroff>myanpt->anendoff) myanpt->ancuroff--; }
		} } }
		if (myanpt->antype==AN_PPRR)
		{
			if (myanpt->anstartoff!=myanpt->anendoff) { myanpt->ancuroff--;
			if (myanpt->ancuroff==((myanpt->anstartoff)-1)) { myanpt->ancuroff += 2;
			myanpt->antype = AN_PPRF;
			if (myanpt->ancuroff>myanpt->anendoff) myanpt->ancuroff--; }
		} } else {
		if (myanpt->antype==AN_PPRF)
		{
			if (myanpt->anstartoff!=myanpt->anendoff) { myanpt->ancuroff++;
			if (myanpt->ancuroff==myanpt->anendoff) { myanpt->ancuroff -= 2;
			myanpt->antype = AN_PPRR;
			if (myanpt->ancuroff<myanpt->anstartoff) myanpt->ancuroff++; }
		} } }
	} } myanpt--; }
}

void MapCMAPtoPE (unsigned char * mycmappt, PALETTEENTRY * mypept)
{
int i;
	for (i=0;i<256;i++)
	{
		mypept[i].peRed = (BYTE) *mycmappt; mycmappt++;
		mypept[i].peGreen = (BYTE) *mycmappt; mycmappt++;
		mypept[i].peBlue = (BYTE) *mycmappt; mycmappt++;
		mypept[i].peFlags = 0;
	}
}

static int MapGetchksz (unsigned char * locpt)
{
	return ((((int) (locpt[0]))<<24)|(((int) (locpt[1]))<<16)|
		(((int) (locpt[2]))<<8)|((int) (locpt[3])));
}

static int MapGetshort (unsigned char * locpt)
{
int rval;

	if (mapislsb)
	rval = ((((int) (locpt[1]))<<8)|((int) (locpt[0])));
	else
	rval = ((((int) (locpt[0]))<<8)|((int) (locpt[1])));
	if (rval & 0x8000) rval -= 0x10000;
	return rval;
}

static int MapGetlong (unsigned char * locpt)
{
	if (mapislsb)
	return ((((int) (locpt[3]))<<24)|(((int) (locpt[2]))<<16)|
		(((int) (locpt[1]))<<8)|((int) (locpt[0])));
	else
	return ((((int) (locpt[0]))<<24)|(((int) (locpt[1]))<<16)|
		(((int) (locpt[2]))<<8)|((int) (locpt[3])));
}

int MapDecodeMPHD (unsigned char * mdatpt)
{
	mdatpt += 8;
	if (mdatpt[0] > 1) { maperror = MER_MAPTOONEW; return -1; }
	if (mdatpt[2] == 1) mapislsb = 1; else mapislsb = 0;

	maptype = (int) mdatpt[3];
	if (maptype > 3) { maperror = MER_MAPTOONEW; return -1; }
	mapwidth = (short) MapGetshort (mdatpt+4);
	mapheight = (short) MapGetshort (mdatpt+6);
	mapblockwidth = (short) MapGetshort (mdatpt+12);
	mapblockheight = (short) MapGetshort (mdatpt+14);
	mapdepth = (short) MapGetshort (mdatpt+16);
	mapaltdepth = mapdepth;
	mapblockstrsize = (short) MapGetshort (mdatpt+18);
	mapnumblockstr = (short) MapGetshort (mdatpt+20);
	mapnumblockgfx = (short) MapGetshort (mdatpt+22);

	if (MapGetchksz (mdatpt-4) > 24) {
		maptrans8 = (int) mdatpt[24];
		maptransred = (int) mdatpt[25];
		maptransgreen = (int) mdatpt[26];
		maptransblue = (int) mdatpt[27];
	}

	if (MapGetchksz (mdatpt-4) > 28) {
		mapblockgapx = (int) MapGetshort (mdatpt+28);
		mapblockgapy = (int) MapGetshort (mdatpt+30);
		mapblockstaggerx = (int) MapGetshort (mdatpt+32);
		mapblockstaggery = (int) MapGetshort (mdatpt+34);
	} else {
		mapblockgapx = (int) mapblockwidth;
		mapblockgapy = (int) mapblockheight;
		mapblockstaggerx = 0;
		mapblockstaggery = 0;
	}
	if (MapGetchksz (mdatpt-4) > 36) mapclickmask = (short) MapGetshort (mdatpt+36);
	else mapclickmask = 0;

	return 0;
}

/*
int DecodeEDHD (unsigned char * mdatpt)
{
int i, j;
short int * mybrshpt;
char * mynamept;
short int * mybrsh2pt;

	mdatpt += 8;
	xmapoffset = (short) MapGetshort (mdatpt);
	ymapoffset = (short) MapGetshort (mdatpt+2);
	fgcolour = (int) MapGetlong (mdatpt+4);
	bgcolour = (int) MapGetlong (mdatpt+8);
	swidth = (short) MapGetshort (mdatpt+12);
	sheight = (short) MapGetshort (mdatpt+14);
	strtstr = (short) MapGetshort (mdatpt+16);
	strtblk = (short) MapGetshort (mdatpt+18);
	curstr = (short) MapGetshort (mdatpt+20);
	curanim = (short) MapGetshort (mdatpt+22); curanim = -1;
	animspd = (short) MapGetshort (mdatpt+24);
	span = (short) MapGetshort (mdatpt+26);
	numbrushes = (short) MapGetshort (mdatpt+28);
	if (clickmask == 0) {
		clickmask = (int) MapGetshort (mdatpt+30);
		if (clickmask<0 || clickmask >= numblockgfx) clickmask = 0;
	}

	if (numbrushes>0)
	{
	mybrshpt =(short int *) (mdatpt+32);
		for (i=0;i<8;i++)
		{
			j = *mybrshpt; j *= *(mybrshpt+1); j *= 2; j += 4;
			brshpt[i] = malloc (j); j /= 2; mybrsh2pt = brshpt[i];
			*mybrsh2pt = *mybrshpt;
			mybrsh2pt++; mybrshpt++;
			*mybrsh2pt = *mybrshpt;
			mybrsh2pt++; mybrshpt++;
			j -= 2;
			if (maptype == 0) {
				while (j) {
					j--;
					*mybrsh2pt = *mybrshpt;
					if (*mybrsh2pt >= 0) *mybrsh2pt /= BLOCKSTRSIZE;
					mybrsh2pt++; mybrshpt++;
				}
			} else {
				while (j) {
					j--;
					*mybrsh2pt = *mybrshpt;
					if (*mybrsh2pt < 0) *mybrsh2pt *= sizeof(ANISTR);
					mybrsh2pt++; mybrshpt++;
				}
			}
			numbrushes--; if (!numbrushes) i=8;
		}
	mynamept = (char *) mybrshpt;
	if ((MapGetchksz (mdatpt-4)) > (mynamept-((char *) mdatpt))) {
		for (i=0;i<8;i++) {
			if (brshpt[i] != NULL) {
				strcpy (brshname[i], mynamept);
				mynamept += strlen (mynamept);
				mynamept++;
			}
		}
	}
	}

	return 0;
}

int DecodeATHR (unsigned char * mdatpt)
{
int i, j;

	mdatpt += 8;
	i = 0; while (i < MapGetchksz (mdatpt-4))
	{
		authorname[i]=mdatpt[i];
		if (mdatpt[i]==0) break;
		i++;
	}
	i++; j = 0;
	while (i < MapGetchksz (mdatpt-4))
	{
		authorinfo1[j]=mdatpt[i];
		if (mdatpt[i]==0) break;
		i++; j++;
	}
	i++; j = 0;
	while (i < MapGetchksz (mdatpt-4))
	{
		authorinfo2[j]=mdatpt[i];
		if (mdatpt[i]==0) break;
		i++; j++;
	}
	i++; j = 0;
	while (i < MapGetchksz (mdatpt-4))
	{
		authorinfo3[j]=mdatpt[i];
		if (mdatpt[i]==0) break;
		i++; j++;
	}
	return 0;
}
*/

int MapDecodeCMAP (unsigned char * mdatpt)
{
	mdatpt += 8;
	
	int	PaletteCount	= MapGetchksz(mdatpt-4);
	
	mapcmappt = (unsigned char *) malloc(PaletteCount);
	
	ZeroMemory(mapcmappt, PaletteCount);
	
	if (mapcmappt==NULL) { maperror = MER_OUTOFMEM; return -1; }
	memcpy (mapcmappt, mdatpt, MapGetchksz (mdatpt-4));
	return 0;
}

int MapDecodeBKDT (unsigned char * mdatpt)
{
int i, j;
BLKSTR * myblkpt;

	mdatpt += 8;
	mapblockstrpt = (char *) malloc (mapnumblockstr*sizeof(BLKSTR));
	if (mapblockstrpt==NULL) { maperror = MER_OUTOFMEM; return -1; }

	myblkpt = (BLKSTR *) mapblockstrpt;
	j = MapGetchksz (mdatpt-4);
	i = 0; while (i < (mapnumblockstr*mapblockstrsize)) {
		myblkpt->bgoff = MapGetlong (mdatpt+i);
		myblkpt->fgoff = MapGetlong (mdatpt+i+4);
		myblkpt->fgoff2 = MapGetlong (mdatpt+i+8);
		myblkpt->fgoff3 = MapGetlong (mdatpt+i+12);
		if (maptype == 0) {
			myblkpt->bgoff = (myblkpt->bgoff) / (mapblockwidth*mapblockheight*((mapdepth+1)/8));
			myblkpt->fgoff = (myblkpt->fgoff) / (mapblockwidth*mapblockheight*((mapdepth+1)/8));
			myblkpt->fgoff2 = (myblkpt->fgoff2) / (mapblockwidth*mapblockheight*((mapdepth+1)/8));
			myblkpt->fgoff3 = (myblkpt->fgoff3) / (mapblockwidth*mapblockheight*((mapdepth+1)/8));
		}
		myblkpt->user1 = (unsigned int) MapGetlong (mdatpt+i+16);
		myblkpt->user2 = (unsigned int) MapGetlong (mdatpt+i+20);
		myblkpt->user3 = (unsigned short int) MapGetshort (mdatpt+i+24);
		myblkpt->user4 = (unsigned short int) MapGetshort (mdatpt+i+26);
		myblkpt->user5 = mdatpt[i+28];
		myblkpt->user6 = mdatpt[i+29];
		myblkpt->user7 = mdatpt[i+30];
		if (mdatpt[i+31]&0x80) myblkpt->unused3 = 1; else myblkpt->unused3 = 0;
		if (mdatpt[i+31]&0x40) myblkpt->unused2 = 1; else myblkpt->unused2 = 0;
		if (mdatpt[i+31]&0x20) myblkpt->unused1 = 1; else myblkpt->unused1 = 0;
		if (mdatpt[i+31]&0x10) myblkpt->trigger = 1; else myblkpt->trigger = 0;
		if (mdatpt[i+31]&0x08) myblkpt->br = 1; else myblkpt->br = 0;
		if (mdatpt[i+31]&0x04) myblkpt->bl = 1; else myblkpt->bl = 0;
		if (mdatpt[i+31]&0x02) myblkpt->tr = 1; else myblkpt->tr = 0;
		if (mdatpt[i+31]&0x01) myblkpt->tl = 1; else myblkpt->tl = 0;
		i += mapblockstrsize;
		myblkpt++;
	}
	return 0;
}

int MapDecodeANDT (unsigned char * mdatpt)
{
int numani, i, ancksz;
unsigned char * mdatendpt;

	mdatpt += 8;
	ancksz = MapGetchksz(mdatpt-4);
	mdatendpt = mdatpt+ancksz;

	numani = 0; while (1) {
		mdatendpt -= 16;
		numani++;
		if (*mdatendpt == 255) break;
	}

	mapanimseqpt = (int *) malloc (((mdatendpt-mdatpt)/4)*sizeof(int));
	if (mapanimseqpt == NULL) { maperror = MER_OUTOFMEM; return -1; }
	i = 0; while (mdatpt != mdatendpt) {
		mapanimseqpt[i] = MapGetlong (mdatpt);
		if (maptype == 0) mapanimseqpt[i] /= mapblockstrsize;
		mdatpt += 4; i++;
	}

	mapanimstrpt = (ANISTR *) malloc (numani*sizeof(ANISTR));
	if (mapanimstrpt == NULL) { maperror = MER_OUTOFMEM; return -1; }
	mapanimstrendpt = mapanimstrpt;
	mapanimstrendpt += numani;

	i = 0; while (i<numani) {
		mapanimstrpt[i].antype = mdatendpt[0];
		mapanimstrpt[i].andelay = mdatendpt[1];
		mapanimstrpt[i].ancount = mdatendpt[2];
		mapanimstrpt[i].anuser = mdatendpt[3];
		if (maptype == 0) {
			mapanimstrpt[i].ancuroff = (int) ((MapGetlong (mdatendpt+4)+ancksz)/4);
			mapanimstrpt[i].anstartoff = (int) ((MapGetlong (mdatendpt+8)+ancksz)/4);
			mapanimstrpt[i].anendoff = (int) ((MapGetlong (mdatendpt+12)+ancksz)/4);
		} else {
			mapanimstrpt[i].ancuroff = (int) MapGetlong (mdatendpt+4);
			mapanimstrpt[i].anstartoff = (int) MapGetlong (mdatendpt+8);
			mapanimstrpt[i].anendoff = (int) MapGetlong (mdatendpt+12);
		}
		mdatendpt += 16; i++;
	}

	MapInitAnims ();
	return 0;
}

int MapDecodeAGFX (unsigned char * mdatpt)
{
//	if (bitmap_color_depth (screen) > 8) return 0;
//	if (mapblockgfxpt != NULL) free (mapblockgfxpt);
	mapaltblockgfxpt = (char *) malloc(MapGetchksz (mdatpt+4));
	if (mapaltblockgfxpt==NULL) { maperror = MER_OUTOFMEM; return -1; }
	memcpy (mapaltblockgfxpt, mdatpt+8, MapGetchksz(mdatpt+4));
	mapaltdepth = 8;
	return 0;
}

int MapDecodeBGFX (unsigned char * mdatpt)
{
	mdatpt += 8;

	mapblockgfxpt = (BYTE *)malloc(mapnumblockgfx * mapblockwidth * mapblockheight * 4);
	if (mapblockgfxpt==NULL) { maperror = MER_OUTOFMEM; return -1; }

	memset(mapblockgfxpt, 0, mapnumblockgfx * mapblockwidth * mapblockheight * 4);

	BYTE*	pBlocks	= mapblockgfxpt;
	
	for (int i=0;i<mapnumblockgfx;i++)
	{
		for (int j=0;j<mapblockheight;j++)
		{
			for (int k=0;k<mapblockwidth;k++)
			{
				switch (mapdepth)
				{
					case 8:
					case 15:
					case 16:
						break;

					case 24:
						pBlocks[0] = mdatpt[0];
						pBlocks[1] = mdatpt[1];
						pBlocks[2] = mdatpt[2];
						
						if (pBlocks[0] == MTRANSPR && pBlocks[1] == MTRANSPG && pBlocks[2] == MTRANSPB)
						{
							pBlocks[3] = 0;
						}
						
						else
						{
							pBlocks[3] = (BYTE)0xFF;
						}
						
						mdatpt += 3;
					
						break;
					
					case 32:
						pBlocks[0] = mdatpt[1];
						pBlocks[1] = mdatpt[2];
						pBlocks[2] = mdatpt[3];
						pBlocks[3] = mdatpt[0];
						mdatpt += 4;
					
						break;
					
					default:
						break;
				}
				
				pBlocks	+= 4;
			}
		}
	}
	
	return	0;
}

int MapDecodeNOVC (unsigned char * mdatpt)
{
	memset (mapnovctext, 0, 70);
	if (MapGetchksz ((unsigned char *) mdatpt+4) < 70) strcpy (mapnovctext, (char *) mdatpt+8);
	return 0;
}

int MapDecodeLayer (unsigned char * mdatpt, int lnum)
{
int i, j, k, l;
short int * mymappt, * mymap2pt;

	mapmappt[lnum] = (short int *) malloc (mapwidth*mapheight*sizeof(short int));
	if (mapmappt[lnum] == NULL) { maperror = MER_OUTOFMEM; return -1; }

	mdatpt += 8;
	mymappt = mapmappt[lnum];
	if (maptype == 0) {
	for (j=0;j<mapheight;j++) {
		for (i=0;i<mapwidth;i++) {
			*mymappt = (short int) MapGetshort (mdatpt);
			if (*mymappt >= 0) { *mymappt /= mapblockstrsize; }
			else { *mymappt /= 16; }
			mdatpt+=2; mymappt++;
		}
	}
	} else {
	if (maptype == 1) {
	for (j=0;j<mapheight;j++) {
		for (i=0;i<mapwidth;i++) {
			*mymappt = (short int) MapGetshort (mdatpt);
			mdatpt+=2; mymappt++;
		}
	}
	} else {
	if (maptype == 2) {
	for (j=0;j<mapheight;j++) {
		for (i=0;i<mapwidth;) {
			k = (int) MapGetshort (mdatpt);
			mdatpt += 2;
			if (k > 0) {
				while (k) {
					*mymappt = (short int) MapGetshort (mdatpt);
					mymappt++; mdatpt += 2;
					i++; k--;
				}
			} else {
			if (k < 0) {
				l = (int) MapGetshort (mdatpt); mdatpt += 2;
				while (k) {
					*mymappt = (short int) l;
					mymappt++;
					i++; k++;
				}
			} else {
			} }
		}
	}
	} else {
	if (maptype == 3) {
	for (j=0;j<mapheight;j++) {
		for (i=0;i<mapwidth;) {
			k = (int) MapGetshort (mdatpt);
			mdatpt += 2;
			if (k > 0) {
				while (k) {
					*mymappt = (short int) MapGetshort (mdatpt);
					mymappt++; mdatpt += 2;
					i++; k--;
				}
			} else {
			if (k < 0) {
				mymap2pt = mymappt + (int) MapGetshort (mdatpt); mdatpt += 2;
				while (k) {
					*mymappt = *mymap2pt;
					mymappt++; mymap2pt++;
					i++; k++;
				}
			} else {
			} }
		}
	}
	} } } }

	if (lnum == 0) { mappt = mapmappt[lnum]; }
	return 0;
}

int MapDecodeNULL (unsigned char * mdatpt)
{
	return 0;
}

int MapRealDecode (FILE * mfpt, unsigned char * mmpt, long int mpfilesize)
{
int chkdn;
unsigned char * fmappospt;
char mphdr[8];

	mpfilesize -= 12;

	while (mpfilesize > 0) {

		if (mfpt != NULL) {
			if (fread (mphdr, 1, 8, mfpt) != 8) {
				maperror = MER_MAPLOADERROR;
				MapFreeMem ();
				return -1;
			}
			fmappospt = (unsigned char *) malloc (MapGetchksz((unsigned char *) mphdr+4)+8);
			if (fmappospt == NULL) {
				maperror = MER_OUTOFMEM;
				MapFreeMem ();
				return -1;
			}
			memcpy (fmappospt, mphdr, 8);
			if (fread (fmappospt+8, 1, MapGetchksz((unsigned char *) mphdr+4),
				mfpt) != (unsigned int) MapGetchksz((unsigned char *) mphdr+4)) {
				maperror = MER_MAPLOADERROR;
				MapFreeMem ();
				return -1;
			}
		} else {
			fmappospt = mmpt;
			mmpt += MapGetchksz(mmpt+4);
			mmpt += 8;
		}

		chkdn = 0;
		if (!strncmp ((char *) fmappospt, "MPHD", 4)) { chkdn = 1; MapDecodeMPHD (fmappospt); }
/*		if (!strncmp ((char *) fmappospt, "ATHR", 4)) { chkdn = 1; MapDecodeATHR (fmappospt); }
		if (!strncmp ((char *) fmappospt, "EDHD", 4)) { chkdn = 1; MapDecodeEDHD (fmappospt); }
*/
		if (!strncmp ((char *) fmappospt, "CMAP", 4)) { chkdn = 1; MapDecodeCMAP (fmappospt); }
		if (!strncmp ((char *) fmappospt, "BKDT", 4)) { chkdn = 1; MapDecodeBKDT (fmappospt); }
		if (!strncmp ((char *) fmappospt, "ANDT", 4)) { chkdn = 1; MapDecodeANDT (fmappospt); }
		if (!strncmp ((char *) fmappospt, "AGFX", 4)) { chkdn = 1; MapDecodeAGFX (fmappospt); }
		if (!strncmp ((char *) fmappospt, "BGFX", 4)) { chkdn = 1; MapDecodeBGFX (fmappospt); }
		if (!strncmp ((char *) fmappospt, "NOVC", 4)) { chkdn = 1; MapDecodeNOVC (fmappospt); }
		if (!strncmp ((char *) fmappospt, "BODY", 4)) { chkdn = 1; MapDecodeLayer (fmappospt, 0); }
		if (!strncmp ((char *) fmappospt, "LYR1", 4)) { chkdn = 1; MapDecodeLayer (fmappospt, 1); }
		if (!strncmp ((char *) fmappospt, "LYR2", 4)) { chkdn = 1; MapDecodeLayer (fmappospt, 2); }
		if (!strncmp ((char *) fmappospt, "LYR3", 4)) { chkdn = 1; MapDecodeLayer (fmappospt, 3); }
		if (!strncmp ((char *) fmappospt, "LYR4", 4)) { chkdn = 1; MapDecodeLayer (fmappospt, 4); }
		if (!strncmp ((char *) fmappospt, "LYR5", 4)) { chkdn = 1; MapDecodeLayer (fmappospt, 5); }
		if (!strncmp ((char *) fmappospt, "LYR6", 4)) { chkdn = 1; MapDecodeLayer (fmappospt, 6); }
		if (!strncmp ((char *) fmappospt, "LYR7", 4)) { chkdn = 1; MapDecodeLayer (fmappospt, 7); }
		if (!chkdn) MapDecodeNULL (fmappospt);

		mpfilesize -= 8;
		mpfilesize -= MapGetchksz (fmappospt+4);
		if (mfpt != NULL) free (fmappospt);

		if (maperror != MER_NONE) { MapFreeMem (); return -1; }
	}

	return	1;
}

int MapLoad(char * mapname)
{
int mretval;
char idtag[4];
unsigned char tempc;
int mapfilesize = 0;

	MapFreeMem ();
	maperror = MER_NONE;

	FILE	*mapfilept = fopen (mapname, "rb");
	
	if (mapfilept==NULL) { maperror = MER_NOOPEN; return -1; }

	maperror = MER_MAPLOADERROR;
	if (fread (&idtag[0], 1, 1, mapfilept) == 1) {
	if (fread (&idtag[1], 1, 1, mapfilept) == 1) {
	if (fread (&idtag[2], 1, 1, mapfilept) == 1) {
	if (fread (&idtag[3], 1, 1, mapfilept) == 1) {
	if (fread (&tempc, 1, 1, mapfilept) == 1) {
	mapfilesize = (((int) tempc)<<24);
	if (fread (&tempc, 1, 1, mapfilept) == 1) {
	mapfilesize |= (((int) tempc)<<16);
	if (fread (&tempc, 1, 1, mapfilept) == 1) {
	mapfilesize |= (((int) tempc)<<8);
	if (fread (&tempc, 1, 1, mapfilept) == 1) {
	mapfilesize |= (((int) tempc));
	mapfilesize += 8;
	if (!strncmp (idtag, "FORM", 4)) {
	if (fread (&idtag[0], 1, 1, mapfilept) == 1) {
	if (fread (&idtag[1], 1, 1, mapfilept) == 1) {
	if (fread (&idtag[2], 1, 1, mapfilept) == 1) {
	if (fread (&idtag[3], 1, 1, mapfilept) == 1) {
	if (!strncmp (idtag, "FMAP", 4)) maperror = MER_NONE;
	} } } } }
	} } } } } } } }

	if (maperror != MER_NONE) { fclose (mapfilept); return -1; }

	mretval = MapRealDecode (mapfilept, NULL, mapfilesize);
	fclose (mapfilept);

	return mretval;
}

int MapDecode(unsigned char * mapmempt)
{
long int maplength;

	MapFreeMem ();
	maperror = MER_NONE;

	if (*mapmempt!='F') maperror = MER_MAPLOADERROR;
	if (*(mapmempt+1)!='O') maperror = MER_MAPLOADERROR;
	if (*(mapmempt+2)!='R') maperror = MER_MAPLOADERROR;
	if (*(mapmempt+3)!='M') maperror = MER_MAPLOADERROR;
	mapmempt += 4;
	maplength = (MapGetchksz (mapmempt))+8;

	if (maperror) return -1;
	mapmempt += 4;

	if (*mapmempt!='F') maperror = MER_MAPLOADERROR;
	if (*(mapmempt+1)!='M') maperror = MER_MAPLOADERROR;
	if (*(mapmempt+2)!='A') maperror = MER_MAPLOADERROR;
	if (*(mapmempt+3)!='P') maperror = MER_MAPLOADERROR;
	mapmempt+=4;

	if (maperror) return -1;
	return MapRealDecode (NULL, mapmempt, maplength);
}
