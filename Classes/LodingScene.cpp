#include "LodingScene.h"
//#include "GolfXIMager.h"
#include "HelloWorldScene.h"
#include "MovieVideoLayer.h"
#include "RecordClass.h"
#include "ResetGGMager.h"
#include "websocketMager.h"
#include "SerialMager.h"


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
	websocketMager::getInstence();
	SerialMager::getInstence();

	Ext_cameraNum = 2;

	tSdkCameraDevInfo	cameraInfo[2] = { NULL };

	CameraSdkInit(1);
	CameraEnumerateDevice(cameraInfo, &Ext_cameraNum);
	if(Ext_cameraNum == 1)
	{
		if(cameraInfo[0].acPortType[0] == 'N'&&cameraInfo[0].acPortType[1] == 'E'&&cameraInfo[0].acPortType[2] == 'T')
		{
			Ext_Is300Frames = true;
		}
		else
		{
			Ext_Is300Frames = false;
		}
	}
	else
	{
		if(cameraInfo[0].acPortType[0] == 'N'&&cameraInfo[0].acPortType[1] == 'E'&&cameraInfo[0].acPortType[2] == 'T'&&
			cameraInfo[1].acPortType[0] == 'N'&&cameraInfo[1].acPortType[1] == 'E'&&cameraInfo[1].acPortType[2] == 'T')
		{
			Ext_Is300Frames = true;
		}
		else
		{
			Ext_Is300Frames = false;
		}
	}
	printf("初始化LodingScene\n");
	//GolfXIMager::getInstence();
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
		Ext_ToPixels = doc["ToPixels"].GetDouble();
		Ext_StepNum = doc["StepNum"].GetInt();
		Ext_FFmpegStep = doc["FFmpegStep"].GetInt();
		Ext_FrameRate = doc["FrameRate"].GetInt();
		//Ext_IsTurnCamera = doc["TurnCamera"].GetBool();
	}
	if(Ext_FrameRate == 300)
	{
		Ext_VideoExposureTime = 3300;
	}
	else
	{
		Ext_VideoExposureTime = 16600;
	}
	CCSprite* pBackGround = CCSprite::create("HomeUI/Bg.png");
	pBackGround->setPosition(ccp(VISIBLEW / 2, VISIBLEH / 2));
	this->addChild(pBackGround);
	CCLabelTTF* pLable = CCLabelTTF::create(GBKToUTF8("正在为开机第一次加载系统做准备，\n这个过程大约需要十秒。").c_str(),"Arial",72);
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