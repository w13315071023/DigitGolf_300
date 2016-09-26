#pragma once
#include "Tools.h"
class MessageScene:public CCLayer
{
public:
	MessageScene(void);
	~MessageScene(void);
	static CCScene* getScene();
	CREATE_FUNC(MessageScene);
	bool init();
	void update(float dt);
	void MSGfunc();
};

