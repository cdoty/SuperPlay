#include <TinySTL/stddef.h>

#include "ISpriteBatch.h"
#include "ShadowOAM.h"

NAMESPACE(SPlay)

ShadowOAM::ShadowOAM()	:
	m_pShadowObjs(NULL),
	m_pHead(NULL)
{
}

ShadowOAM::~ShadowOAM()
{
	close();
}

ShadowOAM* ShadowOAM::create()
{
	ShadowOAM*	pShadowOAM	= new ShadowOAM();

	if (false == pShadowOAM->initialize())
	{
		delete	pShadowOAM;

		pShadowOAM	= NULL;
	}

	return	pShadowOAM;
}

bool ShadowOAM::initialize()
{
	m_pShadowObjs	= new ShadowObj[gsc_iMaxObjs];

	m_pHead	= m_pShadowObjs[0];

	return	super::initialize();
}

void ShadowOAM::close()
{
	delete[]	m_pShadowObjs;
}

void ShadowOAM::render(int _iLayer)
{
	m_pSpriteBatch->startBatch();
	
	float	fZ			= 0.0f;
	float	fZIncrement	= 1.0f / static_cast<float>(gsc_iMaxObjs);

	ShadowObj*	pNode	= m_pHead;

	while (pNode != NULL)
	{
		m_pObjs[pNode->iIndex].render(m_pSpriteBatch, _iLayer, fZ);

		fZ	+= fZIncrement;

		pNode	= pNode->pNext;
	}

	m_pSpriteBatch->endBatch();
}

void ShadowOAM::clearObjs()
{
	super::clearObjs();
}
		 		
int ShadowOAM::getAvailableObject()
{
	return	-1;
}

ENDNAMESPACE
