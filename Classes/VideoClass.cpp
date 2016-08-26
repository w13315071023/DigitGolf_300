#include "VideoClass.h"


VideoClass::VideoClass(void)
{
	m_Width = 640;
	m_Height = 480;
	m_IsPlayOver = true;
	m_pTexture = new CCTexture2D();
	m_pSprite = new CCSprite();
	m_pTexture->initWithData(
		NULL,
		kTexture2DPixelFormat_RGB888,
		0,
		0,
		CCSize(640, 480));
	m_pSprite->initWithTexture(m_pTexture);
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(ccp(0.5,0.5));
}


VideoClass::~VideoClass(void)
{
	m_pTexture->release();
}
void VideoClass::ShowVideo()
{
	if (m_VideoList.empty())
	{
		m_IsPlayOver = true;
		return;
	}
	if (m_VideoIndex < m_VideoList.size())
	{
		if(m_VideoIndex < 0)
		{
			m_VideoIndex = 0;
		}
		m_pTexture->updateVideoWithData(
			m_VideoList[m_VideoIndex],
			kTexture2DPixelFormat_RGB888,
			m_Width,
			m_Height,
			CCSize(630, 470));
		m_pSprite->initWithTexture(m_pTexture);
		//m_VideoIter += Ext_StepNum;
		m_VideoIndex ++;
	}
	else
	{
		m_IsPlayOver = true;
		m_VideoIndex = 0;
	}
}
void VideoClass::ReSetVideo()
{
	m_VideoIndex = 0;
	ShowVideo();
}