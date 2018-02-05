#ifndef _LostScene_H_
#define _LostScene_H_

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;

class LostScene: public Layer {
	public:
	static Scene* createScene();
	CREATE_FUNC(LostScene);
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCloseCallback2(cocos2d::Ref* pSender);
};

#endif