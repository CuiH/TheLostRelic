#include "SecondScene.h"
#include "HelloWorldScene.h"
#include "cocos2d.h"
#include "RotateMenu.h"
#include "TollgateScene.h"
#include "WinScene.h"
#include "LostScene.h"

USING_NS_CC;

Scene * SecondScene::createScene() {
	auto scene = Scene::create();
	auto layer = SecondScene::create();
	scene->addChild(layer);
	return scene;
}

bool SecondScene::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a rotation menu

	auto item1 = MenuItemImage::create("level1_click.png", "level1.png", CC_CALLBACK_1(SecondScene::menuItem1Callback, this));
	auto item2 = MenuItemImage::create("level2_click.png", "level2.png", CC_CALLBACK_1(SecondScene::menuItem2Callback, this));
	auto item3 = MenuItemImage::create("level3_click.png", "level3.png", CC_CALLBACK_1(SecondScene::menuItem3Callback, this));

	RotateMenu *menu = RotateMenu::create();

	menu->addMenuItem(item1);
	menu->addMenuItem(item2);
	menu->addMenuItem(item3);

	menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 1.85));
	this->addChild(menu, 2);


	// add back
	auto item4 = MenuItemImage::create("back2.png", "back2_click.png", CC_CALLBACK_1(SecondScene::menuItem4Callback, this));

	auto menu2 = Menu::create(item4, NULL);
	menu2->setPosition(48, visibleSize.height - item4->getContentSize().height+10);
	this->addChild(menu2, 1);


	for (int i = 0; i < 5; i++) {
		sprite[i] = Sprite::create("B2.png");
		sprite[i]->setAnchorPoint(Vec2(0.5f, 0.5f));
		sprite[i]->setPosition(visibleSize / 2);
		this->addChild(sprite[i]);
	}
	hideAllSprite();

	// add "background" splash screen"
	auto bgsprite = Sprite::create("bgg.png");

	// position the sprite on the center of the screen
	bgsprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(bgsprite, 0);
	return true;
}

void SecondScene::popScene(Ref* pSender) {
	Director::getInstance()->popScene();
}

// rotate
void SecondScene::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void SecondScene::menuItem1Callback(cocos2d::Ref* pSender) {
	hideAllSprite();
	sprite[0]->setVisible(true);
	Director::getInstance()->pushScene(
		TransitionCrossFade::create(1.0f, TollgateScene::createScene()));
}
void SecondScene::menuItem2Callback(cocos2d::Ref* pSender) {
	hideAllSprite();
	sprite[1]->setVisible(true);
}
void SecondScene::menuItem3Callback(cocos2d::Ref* pSender) {
	hideAllSprite();
	sprite[2]->setVisible(true);
}

void SecondScene::menuItem4Callback(cocos2d::Ref* pSender) {
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

void SecondScene::hideAllSprite() {
	for (auto p : sprite) {
		if (p->isVisible())
			p->setVisible(false);
	}
}