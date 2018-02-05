#include "WinScene.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* WinScene::createScene() {
    auto scene = Scene::create();
    auto layer = WinScene::create();
    scene->addChild(layer);

    return scene;
}

bool WinScene::init() {
    if (!Layer::init())
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();

	// add "background" splash screen"
	auto sprite = Sprite::create("youwin.png");
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// position the sprite on the center of the screen
	sprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// add the sprite as a child to this layer
	this->addChild(sprite, 0);

	auto closeItem = MenuItemImage::create(
		"fhcd_a.png",
		"fhcd.png",
		CC_CALLBACK_1(WinScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(0.0, -closeItem->getContentSize().height));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height/2 - closeItem->getContentSize().height));
	this->addChild(menu, 1);

	return true;
}

void WinScene::menuCloseCallback(Ref* pSender) {
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

