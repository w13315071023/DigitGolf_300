#pragma once
#include "Tools.h"

USING_NS_CC;
class DrawingLayer:public CCLayer
{
private:
	//static DrawingLayer* m_pSelf;
	//DrawingLayer(void);
public:
    //��ť��ѡɫ��
    CCMenuItemToggle* m_pMenuItemToggle;
	CCMenuItemImage* m_pDrawingItem;
	CCMenuItemImage* m_pDrawRecItem;
	CCMenuItemImage* m_pDrawCirItem;
	CCMenuItemImage* m_pDrawAngleItem;
	CCMenuItemImage* m_pDeleteItem;
	CCMenuItemImage* m_pClsItem;
    CCLayerColor* m_pRedLayer;
    CCLayerColor* m_pGreenLayer;
    CCLayerColor* m_pBlueLayer;
    CCLayerColor* m_pYellowLayer;
	CCSprite* m_pColorBox;
	CCSprite* m_pFontBox;
    //�滭����
    vector<ColorPoint> m_PointVec;
    vector<ColorRect> m_RectVec;
    vector<ColorCircle> m_CircleVec;
	vector<ColorAngle> m_AngleVec;
	stack<int> m_DrawSta;
    //��ǰѡ�����ɫ�ͻ滭��״
    ccColor3B m_cSelectedColor;
    CCPoint m_PointEnd;
    ColorRect m_curRect;
    ColorCircle m_curCircle;
	ColorAngle m_curAngle;
    //����
    bool m_bIsDrawRect;
    bool m_bIsDrawCircle;
    bool m_bIsDrawing;
	bool m_bIsDrawAngle;
	bool m_bIsDrawAngleEnd;
    bool m_bIsDelete;
    bool m_bIsCls;

	int m_ActionNum;
public:
	//static DrawingLayer* shareDrawingLayer(void);
	DrawingLayer(void);
    ~DrawingLayer(void);
    CREATE_FUNC(DrawingLayer);
    //��ť�Ϳ��ذ�ť�Ļص�����
    void menuToggleCallBack(CCObject* pSender);
    void menuCallBack(CCObject* pSender);
	void actionCallBack();
    //���ʼ��
    virtual bool init();
    //�����¼�
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //�滭����
    void draw(void);
	void ClsAll();
};

