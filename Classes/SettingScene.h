#pragma once
#include "Tools.h"

class SettingScene:public CCLayer
{
public:
	CCControlSlider* m_VideoSleepSlider;
	CCControlSlider* m_SerialThresholdSlider;
	CCControlSlider* m_VideoGainSlider;

	CCLabelTTF* m_VideoSleepLabel;
	CCLabelTTF* m_SerialThresholdLabel;
	CCLabelTTF* m_VideoGainLabel;

	CCMenuItemImage* m_pDemoVideo;
	CCMenuItemImage* m_pSelfVideo;

	CCMenuItemImage* m_pFrames60;
	CCMenuItemImage* m_pFrames300;
public:
	static CCScene* getScene();
	CREATE_FUNC(SettingScene);
	SettingScene(void);
	~SettingScene(void);
	bool init();
	void valueChanged(CCObject* sender, CCControlEvent controlEvent);
	void menuEnterCallBack(CCObject* obj);
	void menuVideoCallBack(CCObject* obj);
	void menuFramesCallBack(CCObject* obj);
	void SetCameraCallBack(CCObject* obj);
	void SetQingjingCallBack(CCObject* obj);
	virtual void onExit();
};