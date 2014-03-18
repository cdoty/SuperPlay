#pragma once

#include "File.h"

#ifndef YSRESULT_IS_DEFINED
#define YSERR 0
#define YSOK 1
#endif

#ifndef YSBOOL_IS_DEFINED
#define YSBOOL_IS_DEFINED
#define YSFALSE 0
#define YSTRUE  1
#endif



class YsPngHuffmanTree
{
public:
	YsPngHuffmanTree();
	~YsPngHuffmanTree();
	YsPngHuffmanTree *zero,*one;
	unsigned int dat;
	unsigned int weight,depth;
	static int leakTracker;

	static void DeleteHuffmanTree(YsPngHuffmanTree *node);
};

class YsPngUncompressor
{
public:
	class YsGenericPngDecoder *output;

	inline unsigned int GetNextBit(const unsigned char* dat,unsigned &bytePtr,unsigned &bitPtr)
	{
		unsigned a;
		a=dat[bytePtr]&bitPtr;
		bitPtr<<=1;
		if(bitPtr>=256)
		{
			bitPtr=1;
			bytePtr++;
		}
		return (a!=0 ? 1 : 0);
	}
	inline unsigned int GetNextMultiBit(const unsigned char* dat,unsigned &bytePtr,unsigned &bitPtr,unsigned n)
	{
		unsigned value,mask,i;
		value=0;
		mask=1;
		for(i=0; i<n; i++)
		{
			if(GetNextBit(dat,bytePtr,bitPtr))
			{
				value|=mask;
			}
			mask<<=1;
		}
		return value;
	}

	void MakeFixedHuffmanCode(unsigned hLength[288],unsigned hCode[288]);
	static void MakeDynamicHuffmanCode(unsigned hLength[288],unsigned hCode[288],unsigned nLng,unsigned* lng);
	int DecodeDynamicHuffmanCode
	   (unsigned int &hLit,unsigned int &hDist,unsigned int &hCLen,
	    unsigned int *&hLengthLiteral,unsigned int *&hCodeLiteral,
	    unsigned int *&hLengthDist,unsigned int *&hCodeDist,
	    unsigned int hLengthBuf[322],unsigned int hCodeBuf[322],
	    const unsigned char* dat,unsigned int &bytePtr,unsigned int &bitPtr);

	YsPngHuffmanTree *MakeHuffmanTree(unsigned n,unsigned* hLength,unsigned* hCode);
	void DeleteHuffmanTree(YsPngHuffmanTree *node);

	unsigned GetCopyLength(unsigned value,unsigned char* dat,unsigned &bytePtr,unsigned &bitPtr);
	unsigned GetBackwardDistance(unsigned distCode,unsigned char* dat,unsigned &bytePtr,unsigned &bitPtr);

	int Uncompress(unsigned length,unsigned char* dat);
};

////////////////////////////////////////////////////////////

class YsPngHeader
{
public:
	unsigned int width,height;
	unsigned int bitDepth,colorType;
	unsigned int compressionMethod,filterMethod,interlaceMethod;

	void Decode(unsigned char* dat);
};

class YsPngPalette
{
public:
	unsigned int nEntry;
	unsigned char *entry;

	YsPngPalette();
	~YsPngPalette();
	int Decode(unsigned length,unsigned char* dat);
};

class YsPngTransparency
{
public:
	unsigned int col[3];

	// For color type 3, up to three transparent colors is supported.
	int Decode(unsigned length,unsigned char* dat,unsigned int colorType);
};

class YsGenericPngDecoder
{
public:
	enum
	{
		gamma_default=100000
	};

	YsPngHeader hdr;
	YsPngPalette plt;
	YsPngTransparency trns;
	unsigned int gamma;

	YsGenericPngDecoder();
	virtual ~YsGenericPngDecoder() {}
	void Initialize(void);
	int CheckSignature(SPlay::File *fp);
	int ReadChunk(unsigned &length,unsigned char *&buf,unsigned &chunkType,unsigned &crc,SPlay::File *fp);
	int Decode(const char* fn);

	virtual int PrepareOutput(void);
	virtual int Output(unsigned char dat);
	virtual int EndOutput(void);
};



////////////////////////////////////////////////////////////


class YsRawPngDecoder : public YsGenericPngDecoder
{
public:
	YsRawPngDecoder();
	virtual ~YsRawPngDecoder();


	int wid,hei;
	unsigned char *rgba;  // Raw data of R,G,B,A
	unsigned char *indexed;  // Raw indexed color data
	int autoDeleteRgbaBuffer;


	int filter,x,y,firstByte;
	int inLineCount;
	int inPixelCount;
	unsigned int r,g,b,msb;  // msb for reading 16 bit depth
	unsigned int index;

	unsigned int interlacePass;

	// For filtering
	unsigned char *twoLineBuf8,*curLine8,*prvLine8;

	void ShiftTwoLineBuf(void);

	virtual int PrepareOutput(void);
	virtual int Output(unsigned char dat);
	virtual int EndOutput(void);

	void Flip(void);  // For drawing in OpenGL
};
