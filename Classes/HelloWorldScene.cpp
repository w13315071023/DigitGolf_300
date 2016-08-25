#include "HelloWorldScene.h"
#include "PostureAnalysisScene.h"
#include "DataMager.h"
#include "SerialMager.h"
#include "SettingScene.h"
//#include "GolfXIMager.h"
#include "MovieVideoLayer.h"
#include "RecordClass.h"
#include "MyMenu.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
	printf("��ʼ��HelloWorld\n");
    {//��ʼ����Ա����
		m_curCueType = CUETYPE_TIEGAN;
		m_curGender = GENDER_MAN;
		m_isBeginButtonOn = false;
		m_isEndButtonOn = false;
		
        m_pCueTtpeArr[0] = CCMenuItemImage::create(
										"HomeUI/yihaomu.png",
										"HomeUI/yihaomuon.png",
										"HomeUI/yihaomuon.png",
                                        this,
										menu_selector(HelloWorld::menuCueTtpeCallback));
        m_pCueTtpeArr[1] = CCMenuItemImage::create(
										"HomeUI/mugan.png",
										"HomeUI/muganon.png",
										"HomeUI/muganon.png",
                                        this,
										menu_selector(HelloWorld::menuCueTtpeCallback));
        m_pCueTtpeArr[2] = CCMenuItemImage::create(
										"HomeUI/tiegan.png",
										"HomeUI/tieganon.png",
										"HomeUI/tieganon.png",
                                        this,
										menu_selector(HelloWorld::menuCueTtpeCallback));
        m_pCueTtpeArr[3] = CCMenuItemImage::create(
										"HomeUI/waqigan.png",
										"HomeUI/waqiganon.png",
										"HomeUI/waqiganon.png",
                                        this,
										menu_selector(HelloWorld::menuCueTtpeCallback));

        m_pGenderArr[0] = CCMenuItemImage::create(
										"HomeUI/nan.png",
										"HomeUI/nanon.png",
										"HomeUI/nanon.png",
                                        this,
										menu_selector(HelloWorld::menuGenderCallback));
        m_pGenderArr[1] = CCMenuItemImage::create(
										"HomeUI/nv.png",
										"HomeUI/nvon.png",
										"HomeUI/nvon.png",
                                        this,
										menu_selector(HelloWorld::menuGenderCallback));
    }
    //�����ؼ�
	CCSprite* pBackGround = CCSprite::create("HomeUI/Bg.png");

	CCMenuItemImage* pBeginItem = CCMenuItemImage::create(
									"HomeUI/jinruxitong1.png",
									"HomeUI/jinruxitong2.png",
									this,
									menu_selector(HelloWorld::menuCallback));
	CCMenuItemImage* pEndItem = CCMenuItemImage::create(
									"HomeUI/tuichuxitong1.png",
									"HomeUI/tuichuxitong2.png",
									this,
									menu_selector(HelloWorld::menuEndCallback));
    CCSprite* pSprite1 = CCSprite::create("HomeUI/bianyuanguang.png");
    CCSprite* pSprite2 = CCSprite::create("HomeUI/bianyuanguang.png");
    //Ϊ�ؼ�����λ��
	pBackGround->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));

	pBeginItem->setPosition(ccp(VISIBLEW / 2 - 400, 130));
	pEndItem->setPosition(ccp(VISIBLEW / 2 + 400, 130));

	m_pCueTtpeArr[0]->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 + 300));
	m_pCueTtpeArr[1]->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 + 170));
	m_pCueTtpeArr[2]->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 + 40));
	m_pCueTtpeArr[3]->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 - 90));
	m_pGenderArr[0]->setPosition(ccp(VISIBLEW / 2 + 350, VISIBLEH*0.59));
	m_pGenderArr[1]->setPosition(ccp(VISIBLEW / 2 + 350, VISIBLEH*0.42));

	pSprite1->setPosition(ccp(VISIBLEW / 2 - 350, VISIBLEH*0.4 + 40));
	m_pCueTtpeArr[2]->setEnabled(false);
	pSprite2->setPosition(ccp(VISIBLEW / 2 + 350, VISIBLEH*0.59));
	m_pGenderArr[0]->setEnabled(false);
    //���ÿؼ���ǩ
    pSprite1->setTag(1);
    pSprite2->setTag(2);
    m_pCueTtpeArr[0]->setTag(CUETYPE_YIHAOMU);
    m_pCueTtpeArr[1]->setTag(CUETYPE_MUGAN);
    m_pCueTtpeArr[2]->setTag(CUETYPE_TIEGAN);
    m_pCueTtpeArr[3]->setTag(CUETYPE_WAQIGAN);
    m_pGenderArr[0]->setTag(GENDER_MAN);
    m_pGenderArr[1]->setTag(GENDER_WOMAN);
    //���ؼ���ӵ���Ⱦ��
	this->addChild(pBackGround);
    this->addChild(pSprite1);
    this->addChild(pSprite2);
    //������ť�㲢��Ӱ�ť
	CCMenuItemImage* pSetting = CCMenuItemImage::create(
		"HomeUI/shezhi1.png",
		"HomeUI/shezhi2.png",
		this,
		menu_selector(HelloWorld::menuSettingCallback));
	pSetting->setPosition(ccp(VISIBLEW/2,130));
	MyMenu* pMenu = MyMenu::create(
								m_pCueTtpeArr[0],
								m_pCueTtpeArr[1],
								m_pCueTtpeArr[2],
								m_pCueTtpeArr[3],
								m_pGenderArr[0],
								m_pGenderArr[1],
								pBeginItem,
								pEndItem,
								pSetting,NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	this->scheduleUpdate();
    return true;
}
//��ť�Ļص�����
void HelloWorld::menuCallback(CCObject* pSender)
{
	if (m_isBeginButtonOn)
	{
		return;
	}
	m_isBeginButtonOn = true;
	printf("����ϵͳ\n");
	Ext_IsResetGG = true;
	DataMager::shareDataMager()->m_curCuetype = this->m_curCueType;
	DataMager::shareDataMager()->m_curGender = this->m_curGender;
	DataMager::shareDataMager()->SaveData();
	//ת�����Ʒ�������
	SerialMager::getInstence()->setThreshold(Ext_SerialThreshold);
	//GolfXIMager::getInstence()->setClubType(140);

	if (MovieVideoLayer::m_Camera1)
	{
		MovieVideoLayer::m_Camera1->setExposureTime(Ext_VideoExposureTime);
		MovieVideoLayer::m_Camera1->setGain(Ext_VideoGain);
	}
	if (MovieVideoLayer::m_Camera2)
	{
		MovieVideoLayer::m_Camera2->setExposureTime(Ext_VideoExposureTime);
		MovieVideoLayer::m_Camera2->setGain(Ext_VideoGain);
	}
	printf("ת�����Ʒ�������\n");
	CCDirector::sharedDirector()->replaceScene(PostureAnalysisScene::CreateScene());
}
void HelloWorld::menuEndCallback(CCObject* pSender)
{
	if (m_isEndButtonOn || m_isBeginButtonOn)
	{
		return;
	}
	Ext_IsTurnEnd = true;
	if (MovieVideoLayer::m_Camera1)
	{
		MovieVideoLayer::m_Camera1->Destructor();
	}
	if (MovieVideoLayer::m_Camera2)
	{
		MovieVideoLayer::m_Camera2->Destructor();
	}
	if (PostureAnalysisScene::m_pFrontMovieVideoLayer)
	{
		delete PostureAnalysisScene::m_pFrontMovieVideoLayer;
		PostureAnalysisScene::m_pFrontMovieVideoLayer = NULL;
	}
	if (PostureAnalysisScene::m_pSideMovieVideoLayer)
	{
		delete PostureAnalysisScene::m_pSideMovieVideoLayer;
		PostureAnalysisScene::m_pSideMovieVideoLayer = NULL;
	}
	SerialMager::getInstence()->unLoadInstence();
	CCDirector::sharedDirector()->end();
}
void HelloWorld::menuSettingCallback(CCObject* pSender)
{
	Ext_IsResetGG = true;
	CCDirector::sharedDirector()->pushScene(SettingScene::getScene());
}
//����Ĵ����¼�
void HelloWorld::menuCueTtpeCallback(CCObject* pSender)
{
	Ext_IsResetGG = true;
	//��ȡ��ʶ�ؼ�
	CCNode* pNode1 = this->getChildByTag(1);
	

	for (int i = 0; i < 4; i++)
	{
		m_pCueTtpeArr[i]->setEnabled(true);
		//�ж���û�е�������
		if (m_pCueTtpeArr[i] == pSender)
		{
			//��¼ѡ������
			m_curCueType = (CUETYPE)m_pCueTtpeArr[i]->getTag();
			instenceTarget = m_pCueTtpeArr[i]->getTag();
			//����ʶ�ؼ��ƶ���ѡ���ǩǰ
			pNode1->setPosition(ccp(
				m_pCueTtpeArr[i]->getPosition().x,
				m_pCueTtpeArr[i]->getPosition().y));
			m_pCueTtpeArr[i]->setEnabled(false);
		}
	}
}
void HelloWorld::menuGenderCallback(CCObject* pSender)
{
	Ext_IsResetGG = true;
	CCNode* pNode1 = this->getChildByTag(2);

    for(int i = 0;i < 2;i++)
    {
		m_pGenderArr[i]->setEnabled(true);
        //�ж���û�е�����Ա�
        if(m_pGenderArr[i] == pSender)
        {
            //��¼ѡ����Ա�
            m_curGender = (GENDER)m_pGenderArr[i]->getTag();
            //����ʶ�ؼ��ƶ���ѡ���ǩǰ
			pNode1->setPosition(ccp(
                m_pGenderArr[i]->getPosition().x,
                m_pGenderArr[i]->getPosition().y));
			m_pGenderArr[i]->setEnabled(false);
        }
    }
}
void HelloWorld::update(float dt)
{
	if (!SerialMager::getInstence()->getComPort())
	{
		CCMessageBox("������С����","���棡");
		menuEndCallback(NULL);
	}
}