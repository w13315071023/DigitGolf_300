#include "DrawingLayer.h"
#include "PostureAnalysisScene.h"
#include "MyMenu.h"

DrawingLayer::DrawingLayer(void)
{
}
DrawingLayer::~DrawingLayer(void)
{
}
bool DrawingLayer::init()
{
    //��ʼ������
    if(!CCLayer::init())
    {
        return false;
    }
    m_bIsDrawing = false;
    m_bIsDelete = false;
    m_bIsCls = false;
    m_bIsDrawRect = false;
    m_bIsDrawCircle = false;
	m_bIsDrawAngle = false;
	m_bIsDrawAngleEnd = false;
	m_ActionNum = 0;
    m_PointEnd = ccp(-10,-10);
    m_cSelectedColor = ccc3(255,0,0);
	m_pRedLayer = CCLayerColor::create(ccc4(255, 0, 0, 255), 60, 42);
	m_pGreenLayer = CCLayerColor::create(ccc4(0, 255, 0, 255), 60, 42);
	m_pBlueLayer = CCLayerColor::create(ccc4(0, 0, 255, 255), 60, 42);
	m_pYellowLayer = CCLayerColor::create(ccc4(255, 255, 0, 255), 60, 42);

	m_pColorBox = CCSprite::create("UI_DrawLayer/�ʿ��Ե��.png");
	m_pColorBox->setPosition(ccp(1857 + 200, 483 + 58 * 3));
	this->addChild(m_pColorBox);
	m_pFontBox = CCSprite::create("UI_DrawLayer/�����Ե��.png");
	m_pFontBox->setPosition(ccp(1857, -100));
	this->addChild(m_pFontBox);

    //������ͼ��ť����
	m_pMenuItemToggle = CCMenuItemToggle::createWithTarget(
		this, menu_selector(DrawingLayer::menuToggleCallBack),
		CCMenuItemImage::create("UI_DrawLayer/��ͼ.png", "UI_DrawLayer/��ͼ.png"),
		CCMenuItemImage::create("UI_DrawLayer/�ر�.png", "UI_DrawLayer/�ر�.png"),
		NULL);
	//������ͼ���߰�ť
	m_pDrawAngleItem = CCMenuItemImage::create(
		"UI_DrawLayer/����.png",
		"UI_DrawLayer/����.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));
	m_pDrawCirItem = CCMenuItemImage::create(
		"UI_DrawLayer/��Բ.png",
		"UI_DrawLayer/��Բ.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));
	m_pDrawRecItem = CCMenuItemImage::create(
		"UI_DrawLayer/����.png",
		"UI_DrawLayer/����.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));
	m_pDrawingItem = CCMenuItemImage::create(
		"UI_DrawLayer/����.png",
		"UI_DrawLayer/����.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));

	m_pDeleteItem = CCMenuItemImage::create(
		"UI_DrawLayer/����.png",
		"UI_DrawLayer/����.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));

	m_pClsItem = CCMenuItemImage::create(
		"UI_DrawLayer/���.png",
		"UI_DrawLayer/���.png",
		this,
		menu_selector(DrawingLayer::menuCallBack));
    //�رղ�ĺ���ê��
    m_pRedLayer->ignoreAnchorPointForPosition(false);
    m_pGreenLayer->ignoreAnchorPointForPosition(false);
    m_pBlueLayer->ignoreAnchorPointForPosition(false);
    m_pYellowLayer->ignoreAnchorPointForPosition(false);
    //���ð�ť��ê��
    m_pMenuItemToggle->setAnchorPoint(ccp(0.5,0.5));
    m_pDrawingItem->setAnchorPoint(ccp(0.5,0.5));
    m_pDeleteItem->setAnchorPoint(ccp(0.5,0.5));
	m_pClsItem->setAnchorPoint(ccp(0.5, 0.5));
	m_pDrawAngleItem->setAnchorPoint(ccp(0.5, 0.5));
	m_pDrawRecItem->setAnchorPoint(ccp(0.5, 0.5));
	m_pDrawCirItem->setAnchorPoint(ccp(0.5, 0.5));
	m_pRedLayer->setAnchorPoint(ccp(0.5, 0.5));
	m_pGreenLayer->setAnchorPoint(ccp(0.5, 0.5));
	m_pBlueLayer->setAnchorPoint(ccp(0.5, 0.5));
	m_pYellowLayer->setAnchorPoint(ccp(0.5, 0.5));
    //���ð�ť��λ��
	m_pDrawAngleItem->setPosition(ccp(1857, -100));
	m_pMenuItemToggle->setPosition(ccp(1857, 93));
	m_pDrawingItem->setPosition(ccp(1857, -100));
	m_pDeleteItem->setPosition(ccp(1857, -100));
	m_pClsItem->setPosition(ccp(1857, -100));
	m_pDrawRecItem->setPosition(ccp(1857, -100));
	m_pDrawCirItem->setPosition(ccp(1857, -100));
	m_pRedLayer->setPosition(ccp(1857+200, 483+58*3));
	m_pGreenLayer->setPosition(ccp(1857+200,483+58*2));
	m_pBlueLayer->setPosition(ccp(1857+200, 483+58*1));
	m_pYellowLayer->setPosition(ccp(1857+200, 483+58*0));
    //���ؼ���ӵ���Ⱦ��
    this->addChild(m_pRedLayer);
    this->addChild(m_pGreenLayer);
    this->addChild(m_pBlueLayer);
    this->addChild(m_pYellowLayer);
    //����ť��ӵ���ť�㲢��Ⱦ
	MyMenu* pMenu = MyMenu::create(
                                m_pMenuItemToggle,
                                m_pDrawingItem,
                                m_pDeleteItem,
                                m_pClsItem,
                                m_pDrawRecItem,
                                m_pDrawCirItem,
								m_pDrawAngleItem,
                                NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu);

    return true;
}
//���ذ�ť�Ļص�����
void DrawingLayer::menuToggleCallBack(CCObject* pSender)
{
	Ext_IsResetGG = true;
    //��ȡ���ذ�ť��ǰ��״̬
    int index = m_pMenuItemToggle->getSelectedIndex();
	m_pMenuItemToggle->setEnabled(false);
	m_pDrawAngleItem->setEnabled(false);
	m_pDrawRecItem->setEnabled(false);
	m_pDrawCirItem->setEnabled(false);
	m_pDrawingItem->setEnabled(false);
	m_pDeleteItem->setEnabled(false);
	m_pClsItem->setEnabled(false);
	CCCallFunc* pCallFunc = CCCallFunc::create(this, callfunc_selector(DrawingLayer::actionCallBack));
    //CCLog("%d",index);
    if(index == 1)
    {
        //���ư�ť��ѡɫ��Ķ���λ�ã����룩
		m_pDrawAngleItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 5)), pCallFunc,NULL));
		m_pDrawRecItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 4)), pCallFunc, NULL));
		m_pDrawCirItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 3)), pCallFunc, NULL));
		m_pDrawingItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 2)), pCallFunc, NULL));
		m_pDeleteItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 1)), pCallFunc, NULL));
		m_pClsItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 155 + 62 * 0)), pCallFunc, NULL));
		m_pRedLayer->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 3)), pCallFunc, NULL));
		m_pGreenLayer->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 2)), pCallFunc, NULL));
		m_pBlueLayer->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 1)), pCallFunc, NULL));
		m_pYellowLayer->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 0)), pCallFunc, NULL));
		m_pColorBox->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, 545 + 58 * 3)), pCallFunc, NULL));

		//m_pDrawAngleItem->setPosition( ccp(1857, 155 + 62 * 5));
		//m_pDrawRecItem->setPosition(ccp(1857, 155 + 62 * 4));
		//m_pDrawCirItem->setPosition( ccp(1857, 155 + 62 * 3));
		//m_pDrawingItem->setPosition(ccp(1857, 155 + 62 * 2));
		//m_pDeleteItem->setPosition(ccp(1857, 155 + 62 * 1));
		//m_pClsItem->setPosition(ccp(1857, 155 + 62 * 0));
		//m_pRedLayer->setPosition( ccp(1857, 545 + 58 * 3));
		//m_pGreenLayer->setPosition(ccp(1857, 545 + 58 * 2));
		//m_pBlueLayer->setPosition(ccp(1857, 545 + 58 * 1));
		//m_pYellowLayer->setPosition(ccp(1857, 545 + 58 * 0));
		//m_pColorBox->setPosition(ccp(1857, 545 + 58 * 3));
    }
    else
    {
        //���ư�ť��ѡɫ��Ķ���λ�ã��˳���
		m_pDrawAngleItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, -100)), pCallFunc, NULL));
		m_pDrawingItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, -100)), pCallFunc, NULL));
		m_pDeleteItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, -100)), pCallFunc, NULL));
		m_pClsItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, -100)), pCallFunc, NULL));
		m_pDrawRecItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, -100)), pCallFunc, NULL));
		m_pDrawCirItem->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, -100)), pCallFunc, NULL));
		m_pRedLayer->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857 + 200, 545 + 58 * 3)), pCallFunc, NULL));
		m_pGreenLayer->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857 + 200, 545 + 58 * 2)), pCallFunc, NULL));
		m_pBlueLayer->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857 + 200, 545 + 58 * 1)), pCallFunc, NULL));
		m_pYellowLayer->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857 + 200, 545 + 58 * 0)), pCallFunc, NULL));
		m_pColorBox->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857 + 200, 58 * 3)), pCallFunc, NULL));
		m_pFontBox->runAction(CCSequence::create(CCMoveTo::create(0.3, ccp(1857, -100)), pCallFunc, NULL));

		//m_pDrawAngleItem->setPosition(ccp(1857, -100));
		//m_pDrawingItem->setPosition(ccp(1857, -100));
		//m_pDeleteItem->setPosition(ccp(1857, -100));
		//m_pClsItem->setPosition(ccp(1857, -100));
		//m_pDrawRecItem->setPosition( ccp(1857, -100));
		//m_pDrawCirItem->setPosition(ccp(1857, -100));
		//m_pRedLayer->setPosition(ccp(1857 + 200, 545 + 58 * 3));
		//m_pGreenLayer->setPosition(ccp(1857 + 200, 545 + 58 * 2));
		//m_pBlueLayer->setPosition(ccp(1857 + 200, 545 + 58 * 1));
		//m_pYellowLayer->setPosition(ccp(1857 + 200, 545 + 58 * 0));
		//m_pColorBox->setPosition(ccp(m_pColorBox->getPosition().x + 200, m_pColorBox->getPosition().y));
		//m_pFontBox->setPosition(ccp(1857, -100));

        //�رմ����¼�
        this->setTouchEnabled(false);
        //�رջ滭����
        m_bIsDrawing = false;
        m_bIsDelete = false;
        m_bIsCls = false;
        m_bIsDrawRect = false;
        m_bIsDrawCircle = false;
    }
}
void DrawingLayer::actionCallBack()
{
	m_ActionNum++;
	if (m_ActionNum == 11 || m_ActionNum == 12)
	{
		m_ActionNum = 0;
		m_pMenuItemToggle->setEnabled(true);
		m_pDrawAngleItem->setEnabled(true);
		m_pDrawRecItem->setEnabled(true);
		m_pDrawCirItem->setEnabled(true);
		m_pDrawingItem->setEnabled(true);
		m_pDeleteItem->setEnabled(true);
		m_pClsItem->setEnabled(true);
	}
}
//��ť�Ļص�����
void DrawingLayer::menuCallBack(CCObject* pSender)
{
	Ext_IsResetGG = true;
    if(m_pDrawingItem == pSender)
    {//�滭��ť���¼�
        m_bIsDelete = false;
        m_bIsDrawing = true;
        m_bIsDrawRect = false;
        m_bIsDrawCircle = false;
		m_bIsDrawAngle = false;
		m_pFontBox->setPosition(m_pDrawingItem->getPosition());
    }
    else if(m_pDeleteItem == pSender)
    {
		m_bIsDrawAngleEnd = false;
		m_curAngle = ColorAngle();
		if (m_DrawSta.empty())
		{
			return;
		}
		//ȡ����ǰ���һ�λ滭ID
		int index = m_DrawSta.top();
		switch (index)
		{
		case 1:
		{
			m_bIsDrawAngleEnd = false;
			m_curAngle = ColorAngle();
			//ɾ���߶�
			bool IsDelPoint = false;
			vector<ColorPoint> ::reverse_iterator riter = m_PointVec.rbegin();
			while (riter != m_PointVec.rend())
			{
				if (riter->pos.equals(m_PointEnd))
				{
					IsDelPoint = !IsDelPoint;
					if (IsDelPoint == true)
					{
						m_PointVec.erase((riter + 1).base());
						riter = m_PointVec.rbegin();
					}
					else
					{
						break;
					}
				}
				else
				{
					m_PointVec.erase((riter + 1).base());
					riter = m_PointVec.rbegin();
				}
			}
		}
		break;
		//ɾ������
		case 2:
		{
			if (!m_RectVec.empty())
			{
				m_RectVec.pop_back();
			}
		}
		break;
		//ɾ��Բ
		case 3:
		{
			if (!m_CircleVec.empty())
			{
				m_CircleVec.pop_back();
			}
		}
		break;
		//ɾ����
		case 4:
		{
			if (!m_AngleVec.empty())
			{
				this->removeChild(m_AngleVec.back().label);
				m_AngleVec.pop_back();
			}
		}
		break;
		}
		//����ջ��
		m_DrawSta.pop();
	}
    else if(m_pDrawRecItem == pSender)
    {//����ť���¼�
		m_pFontBox->setPosition(m_pDrawRecItem->getPosition());
        m_bIsDelete = false;
        m_bIsDrawing = false;
        m_bIsDrawRect = true;
        m_bIsDrawCircle = false;
		m_bIsDrawAngle = false;
    }
    else if(m_pDrawCirItem == pSender)
    {//��Բ��ť���¼�
		m_pFontBox->setPosition(m_pDrawCirItem->getPosition());
        m_bIsDelete = false;
        m_bIsDrawing = false;
        m_bIsDrawRect = false;
        m_bIsDrawCircle = true;
		m_bIsDrawAngle = false;
    }
	else if (m_pDrawAngleItem == pSender)
	{//���ǰ�ť���¼�
		m_pFontBox->setPosition(m_pDrawAngleItem->getPosition());
		m_bIsDelete = false;
		m_bIsDrawing = false;
		m_bIsDrawRect = false;
		m_bIsDrawCircle = false;
		m_bIsDrawAngle = true;
	}
    else if(m_pClsItem == pSender)
    {//�����ť�Ļص�
		this->ClsAll();
    }
    //�������㴥��
    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
}
//��������ʱ�Ļص�
bool DrawingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	Ext_IsResetGG = true;
    //��ȡ������
    CCPoint pos = pTouch->getLocation();
    //ѡȡ��ɫ
    if(m_pRedLayer->boundingBox().containsPoint(pos))
    {
        m_cSelectedColor = m_pRedLayer->getColor();
		m_pColorBox->setPosition(m_pRedLayer->getPosition());
    }
    else if(m_pGreenLayer->boundingBox().containsPoint(pos))
    {
        m_cSelectedColor = m_pGreenLayer->getColor();
		m_pColorBox->setPosition(m_pGreenLayer->getPosition());
    }
    else if(m_pBlueLayer->boundingBox().containsPoint(pos))
    {
        m_cSelectedColor = m_pBlueLayer->getColor();
		m_pColorBox->setPosition(m_pBlueLayer->getPosition());
    }
    else if(m_pYellowLayer->boundingBox().containsPoint(pos))
    {
        m_cSelectedColor = m_pYellowLayer->getColor();
		m_pColorBox->setPosition(m_pYellowLayer->getPosition());
    }
	if (
		m_bIsDrawing == false &&
		m_bIsDrawRect == false &&
		m_bIsDrawCircle == false &&
		m_bIsDrawAngle == false)
    {
        return false;
    }
    //��¼���ߵ㿪ʼ
	if (pos.x<100 || pos.x>1820 || pos.y<100 || pos.y>980)
	{
		return false;
	}
    if(m_bIsDrawing == true)
    {
        ColorPoint cp;
        cp.pos = pos;
        cp.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
        m_PointVec.push_back(cp);
    }
    //��¼�������꿪ʼ
    else if(m_bIsDrawRect == true)
    {
        m_curRect.pos1 = pos;
        m_curRect.pos2 = pos;
        m_curRect.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
    }
    //��¼��Բ���꿪ʼ
    else if(m_bIsDrawCircle == true)
    {
        m_curCircle.center = pos;
        m_curCircle.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
    }
	//��¼�������꿪ʼ
	else if (m_bIsDrawAngle == true)
	{
		if (m_bIsDrawAngleEnd == false)
		{
			m_curAngle.pos1 = pos;
			m_curAngle.pos2 = pos;
			m_curAngle.pos3 = pos;
			m_curAngle.c4b = ccc4(m_cSelectedColor.r,
				m_cSelectedColor.g,
				m_cSelectedColor.b,
				255);
		}
		else
		{
			m_curAngle.pos3 = pos;
			CCPoint vector1 = (m_curAngle.pos2 - m_curAngle.pos1).normalize();
			CCPoint vector2 = (m_curAngle.pos3 - m_curAngle.pos1).normalize();
			float radians = ccpAngle(vector1, vector2);
			m_curAngle.angle = CC_RADIANS_TO_DEGREES(radians);
			char name[32];
			sprintf(name, "%.2f", m_curAngle.angle);
			m_curAngle.label = CCLabelTTF::create(name, "airal", 20);
			m_curAngle.label->setPosition(ccp(m_curAngle.pos1.x + 10, m_curAngle.pos1.y));
			m_curAngle.label->setColor(ccc3(0, 255, 255));
			this->addChild(m_curAngle.label);
		}
	}
    return true;
    
}
//�����ƶ�ʱ�Ļص�
void DrawingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	Ext_IsResetGG = true;
    //��ȡ������
    CCPoint pos = pTouch->getLocation();
	if (pos.x<100 || pos.x>1820 || pos.y<100 || pos.y>980)
	{
		return;
	}
    //��¼�滭������
    if(m_bIsDrawing == true)
    {
        ColorPoint cp;
        cp.pos = pos;
        cp.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
        m_PointVec.push_back(cp);
    }
    else if(m_bIsDrawRect == true)
    {
        m_curRect.pos2 = pos;
    }
    else if(m_bIsDrawCircle == true)
    {
        float a = m_curCircle.center.x;
        float b = m_curCircle.center.y;
        float d = sqrt(pow(a-pos.x,2)+pow(b-pos.y,2));
        m_curCircle.radius = d;
    }
	else if (m_bIsDrawAngle == true)
	{
		if (m_bIsDrawAngleEnd == false)
		{
			m_curAngle.pos2 = pos;
		}
		else
		{
			m_curAngle.pos3 = pos;
			CCPoint vector1 = (m_curAngle.pos2 - m_curAngle.pos1).normalize();
			CCPoint vector2 = (m_curAngle.pos3 - m_curAngle.pos1).normalize();
			float radians = ccpAngle(vector1, vector2);
			m_curAngle.angle = CC_RADIANS_TO_DEGREES(radians);
			char name[32];
			sprintf(name, "%.2f", m_curAngle.angle);
			m_curAngle.label->setString(name);
		}
	}
}
//����̧��ʱ�Ļص�
void DrawingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	Ext_IsResetGG = true;
    CCPoint pos = pTouch->getLocation();
	if (pos.x<100 || pos.x>1820 || pos.y<100 || pos.y>980)
	{
		return;
	}
    //��¼���ߵ����
    if(m_bIsDrawing == true)
    {
        ColorPoint cp;

        cp.pos = pos;
        cp.c4b = ccc4(m_cSelectedColor.r,
                    m_cSelectedColor.g,
                    m_cSelectedColor.b,
                    255);
        m_PointVec.push_back(cp);
        cp.pos = m_PointEnd;
        m_PointVec.push_back(cp);
		m_DrawSta.push(1);
    }
    //��¼�����������
    else if(m_bIsDrawRect == true)
    {
        m_curRect.pos2 = pos;
        m_RectVec.push_back(m_curRect);
        m_curRect.pos1 = ccp(-1,-1);
        m_curRect.pos2 = ccp(-1,-1);
		m_DrawSta.push(2);
    }
    //��¼��Բ�������
    else if(m_bIsDrawCircle == true)
    {
        float a = m_curCircle.center.x;
        float b = m_curCircle.center.y;
        float d = sqrt(pow(a-pos.x,2)+pow(b-pos.y,2));
        m_curCircle.radius = d;
        m_CircleVec.push_back(m_curCircle);
        m_curCircle.radius = 0;
		m_DrawSta.push(3);
    }
	//��¼�����������
	else if (m_bIsDrawAngle == true)
	{
		if (m_bIsDrawAngleEnd == false)
		{
			m_curAngle.pos2 = pos;
		}
		else
		{
			m_curAngle.pos3 = pos;
			CCPoint vector1 = (m_curAngle.pos2 - m_curAngle.pos1).normalize();
			CCPoint vector2 = (m_curAngle.pos3 - m_curAngle.pos1).normalize();
			float radians = ccpAngle(vector1, vector2);
			m_curAngle.angle = CC_RADIANS_TO_DEGREES(radians);
			m_AngleVec.push_back(m_curAngle);
			m_DrawSta.push(4);
			m_curAngle = ColorAngle();
		}
		m_bIsDrawAngleEnd = !m_bIsDrawAngleEnd;
	}
}
//�滭����
void DrawingLayer::draw(void)
{
	//���û滭ʱ������
	ccPointSize(LINEWIDTH);
	glLineWidth(LINEWIDTH);
    //���ݼ�¼�Ļ滭�㻭��
    vector<ColorPoint> ::iterator iter;
    for(iter = m_PointVec.begin();iter != m_PointVec.end();iter++)
    {
        if(iter == m_PointVec.begin())
        {
            ccDrawColor4B((*iter).c4b.r,(*iter).c4b.g,(*iter).c4b.b,(*iter).c4b.a);
            ccDrawPoint((*iter).pos);
        }
		else if ((*iter).pos.equals(m_PointEnd))
        {
            continue;
        }
        else if((*(iter-1)).pos.equals(m_PointEnd))
        {
            ccDrawColor4B((*iter).c4b.r,(*iter).c4b.g,(*iter).c4b.b,(*iter).c4b.a);
            ccDrawPoint((*iter).pos);
        }
        else
        {
            ccDrawColor4B((*iter).c4b.r,(*iter).c4b.g,(*iter).c4b.b,(*iter).c4b.a);
            ccDrawLine((*(iter-1)).pos,(*iter).pos);
        }
    }
    //���ݼ�¼���껭��
    ccDrawColor4B(m_curRect.c4b.r,
                m_curRect.c4b.g,
                m_curRect.c4b.b,
                m_curRect.c4b.a);
    ccDrawRect(m_curRect.pos1,m_curRect.pos2);
    vector<ColorRect> ::iterator Riter;
    for(Riter = m_RectVec.begin();Riter != m_RectVec.end();Riter++)
    {
        ccDrawColor4B(Riter->c4b.r,
                    Riter->c4b.g,
                    Riter->c4b.b,
                    Riter->c4b.a);
        ccDrawRect(Riter->pos1,Riter->pos2);
    }
    //���ݼ�¼���껭Բ
    ccDrawColor4B(m_curCircle.c4b.r,m_curCircle.c4b.g,m_curCircle.c4b.b,m_curCircle.c4b.a);
    ccDrawCircle(m_curCircle.center,m_curCircle.radius,
        m_curCircle.angle,m_curCircle.segments,m_curCircle.drawLineToCenter);
    vector<ColorCircle> ::iterator Citer;
    for(Citer = m_CircleVec.begin();Citer != m_CircleVec.end();Citer++)
    {
        ccDrawColor4B(Citer->c4b.r,
                    Citer->c4b.g,
                    Citer->c4b.b,
                    Citer->c4b.a);
        ccDrawCircle(Citer->center,
                    Citer->radius,
                    Citer->angle,
                    Citer->segments,
                    Citer->drawLineToCenter);
    }
	//���ݼ�¼���껭��
	ccDrawColor4B(m_curAngle.c4b.r, m_curAngle.c4b.g, m_curAngle.c4b.b, m_curAngle.c4b.a);
	ccDrawLine(m_curAngle.pos1, m_curAngle.pos2);
	ccDrawLine(m_curAngle.pos1, m_curAngle.pos3);
    vector<ColorAngle> ::iterator Angle;
	for (Angle = m_AngleVec.begin(); Angle != m_AngleVec.end(); Angle++)
    {
		ccDrawColor4B(Angle->c4b.r,
					Angle->c4b.g,
					Angle->c4b.b,
					Angle->c4b.a);
		ccDrawLine(Angle->pos1, Angle->pos2);
		ccDrawLine(Angle->pos1, Angle->pos3);
    }
}
//������л�������
void DrawingLayer::ClsAll()
{
	Ext_IsResetGG = true;
	m_bIsDrawAngleEnd = false;
	m_curAngle = ColorAngle();
	if (!m_PointVec.empty())
	{
		m_PointVec.clear();
	}
	if (!m_RectVec.empty())
	{
		m_RectVec.clear();
	}
	if (!m_CircleVec.empty())
	{
		m_CircleVec.clear();
	}
	if (!m_AngleVec.empty())
	{
		vector<ColorAngle> ::iterator Angle;
		for (Angle = m_AngleVec.begin(); Angle != m_AngleVec.end(); Angle++)
		{
			this->removeChild(Angle->label);
		}
		m_AngleVec.clear();
	}
}