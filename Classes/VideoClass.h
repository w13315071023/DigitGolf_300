#pragma once
#include "Tools.h"

class VideoClass :public CCLayer
{
public:
	CCTexture2D* m_pTexture;
	CCSprite* m_pSprite;
	bool m_IsPlayOver;
	bool m_IsRecord;
	float m_Width;
	float m_Height;
	vector<unsigned char*> m_DemoVideoList;
	vector<unsigned char*>::iterator m_DemoVideoIter;
	vector<VideoRAW*> m_VideoList;
	vector<VideoRAW*>::iterator m_VideoIter;
public:
	VideoClass(void);
	virtual ~VideoClass(void);
	void ShowVideo();
	void ShowDemoVideo();
	void ReSetDemoVideo();
	void ReSetVideo();
};

