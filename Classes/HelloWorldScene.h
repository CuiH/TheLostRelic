#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class HelloWorld: public cocos2d::Layer {
	public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void addMenu();
	void addMessage();
	void addMessage2();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuCloseCallback2(cocos2d::Ref* pSender);
	void menuCloseCallback3(cocos2d::Ref* pSender);
	void menuCloseCallback4(cocos2d::Ref* pSender);
	void menuCloseCallback5(cocos2d::Ref* pSender);
	void menuCloseCallback6(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	private:
	Menu* menu;
	Menu* menu2;
	Menu* menu3;
	Layer* message;
	Layer* message2;
};


#endif // __HELLOWORLD_SCENE_H__
