#include "SettingScene.h"
#include "MovieVideoLayer.h"
#include "RecordClass.h"
#include "UINode.h"
#include "MyMenu.h"

CCScene* SettingScene::getScene()
{
	CCScene* scene = CCScene::create();
	if (scene)
	{
		CCLayer* layer = SettingScene::create();
		scene->addChild(layer);
	}
	else
	{
		printf("Error:createScene");
	}
	return scene;
}
SettingScene::SettingScene(void)
{
}
SettingScene::~SettingScene(void)
{
}
bool SettingScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSprite* pBackGround = CCSprite::create("SettingUI/background.png");
	pBackGround->setPosition(ccp(VISIBLEW/2,VISIBLEH/2));
	this->addChild(pBackGround,-1);
	//设置靶心距离
	UINode* pNode = UINode::create();
	pNode->setPosition(ccp(1510,630));
	this->addChild(pNode);
	//视频延迟
	m_VideoSleepSlider = CCControlSlider::create("SettingUI/Slider_1.png", "SettingUI/Slider_2.png", "SettingUI/Slider_3.png");
	m_VideoSleepSlider->setPosition(ccp(760, 710));
	if(Ext_IsDigitTrak)
	{
		m_VideoSleepSlider->setMaximumValue(1000);
		m_VideoSleepSlider->setMinimumValue(0);
	}
	else
	{
		m_VideoSleepSlider->setMaximumValue(1500);
		m_VideoSleepSlider->setMinimumValue(500);
	}
	m_VideoSleepSlider->setValue(Ext_VideoSleep);
	m_VideoSleepSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::valueChanged), CCControlEventValueChanged);

	//声音预制
	m_SerialThresholdSlider = CCControlSlider::create("SettingUI/Slider_1.png", "SettingUI/Slider_2.png", "SettingUI/Slider_3.png");
	m_SerialThresholdSlider->setPosition(ccp(760, 810));
	m_SerialThresholdSlider->setMaximumValue(1000);
	m_SerialThresholdSlider->setMinimumValue(500);
	m_SerialThresholdSlider->setValue(Ext_SerialThreshold);
	m_SerialThresholdSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::valueChanged), CCControlEventValueChanged);
	
	//视频亮度
	m_VideoGainSlider = CCControlSlider::create("SettingUI/Slider_1.png", "SettingUI/Slider_2.png", "SettingUI/Slider_3.png");
	m_VideoGainSlider->setPosition(ccp(760, 610));
	m_VideoGainSlider->setMaximumValue(64);
	m_VideoGainSlider->setMinimumValue(1);
	m_VideoGainSlider->setValue(Ext_VideoGain);
	m_VideoGainSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::valueChanged), CCControlEventValueChanged);
	
	//相机位置
	CCMenuItemToggle* pSetCameraItem = CCMenuItemToggle::createWithTarget(
		this, menu_selector(SettingScene::SetCameraCallBack),
		CCMenuItemImage::create("SettingUI/front.png", "SettingUI/front.png"),
		CCMenuItemImage::create("SettingUI/side.png", "SettingUI/side.png"), NULL
		);
	pSetCameraItem->setPosition(ccp(1510, 720));
	pSetCameraItem->setSelectedIndex(Ext_IsFrontCamera?1:0);
	//情景模式
	CCMenuItemToggle* pSetQingjingItem = CCMenuItemToggle::createWithTarget(
		this, menu_selector(SettingScene::SetQingjingCallBack),
		CCMenuItemImage::create("SettingUI/sunny.png", "SettingUI/sunny.png"),
		CCMenuItemImage::create("SettingUI/cloudy.png", "SettingUI/cloudy.png"),
		CCMenuItemImage::create("SettingUI/indoor.png", "SettingUI/indoor.png"), NULL
		);
	pSetQingjingItem->setPosition(ccp(1510, 800));

	if (Ext_VideoGain <= 5)
	{
		Ext_IsIndoor = false;
		pSetQingjingItem ->setSelectedIndex(0);
	}
	else if (Ext_VideoGain>5&&Ext_VideoGain <= 32)
	{
		Ext_IsIndoor = false;
		pSetQingjingItem ->setSelectedIndex(1);
	}
	else if (Ext_VideoGain > 32)
	{
		Ext_IsIndoor = true;
		pSetQingjingItem ->setSelectedIndex(2);
	}
	//确定按钮
	CCMenuItemImage* pEnter = CCMenuItemImage::create("SettingUI/ok_on.png", "SettingUI/ok_off.png", this, menu_selector(SettingScene::menuEnterCallBack));
	pEnter->setPosition(ccp(VISIBLEW / 2, 90));
	//录像选择
	{
		//默认参考按钮
		m_pDemoVideo = CCMenuItemImage::create("SettingUI/default_on.png", "SettingUI/default_off.png","SettingUI/default_off.png", this, menu_selector(SettingScene::menuVideoCallBack));
		m_pDemoVideo->setPosition(ccp(955, 420));
		//自定义按钮
		m_pSelfVideo = CCMenuItemImage::create("SettingUI/custom_on.png", "SettingUI/custom_off.png","SettingUI/custom_off.png", this, menu_selector(SettingScene::menuVideoCallBack));
		m_pSelfVideo->setPosition(ccp(955, 320));
		if(Ext_IsDemoVideo == true)
		{
			m_pDemoVideo->setEnabled(false);
		}
		else
		{
			m_pSelfVideo->setEnabled(false);
		}
	}
	//系统选择
	{
		m_pFrames60 = CCMenuItemImage::create("SettingUI/60frames_on.png", "SettingUI/60frames_off.png","SettingUI/60frames_off.png", this, menu_selector(SettingScene::menuFramesCallBack));
		m_pFrames60->setPosition(ccp(450, 420));

		m_pFrames300 = CCMenuItemImage::create("SettingUI/300frames_on.png", "SettingUI/300frames_off.png","SettingUI/300frames_off.png", this, menu_selector(SettingScene::menuFramesCallBack));
		m_pFrames300->setPosition(ccp(450, 320));
		if(Ext_Is300Frames)
		{
			if(Ext_FrameRate == 300)
			{
				m_pFrames300->setEnabled(false);
				Ext_VideoExposureTime = 3300;
				Ext_VideoSize = 750;
			}
			else
			{
				m_pFrames60->setEnabled(false);
				Ext_VideoExposureTime = 16600;
				Ext_VideoSize = 150;
			}
		}
		else
		{
			m_pFrames300->setEnabled(false);
			m_pFrames60->setEnabled(false);
			Ext_VideoExposureTime = 16600;
			Ext_VideoSize = 150;
		}
	}
	//触发器选择
	{
		m_pSerialP = CCMenuItemImage::create("SettingUI/box_on.png", "SettingUI/box_off.png","SettingUI/box_off.png", this, menu_selector(SettingScene::menuDigitTrakCallBack));
		m_pSerialP->setPosition(ccp(1460, 420));

		m_pDigitTrak = CCMenuItemImage::create("SettingUI/DigitTrak_on.png", "SettingUI/DigitTrak_off.png","SettingUI/DigitTrak_off.png", this, menu_selector(SettingScene::menuDigitTrakCallBack));
		m_pDigitTrak->setPosition(ccp(1460, 320));
		if(Ext_IsDigitTrak)
		{
			m_pDigitTrak->setEnabled(false);
			m_pSerialP->setEnabled(true);
		}
		else
		{
			m_pSerialP->setEnabled(false);
			m_pDigitTrak->setEnabled(true);
		}
	}

	MyMenu* pMenu = MyMenu::create(
		pEnter,
		m_pDemoVideo,
		m_pSelfVideo,
		pSetCameraItem,
		pSetQingjingItem,
		m_pFrames60,
		m_pFrames300,
		m_pSerialP,
		m_pDigitTrak,
		NULL);
	pMenu->setPosition(CCPointZero);

	this->addChild(m_VideoSleepSlider);
	this->addChild(m_SerialThresholdSlider);
	this->addChild(m_VideoGainSlider);
	this->addChild(pMenu);

	return true;
}
void SettingScene::valueChanged(CCObject* sender, CCControlEvent controlEvent)
{
	if (sender == m_VideoSleepSlider)
	{
		Ext_VideoSleep = (int)m_VideoSleepSlider->getValue();
	}
	else if (sender == m_SerialThresholdSlider)
	{
		Ext_SerialThreshold = (int)m_SerialThresholdSlider->getValue();
	}
	else if (sender == m_VideoGainSlider)
	{
		Ext_VideoGain = (int)m_VideoGainSlider->getValue();
	}
}
void SettingScene::SetQingjingCallBack(CCObject* obj)
{
	CCMenuItemToggle* pItem = (CCMenuItemToggle*)obj;
	if (pItem->getSelectedIndex() == 0)
	{
		Ext_IsIndoor = false;
		Ext_VideoGain = 5;
	}
	else if (pItem->getSelectedIndex() == 1)
	{
		Ext_IsIndoor = false;
		Ext_VideoGain = 30;
	}
	else if (pItem->getSelectedIndex() == 2)
	{
		Ext_IsIndoor = true;
		Ext_VideoGain = 64;
	}
}
void SettingScene::onExit()
{
	CCLayer::onExit();

	Document::AllocatorType allocator;
	Value object(kObjectType);
	
	object.AddMember("VideoSleep", Ext_VideoSleep, allocator);
	object.AddMember("SerialThreshold", Ext_SerialThreshold, allocator);
	object.AddMember("VideoGain", Ext_VideoGain, allocator);
	object.AddMember("ToPixels", Ext_ToPixels, allocator);
	object.AddMember("StepNum", Ext_StepNum, allocator);
	object.AddMember("FFmpegStep", Ext_FFmpegStep, allocator);
	object.AddMember("FrameRate", Ext_FrameRate, allocator);
	object.AddMember("IsFrontCamera", Ext_IsFrontCamera, allocator);
	object.AddMember("IsDigitTrak", Ext_IsDigitTrak, allocator);
	saveValue(object, "Setting.json");
}
void SettingScene::menuEnterCallBack(CCObject* obj)
{
	CCDirector::sharedDirector()->popScene();
}
void SettingScene::menuVideoCallBack(CCObject* obj)
{
	if (obj == m_pDemoVideo)
	{
		m_pDemoVideo->setEnabled(false);
		m_pSelfVideo->setEnabled(true);
		Ext_IsDemoVideo = true;
	}
	else
	{
		m_pDemoVideo->setEnabled(true);
		m_pSelfVideo->setEnabled(false);
		Ext_IsDemoVideo = false;
	}
}
void SettingScene::menuFramesCallBack(CCObject* obj)
{
	if (obj == m_pFrames60)
	{
		m_pFrames60->setEnabled(false);
		m_pFrames300->setEnabled(true);
		Ext_FrameRate = 60;
		Ext_VideoExposureTime = 16600;
	}
	else
	{
		m_pFrames60->setEnabled(true);
		m_pFrames300->setEnabled(false);
		Ext_FrameRate = 300;
		Ext_VideoExposureTime = 3300;
	}
}
void SettingScene::menuDigitTrakCallBack(CCObject* obj)
{
	if(m_pDigitTrak == obj)
	{
		Ext_IsDigitTrak = true;
		Ext_VideoSleep = 590;
		m_pDigitTrak->setEnabled(false);
		m_pSerialP->setEnabled(true);
	}
	else
	{
		Ext_IsDigitTrak = false;
		Ext_VideoSleep = 1000;
		m_pDigitTrak->setEnabled(true);
		m_pSerialP->setEnabled(false);
	}
}
void SettingScene::SetCameraCallBack(CCObject* obj)
{
	if (0 == ((CCMenuItemToggle*)obj)->getSelectedIndex())
	{
		Ext_IsFrontCamera = false;
	}
	else
	{
		Ext_IsFrontCamera = true;
	}
}