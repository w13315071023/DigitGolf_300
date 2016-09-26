#include "MessageScene.h"
#include "PostureAnalysisScene.h"

CCScene* MessageScene::getScene()
{
	CCScene* scene = CCScene::create();
	CCLayer* layer = MessageScene::create();
	scene->addChild(layer);

	return scene;
}
MessageScene::MessageScene(void)
{
}
MessageScene::~MessageScene(void)
{
}
bool MessageScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSprite* pSprite = CCSprite::create("VideoUI/beijing1.png");
	pSprite->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(pSprite);
	CCLabelTTF* pLabel = CCLabelTTF::create(GBKToUTF8("正在保存自定义视频。。。").c_str(), "Arial", 72);
	pLabel->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(pLabel);

	this->scheduleOnce(schedule_selector(MessageScene::update),0.5);

	return true;
}
void MessageScene::update(float dt)
{
	this->MSGfunc();
	CCDirector::sharedDirector()->popScene();
}
void MessageScene::MSGfunc()
{
	if (PostureAnalysisScene::m_pFrontDemoVideoLayer)
	{
		PostureAnalysisScene::m_pFrontDemoVideoLayer->SaveVideo();
	}
	if (PostureAnalysisScene::m_pSideDemoVideoLayer)
	{
		PostureAnalysisScene::m_pSideDemoVideoLayer->SaveVideo();
	}
}