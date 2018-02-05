#ifndef __SecondScene_H__
#define __SecondScene_H__
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;

class SecondScene : public Layer {
public:
    static Scene* createScene();
    virtual bool init();
	void popScene(Ref* pSender);
    CREATE_FUNC(SecondScene);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuItem1Callback(cocos2d::Ref* pSender);
	void menuItem2Callback(cocos2d::Ref* pSender);
	void menuItem3Callback(cocos2d::Ref* pSender);
	void menuItem4Callback(cocos2d::Ref* pSender);

	// 以下回调函数暂未使用
	void menuItem5Callback(cocos2d::Ref* pSender);
	void hideAllSprite();
	cocos2d::Sprite *sprite[5];
};

#endif