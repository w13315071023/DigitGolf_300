#include "LodingScene.h"
//#include "GolfXIMager.h"
#include "SerialMager.h"
#include "HelloWorldScene.h"
#include "MovieVideoLayer.h"
#include "RecordClass.h"
#include "ResetGGMager.h"


RecordClass* MovieVideoLayer::m_Camera1 = NULL;
RecordClass* MovieVideoLayer::m_Camera2 = NULL;
CCScene* LodingScene::getLodingScene()
{
	CCScene* scene = CCScene::create();
	CCLayer* layer = LodingScene::create();
	scene->addChild(layer);
	return scene;
}
LodingScene::LodingScene(void)
{
}
LodingScene::~LodingScene(void)
{
}
bool LodingScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	Ext_cameraNum = 2;

	tSdkCameraDevInfo	cameraInfo[2];
	cameraInfo[0] = tSdkCameraDevInfo();
	cameraInfo[1] = tSdkCameraDevInfo();

	
	CameraSdkInit(1);
	CameraEnumerateDevice(cameraInfo, &Ext_cameraNum);

	printf("��ʼ��LodingScene\n");
	//GolfXIMager::getInstence();
	SerialMager::getInstence();
	if (Ext_cameraNum != 0)
	{
		MovieVideoLayer::m_Camera1 = new RecordClass();
		MovieVideoLayer::m_Camera1->init(cameraInfo[0]);
	}
	if (Ext_cameraNum == 2)
	{
		MovieVideoLayer::m_Camera2 = new RecordClass();
		MovieVideoLayer::m_Camera2->init(cameraInfo[1]);
	}
	Ext_IsThreadOn = true;
	Document doc;
	if (readValue("Setting.json", doc))
	{
		Ext_VideoSleep = doc["VideoSleep"].GetInt();
		Ext_SerialThreshold = doc["SerialThreshold"].GetInt();
		Ext_VideoGain = doc["VideoGain"].GetInt();
		Ext_VideoExposureTime = doc["VideoExposureTime"].GetDouble();
		Ext_ToPixels = doc["ToPixels"].GetDouble();
		Ext_StepNum = doc["StepNum"].GetInt();
	}
	CCSprite* pBackGround = CCSprite::create("HomeUI/Bg.png");
	pBackGround->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(pBackGround);
	CCLabelTTF* pLable = CCLabelTTF::create(GBKToUTF8("����Ϊ������һ�μ���ϵͳ��׼����\n������̴�Լ��Ҫʮ�롣").c_str(),"Arial",72);
	pLable->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(pLable);
	this->scheduleUpdate();
	return true;
}
void LodingScene::update(float dt)
{
	if (Ext_IsGolfXI == false)
	{
		CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
		return;
	}
	//if(GolfXIMager::getInstence()->RelevelXI())
	//{
	//	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
	//}
}