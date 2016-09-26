#include "MovieVideoLayer.h"
#include "PostureAnalysisScene.h"
#include "DataMager.h"
#include "SerialMager.h"
#include "RecordClass.h"

MovieVideoLayer::MovieVideoLayer()
{

}
MovieVideoLayer::~MovieVideoLayer()
{
	av_free(m_pFrameImageRGB);
	if (!m_VideoList.empty())
	{
		
		for (int i = 0; i < m_VideoList.size();i++)
		{
			av_free(m_VideoList[i]);
		}
		m_VideoList.clear();
		m_VideoIndex = 0;
	}
}
MovieVideoLayer* MovieVideoLayer::create(int Direction)
{
    MovieVideoLayer *pRet = new MovieVideoLayer();
    if (pRet && pRet->init(Direction))
    {
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}
bool MovieVideoLayer::init(int Direction)
{
	if (!CCLayer::init())
    {
        return false;
    }
	printf("≥ı ºªØMovieVideoLayer\n");
	m_Camera = NULL;
	m_ShowIndex = 0;
	m_TransIndex = 0;
	m_IsRecord = false;
	m_Width = 640;
	m_Height = 480;
	m_BitRate = 40000;

	if (Ext_cameraNum == 0)
	{
		return true;
	}
	if(Direction == FRONT)
	{
		m_Camera = m_Camera1;
		sprintf(outFilePath,"Upload/name1.mp4");
	}
	else
	{
		m_Camera = m_Camera2; 
		sprintf(outFilePath,"Upload/name2.mp4");
	}
	for (size_t i = 0; i < Ext_VideoSize * Ext_StepNum; i++)
	{
		unsigned char* FrameData = (unsigned char*)av_malloc(m_Camera->BufferSize);
		m_VideoList.push_back(FrameData);
	}
	
	m_pFrameImageRGB = (unsigned char*)av_malloc(m_Camera->BufferSize);
	this->setRotationX(180);
	CCSprite* beijing2 = CCSprite::create("VideoUI/beijing2.png");
	beijing2->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(beijing2);
	m_pSprite->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(m_pSprite);
	if(Direction == FRONT)
	{
		m_pTihuan = CCMenuItemImage::create(
			"VideoUI/tihuan1.png",
			"VideoUI/tihuan2.png",
			this,
			menu_selector(PostureAnalysisScene::CallbackSwapVideo));
		m_pTihuan->setPosition(ccp(VISIBLEW/2+240,VISIBLEH/2+200));
		m_pTihuan->setRotationX(180);
		m_pTihuan->setVisible(false);
		MyMenu* pMenu = MyMenu::create(m_pTihuan,NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu);
	}

	
    return true;
}
void MovieVideoLayer::update(float dt)
{
	m_ShowIndex = (m_Camera->getBuffIndex() - 1<0) ? m_Camera->m_BufferIndexMax-1 : m_Camera->getBuffIndex() - 1;
	m_FrameImageHead = m_Camera->getBufferByIndex(m_ShowIndex)->FrameHead;
	try
	{
		CameraImageProcess(m_Camera->m_hCamera,
			m_Camera->getBufferByIndex(m_ShowIndex)->FrameData,
			m_pFrameImageRGB,
			&m_FrameImageHead);
	}
	catch (...)
	{
		FILE* CatchMsgFile = fopen("CatchMsgFile.txt", "a");
		fprintf(CatchMsgFile, "CameraImageProssesError!\n");
		fclose(CatchMsgFile);
	}
	m_pTexture->updateVideoWithData(
		m_pFrameImageRGB,
		kTexture2DPixelFormat_RGB888,
		640,
		480,
		CCSize(630, 470));
	m_pSprite->initWithTexture(m_pTexture);
}
void MovieVideoLayer::Record(bool isRecord)
{
	m_IsRecord = isRecord;
	m_IsPlayOver = isRecord;
}
void MovieVideoLayer::TransData()
{
	if (m_TransIndex < 200 || Ext_IsRecordBegin == false)
	{
		return;
	}
	if (m_TransIndex == Ext_VideoSize * Ext_StepNum)
	{
		m_TransIndex = 0;
		m_pTihuan->setVisible(true);
		return;
	}
	for (size_t i = 0; i < Ext_StepNum; i++)
	{
		int curIndex = m_Camera->getBuffIndex() - Ext_VideoSize * Ext_StepNum + m_TransIndex;
		curIndex = curIndex < 0 ? m_Camera->m_BufferIndexMax + curIndex : curIndex;

		m_FrameImageHead = m_Camera->getBufferByIndex(curIndex)->FrameHead;
		CameraImageProcess(m_Camera->m_hCamera,
			m_Camera->getBufferByIndex(curIndex)->FrameData,
			m_pFrameImageRGB,
			&m_FrameImageHead);
		swap(m_pFrameImageRGB, m_VideoList[m_TransIndex]);
		m_TransIndex ++;
	}
}
void MovieVideoLayer::RecordOk()
{
	int curIndex = 0;
	m_TransIndex = 0;
	this->Record(false);
	m_pTihuan->setVisible(false);
	for (size_t i = 0; i < Ext_VideoSize * Ext_StepNum; i ++)
	{
		if (i == m_TransIndex+200)
		{
			m_TransIndex = i;
			break;
		}
		curIndex = m_Camera->getBuffIndex() - Ext_VideoSize * Ext_StepNum + i;
		curIndex = curIndex < 0 ? m_Camera->m_BufferIndexMax + curIndex : curIndex;
		m_FrameImageHead = m_Camera->getBufferByIndex(curIndex)->FrameHead;
		try
		{
			CameraImageProcess(m_Camera->m_hCamera,
				m_Camera->getBufferByIndex(curIndex)->FrameData,
				m_pFrameImageRGB,
				&m_FrameImageHead);
			swap(m_pFrameImageRGB, m_VideoList[i]);
		}
		catch (...)
		{
			FILE* CatchMsgFile = fopen("CatchMsgFile.txt", "a");
			fprintf(CatchMsgFile, "CameraImageProssesError!\n");
			fclose(CatchMsgFile);
		}
	}
	m_VideoIndex = 0;
}
void MovieVideoLayer::ResetVideoSize()
{
	int curVideoSize = m_VideoList.size();
	if (curVideoSize> Ext_VideoSize * Ext_StepNum)
	{
		curVideoSize = m_VideoList.size();
		for (size_t i = 0; i < curVideoSize - Ext_VideoSize * Ext_StepNum; i++)
		{
			av_free(m_VideoList.back());
			m_VideoList.pop_back();
		}
	}
	if (curVideoSize< Ext_VideoSize * Ext_StepNum)
	{
		for (size_t i = 0; i < Ext_VideoSize * Ext_StepNum - curVideoSize; i++)
		{
			unsigned char* FrameData = (unsigned char*)av_malloc(MovieVideoLayer::m_Camera1->BufferSize);
			m_VideoList.push_back(FrameData);
		}
	}
}