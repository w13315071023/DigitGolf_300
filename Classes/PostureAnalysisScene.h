#pragma once
#include "cocos2d.h"
#include "Tools.h"
#include "DrawingLayer.h"
#include "HelloWorldScene.h"
#include "DemoVideoLayer.h"
#include "MovieVideoLayer.h"
#include "DataAnalysisScene.h"
#include "SerialMager.h"
#include "MyMenu.h"

USING_NS_CC;
class DemoVideoLayer;
class DrawingLayer;
class PostureAnalysisScene:public CCLayer
{
public:
    MENUTAG m_curMenuTag;
    static MovieVideoLayer* m_pFrontMovieVideoLayer;
	static MovieVideoLayer* m_pSideMovieVideoLayer;
	static DemoVideoLayer* m_pFrontDemoVideoLayer;
	static DemoVideoLayer* m_pSideDemoVideoLayer;
	CCSprite* m_pReadyLabel;
	CCSprite* m_pReadyImage;
	CCMenuItemImage* m_pREWItem;
	CCMenuItemImage* m_pFFItem;
	CCMenuItemImage* m_pRePlayItem;
	CCMenuItemImage* m_pPreview;
	CCMenuItemImage* m_pDanjian;
	CCMenuItemImage* m_pXunhuan;
	CCMenuItemToggle* m_pSpeedItem;
	CCMenuItemToggle* m_pPauseItemToggle;

	CCMenuItemImage* m_pFourViewItem;
	CCMenuItemToggle* m_pFrontViewItem;
	CCMenuItemToggle* m_pSideViewItem;
	CCMenuItemImage* m_pFrontAndSideViewItem;
	CCMenuItemImage* m_pFrontViewItem2;
	CCMenuItemImage* m_pFrontDemoViewItem;
	MyMenu* m_pMenu;
	float m_curSingle;
	unsigned int m_curMsg;

	static DrawingLayer* m_pDrawingLayer;
	static bool m_bIsPlayVideo;
	static bool m_bIsTurnCamera;
	bool m_bIsStepPlay;
	bool m_bIsVisibleMenu;
	bool m_bSetMode;
    //�滭��
    //DrawingLayer* m_pDLayer;
public:
    
    PostureAnalysisScene(void);
    ~PostureAnalysisScene(void);

    //�����Ĵ�������
    static CCScene* CreateScene();
    //����Ĵ�������
    CREATE_FUNC(PostureAnalysisScene);
    //��ʼ������
    bool init();
	void Update(float dt);
    //��ť�Ļص�����
    void menuCallback(CCObject* pSender);
    //void visit();
    void CallbackREW(CCObject* pSender);
    void CallbackFF(CCObject* pSender);
    void CallbackRePlay(CCObject* pSender);
    void CallbackSpeed(CCObject* pSender);
    void CallbackPause(CCObject* pSender);
	void CallbackPreview(CCObject* pSender);
	void CallbackSetMode(CCObject* pSender);
	void CallbackUpload(CCObject* pSender);
};

