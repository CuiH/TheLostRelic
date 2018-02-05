#include "LostScene.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "TollgateScene.h"

USING_NS_CC;

Scene* LostScene::createScene() {
	auto scene = Scene::create();
	auto layer = LostScene::create();
	scene->addChild(layer);

	return scene;
}

bool LostScene::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// add "background" splash screen"
	auto sprite = Sprite::create("youlose.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// position the sprite on the center of the screen
	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	auto closeItem = MenuItemImage::create(
		"cwbg_a.png",
		"cwbg.png",
		CC_CALLBACK_1(LostScene::menuCloseCallback2, this));
	closeItem->setPosition(Vec2(0.0, -closeItem->getContentSize().height));

	auto closeItem2 = MenuItemImage::create(
		"fhcd_a.png",
		"fhcd.png",
		CC_CALLBACK_1(LostScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(0.0, -closeItem->getContentSize().height*1.8));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, closeItem2, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2 - closeItem->getContentSize().height));
	this->addChild(menu, 1);

	return true;
}

void LostScene::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, HelloWorld::createScene()));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void LostScene::menuCloseCallback2(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, TollgateScene::createScene()));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

