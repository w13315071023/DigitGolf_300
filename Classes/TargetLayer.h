#pragma once
#include "Tools.h"

USING_NS_CC;
//����ͼ
class TargetLayer:public CCSprite
{
public:
	vector<vector<CCPoint>*> m_vec;

    TargetLayer(void);
    ~TargetLayer(void);
    CREATE_FUNC(TargetLayer);

    bool init();
};

