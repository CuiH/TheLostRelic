#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "TollgateScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	/*add music*/
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
		"Fate.mp3", true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // add "background" splash screen"
    auto sprite = Sprite::create("bg.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	addMenu();

    return true;
}

void HelloWorld::addMenu() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//主页菜单-》 1.开始游戏 2.关卡选择 3.关于我们 4.退出
	auto closeItem = MenuItemImage::create(
		"quickgame.png",
		"quickgame_click.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Vec2(0.0, -closeItem->getContentSize().height*2.5));

	auto closeItem2 = MenuItemImage::create(
		"yxwf_a.png",
		"yxwf.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback2, this));
	closeItem2->setPosition(Vec2(0.0, -closeItem->getContentSize().height));

	auto closeItem3 = MenuItemImage::create(
		"aboutus.png",
		"aboutus_click.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback3, this));
	closeItem3->setPosition(Vec2(0.0, -closeItem->getContentSize().height * 4));

	auto closeItem4 = MenuItemImage::create(
		"exitgame.png",
		"exitgame_click.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback4, this));
	closeItem4->setPosition(Vec2(0.0, -closeItem->getContentSize().height * 5.5));

	// create menu, it's an autorelease object
	menu = Menu::create(closeItem2, closeItem, closeItem3, closeItem4, NULL);
	menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - closeItem->getContentSize().height * 7));
	this->addChild(menu, 1);
}

void HelloWorld::addMessage() {
	removeChild(menu);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	message = Layer::create();
	Sprite* mes = Sprite::create("paper2.png");
	mes->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	message->addChild(mes, 4);

	auto button = MenuItemImage::create(
		"know.png",
		"know_click.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback5, this));
	button->setScale(0.5);
	button->setPosition(visibleSize.width / 2, 120);
	auto menu = Menu::create(button, NULL);
	menu->setPosition(0, 0);
	message->addChild(menu, 5);
	addChild(message, 8);
}

void HelloWorld::addMessage2() {
	removeChild(menu);

	Size visibleSize = Director::getInstance()->getVisibleSize();

	message2 = Layer::create();
	Sprite* mes = Sprite::create("paper3.png");
	mes->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	message2->addChild(mes, 4);

	auto button = MenuItemImage::create(
		"know.png",
		"know_click.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback6, this));
	button->setScale(0.5);
	button->setPosition(visibleSize.width / 2, 120);
	auto menu = Menu::create(button, NULL);
	menu->setPosition(0, 0);
	message2->addChild(menu, 5);
	addChild(message2, 8);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->replaceScene(
		TransitionCrossFade::create(1.0f, SecondScene::createScene()));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuCloseCallback2(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	addMessage();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuCloseCallback3(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	addMessage2();
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuCloseCallback4(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuCloseCallback5(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	addMenu();
	removeChild(message);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::menuCloseCallback6(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif
	addMenu();
	removeChild(message2);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
