#include "DataAnalysisScene.h"
#include "DrawingLayer.h"
#include "PostureAnalysisScene.h"
#include "HelloWorldScene.h"
#include "TargetLayer.h"
#include "ParabolicLayer.h"
#include "GroundLayer.h"
#include "DataShowLayer.h"
#include "DataMager.h"
#include "DataView.h"

DrawingLayer* DataAnalysisScene::m_pDrawingLayer2 = NULL;
DataAnalysisScene::DataAnalysisScene(void)
{
}
DataAnalysisScene::~DataAnalysisScene(void)
{
}
//�����Ĵ�������
CCScene* DataAnalysisScene::CreateScene()
{
    //����һ������
    CCScene* scene = CCScene::create();
    //������
    DataAnalysisScene* player = DataAnalysisScene::create();
    scene->addChild(player,1);
    return scene;
}
//��ʼ������
bool DataAnalysisScene::init()
{
	if (!CCLayer::init())
    {
        return false;
    }
	m_pDataView = NULL;
	CCSprite* pBackGround = CCSprite::create("DataUI/Bg.png");
	pBackGround->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(pBackGround);
    {//��ʼ����Ա����
        m_pGroundLayer = GroundLayer::create();
        m_pParabolicLayer = ParabolicLayer::create();
        m_pTargetLayer = TargetLayer::create();
        m_pDataShowLayer = DataShowLayer::create();
    }
    //�����ؼ�
	CCMenuItemImage* m_pMenuItem = CCMenuItemImage::create(
		"DataUI/fanhuizhuye1.png",
		"DataUI/fanhuizhuye2.png",
		this,
		menu_selector(DataAnalysisScene::menuCallback));
	CCMenuItemImage* m_pPostureAnalysisItem = CCMenuItemImage::create(
		"DataUI/zishifenxi1.png",
		"DataUI/zishifenxi2.png",
		this,
		menu_selector(DataAnalysisScene::menuCallback));

    //���ÿؼ�ê��
	m_pTargetLayer->setAnchorPoint(ccp(0.5,0.5));
	m_pParabolicLayer->setAnchorPoint(ccp(0,0));
	m_pGroundLayer->setAnchorPoint(ccp(0,0));
    //���ÿؼ�λ��
	m_pTargetLayer->setPosition(ccp(1326, 397));
	m_pGroundLayer->setPosition(ccp(374, 252));
	m_pParabolicLayer->setPosition(ccp(986, 576));
	m_pDataShowLayer->setPosition(ccp(978, 108));
	m_pMenuItem->setPosition(ccp(170,818));
	m_pPostureAnalysisItem->setPosition(ccp(170, 924));
    //���ð�ť��ǩ
    m_pMenuItem->setTag(MENUTAG_Back);
    m_pPostureAnalysisItem->setTag(MENUTAG_PostureAnalysis);
    //���ؼ��������Ⱦ��
    this->addChild(m_pGroundLayer);
    this->addChild(m_pParabolicLayer);
    this->addChild(m_pTargetLayer);
    this->addChild(m_pDataShowLayer);
    //���ð�ť��
    CCMenu* pMenu = CCMenu::create(
                                m_pMenuItem,
                                m_pPostureAnalysisItem,
                                NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

	if(DataMager::shareDataMager()->m_GolfDataMap.empty())
	{
		return true;
	}
	m_pDataShowLayer->ShowData(
		DataMager::shareDataMager()->m_GolfDataMap.rbegin()->second.backspin,
		DataMager::shareDataMager()->m_GolfDataMap.rbegin()->second.sidespin,
		DataMager::shareDataMager()->m_GolfDataMap.rbegin()->second.velocity,
		DataMager::shareDataMager()->m_GolfDataMap.rbegin()->second.pitch,
		DataMager::shareDataMager()->m_GolfDataMap.rbegin()->second.yaw,
		DataMager::shareDataMager()->m_GolfDataMap.rbegin()->second.cam_confidence
		);

	this->setTouchMode(kCCTouchesOneByOne);
	this->setTouchEnabled(true);

    return true;
}
//��ť�Ļص�����
void DataAnalysisScene::menuCallback(CCObject* pSender)
{
	Ext_IsResetGG = true;
    //��ȡ��������ť�ı�ǩ
    int tag = ((CCNode*)pSender)->getTag();
    //���ݱ�ǩ��Ӧ�¼�
    if(tag == MENUTAG_Back)
	{
		PostureAnalysisScene::m_pFrontDemoVideoLayer->release();
		PostureAnalysisScene::m_pFrontDemoVideoLayer = NULL;
		if (PostureAnalysisScene::m_pSideDemoVideoLayer)
		{
			PostureAnalysisScene::m_pSideDemoVideoLayer->release();
			PostureAnalysisScene::m_pSideDemoVideoLayer = NULL;
		}
        CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
	}
    else if(tag ==MENUTAG_PostureAnalysis)
        CCDirector::sharedDirector()->replaceScene(PostureAnalysisScene::CreateScene());
}
bool DataAnalysisScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	Ext_IsResetGG = true;
	CCPoint pos = pTouch->getLocation();
	if (m_pDataShowLayer->boundingBox().containsPoint(pos) && m_pDataView == NULL)
	{
		CCLayerColor* pLayerColor = CCLayerColor::create(ccc4(0, 0, 0, 128));
		m_pDataView = DataView::create();
		m_pDataView->setUserObject(pLayerColor);
		m_pDataView->setPosition(230,170);
		this->addChild(pLayerColor);
		this->addChild(m_pDataView);
	}
	else if (m_pDataView != NULL&&!m_pDataView->boundingBox().containsPoint(pos))
	{
		this->removeChild((CCNode*)m_pDataView->getUserObject());
		this->removeChild(m_pDataView);
		m_pDataView = NULL;
	}
	return false;
}