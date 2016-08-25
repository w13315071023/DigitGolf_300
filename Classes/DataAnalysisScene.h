#pragma once
#include "Tools.h"

USING_NS_CC;
class GroundLayer;
class ParabolicLayer;
class TargetLayer;
class DataShowLayer;
class DrawingLayer;
class DataView;
class DataAnalysisScene:public CCLayer
{
public:
	static DrawingLayer* m_pDrawingLayer2;
    DataAnalysisScene(void);
    ~DataAnalysisScene(void);
	DataView* m_pDataView;
    //���ͼ
    GroundLayer*        m_pGroundLayer;
    //����ͼ
    ParabolicLayer*     m_pParabolicLayer;
    //����ͼ
    TargetLayer*        m_pTargetLayer;
    //������ʾ
    DataShowLayer*      m_pDataShowLayer;
    //�����Ĵ�������
    static CCScene* CreateScene();
    //����Ĵ�������
    CREATE_FUNC(DataAnalysisScene);
    //��ʼ������
    bool init();
    //��ť�Ļص�����
    void menuCallback(CCObject* pSender);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};

