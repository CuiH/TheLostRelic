#define MOVESPEED 8

#include "TollgateScene.h"
#include "Player.h"
#include "SimpleMoveController.h"
#include "HelloWorldScene.h"
#include "SecondScene.h"
#include "cocos-ext.h"
#include "WinScene.h"
#include "LostScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
Scene* TollgateScene::createScene() {
	auto scene = Scene::create();
	auto layer = TollgateScene::create();
	scene->addChild(layer);

	return scene;
}

bool TollgateScene::init() {
	if (!Layer::init()) {
		return false;
	}

	fflag = false;

	count = 500;

	/* 加载Tiled地图，添加到场景中 */
	TMXTiledMap* map = TMXTiledMap::create("version.tmx");

	this->addChild(map);

	/* 加载玩家 */
	addPlayer(map);
	return true;
}

void TollgateScene::upClick(Ref*, TouchEventType type) {
	if (!mPlayer->isViewing()) {
		switch (type) {
			case TouchEventType::TOUCH_EVENT_BEGAN:
				moveControll->setiXSpeed(0);
				moveControll->setiYSpeed(MOVESPEED);
				moveControll->setAble(true);
				mPlayer->setanimation(3);
				mPlayer->setDirection(3);
				break;
			case TouchEventType::TOUCH_EVENT_MOVED:
				break;
			case TouchEventType::TOUCH_EVENT_ENDED:
				moveControll->setiXSpeed(0);
				moveControll->setiYSpeed(0);
				moveControll->setAble(false);
				mPlayer->stopactions();
				mPlayer->setDirection(0);
				break;
			case TouchEventType::TOUCH_EVENT_CANCELED:
				break;
		}
	}
}

void TollgateScene::downClick(Ref*, TouchEventType type) {
	if (!mPlayer->isViewing()) {
		switch (type) {
			case TouchEventType::TOUCH_EVENT_BEGAN:
				moveControll->setiXSpeed(0);
				moveControll->setiYSpeed(-MOVESPEED);
				moveControll->setAble(true);
				mPlayer->setanimation(3);
				mPlayer->setDirection(4);
				break;
			case TouchEventType::TOUCH_EVENT_MOVED:
				break;
			case TouchEventType::TOUCH_EVENT_ENDED:
				moveControll->setiXSpeed(0);
				moveControll->setiYSpeed(0);
				moveControll->setAble(false);
				mPlayer->stopactions();
				mPlayer->setDirection(0);
				break;
			case TouchEventType::TOUCH_EVENT_CANCELED:
				break;
		}
	}
}


void TollgateScene::leftClick(Ref*, TouchEventType type) {
	if (!mPlayer->isViewing()) {
		switch (type) {
			case TouchEventType::TOUCH_EVENT_BEGAN:
				moveControll->setiXSpeed(-MOVESPEED);
				moveControll->setiYSpeed(0);
				moveControll->setAble(true);
				mPlayer->setanimation(2);
				mPlayer->setDirection(1);

				break;
			case TouchEventType::TOUCH_EVENT_MOVED:
				break;
			case TouchEventType::TOUCH_EVENT_ENDED:
				moveControll->setiXSpeed(0);
				moveControll->setiYSpeed(0);
				moveControll->setAble(false);
				mPlayer->stopactions();
				mPlayer->setDirection(0);
				if (mPlayer->getFlag()) {
					addMessage();
				}
				mPlayer->resetFlag();
				break;
			case TouchEventType::TOUCH_EVENT_CANCELED:
				break;
		}
	}
}


void TollgateScene::rightClick(Ref*, TouchEventType type) {
	if (!mPlayer->isViewing()) {
		switch (type) {
			case TouchEventType::TOUCH_EVENT_BEGAN:
				moveControll->setiXSpeed(MOVESPEED);
				moveControll->setiYSpeed(0);
				moveControll->setAble(true);
				mPlayer->setanimation(1);
				mPlayer->setDirection(2);

				break;
			case TouchEventType::TOUCH_EVENT_MOVED:
				break;
			case TouchEventType::TOUCH_EVENT_ENDED:
				moveControll->setiXSpeed(0);
				moveControll->setiYSpeed(0);
				moveControll->setAble(false);
				mPlayer->stopactions();
				mPlayer->setDirection(0);
				if (mPlayer->getFlag()) {
					addMessage();
				}
				mPlayer->resetFlag();
				break;
			case TouchEventType::TOUCH_EVENT_CANCELED:
				break;
		}
	}
}

void TollgateScene::addMessage() {
	Size visibleSize = Director::getInstance()->getVisibleSize();

	message = Layer::create();
	Sprite* mes = Sprite::create("paper.png");
	mes->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	message->addChild(mes,4);
	
	auto button = MenuItemImage::create(
		"know.png",
		"know_click.png",
		CC_CALLBACK_1(TollgateScene::menuCloseCallback, this));
	button->setScale(0.5);
	button->setPosition(visibleSize.width / 2, 120);
	auto menu = Menu::create(button, NULL);
	menu->setPosition(0, 0);
	message->addChild(menu, 5);
	addChild(message);
	fflag = true;
	changeMenu();
}

void TollgateScene::menuCloseCallback(Ref* sender) {
	removeChild(message);
}

void TollgateScene::menuCallback(Ref* sender) {
	if (fflag) {
		Point pos = mPlayer->getTagPosition();
		if (mPlayer->putOutFire(pos.x, pos.y)) {
			resetMenu();
			mymap->removeChild(mfire);
		}
	}
}

void TollgateScene::changeMenu() {
	removeChild(menu2);
	auto button1 = MenuItemImage::create(
		"water.png",
		"water_white.png",
		CC_CALLBACK_1(TollgateScene::menuCallback, this));
	button1->setScale(0.5);
	button1->setPosition(60, 40);

	auto button2 = MenuItemImage::create(
		"map_white.png",
		"map_white.png",
		CC_CALLBACK_1(TollgateScene::menuCallback, this));
	button2->setScale(0.5);
	button2->setPosition(140, 40);

	menu2 = Menu::create(button1,button2, NULL);
	menu2->setPosition(0, 0);
	this->addChild(menu2, 1);
}

void TollgateScene::resetMenu() {
	removeChild(menu2);
	auto button1 = MenuItemImage::create(
		"water_white.png",
		"water_white.png",
		CC_CALLBACK_1(TollgateScene::menuCallback, this));
	button1->setScale(0.5);
	button1->setPosition(60, 40);

	auto button2 = MenuItemImage::create(
		"map_white.png",
		"map_white.png",
		CC_CALLBACK_1(TollgateScene::menuCallback, this));
	button2->setScale(0.5);
	button2->setPosition(140, 40);

	menu2 = Menu::create(button1,button2, NULL);
	menu2->setPosition(0, 0);
	this->addChild(menu2, 1);
}

void TollgateScene::addPlayer(TMXTiledMap* map) {
	mymap = map;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 创建精灵 */
	Sprite* playerSprite = Sprite::create("men_right.png");

	/* 将精灵绑定到玩家对象上 */
	mPlayer = Player::create();
	mPlayer->bindSprite(playerSprite);

	mPlayer->setTiledMap(map);

	/* 加载对象层 */
	TMXObjectGroup* objGroup = map->getObjectGroup("objects");

	/* 加载玩家坐标对象 */
	ValueMap playerPointMap = objGroup->getObject("PlayerPoint");
	float playerX = playerPointMap.at("x").asFloat();
	float playerY = playerPointMap.at("y").asFloat();

	/* 设置玩家坐标 */
	mPlayer->setPosition(Point(playerX, playerY));

	/* 将玩家添加到地图 */
	map->addChild(mPlayer, 4);

	// 加入火坑
	ValueMap firePointMap = objGroup->getObject("FirePoint");
	float fireX = firePointMap.at("x").asFloat();
	float fireY = firePointMap.at("y").asFloat();

	mfire = Sprite::create("fire1.png");

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("fire.plist", "fire.png");
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameList;
	/* 创建精灵帧对象，添加到列表里 */
	for (int i = 1; i <= 8; i++) {
		frame = frameCache->getSpriteFrameByName(StringUtils::format("fire%d.png", i));
		frameList.pushBack(frame);
	}
	/* 根据精灵帧对象创建动画对象 */
	Animation* animation = Animation::createWithSpriteFrames(frameList);
	animation->setLoops(-1);    // 循环播放
	animation->setDelayPerUnit(0.08f);  // 每帧播放间隔
	/* 创建动画动作 */
	Animate* animate = Animate::create(animation);
	mfire->runAction(animate);

	mfire->setPosition(Point(fireX, fireY));

	map->addChild(mfire, 4);

	//添加胜利传送门
	ValueMap WinPointMap = objGroup->getObject("WinPoint");
	float winX = WinPointMap.at("x").asFloat();
	float winY = WinPointMap.at("y").asFloat();

	mwin = Sprite::create("light1.png");
	mwin->setScale(1.3);

	SpriteFrameCache* frameCacheWin = SpriteFrameCache::getInstance();
	frameCacheWin->addSpriteFramesWithFile("light1.plist", "light1.png");
	SpriteFrame* frameWin = NULL;
	Vector<SpriteFrame*> frameListWin;
	/* 创建精灵帧对象，添加到列表里 */
	for (int i = 1; i <= 15; i++) {
		frameWin = frameCacheWin->getSpriteFrameByName(StringUtils::format("%d.png", i));
		frameListWin.pushBack(frameWin);
	}
	/* 根据精灵帧对象创建动画对象 */
	Animation* animationwin = Animation::createWithSpriteFrames(frameListWin);
	animationwin->setLoops(-1);    // 循环播放
	animationwin->setDelayPerUnit(0.08f);  // 每帧播放间隔
	/* 创建动画动作 */
	Animate* animatewin = Animate::create(animationwin);
	mwin->runAction(animatewin);

	mwin->setPosition(Point(winX, winY));

	map->addChild(mwin, 6);


	// 添加按钮
	Button* buttonUp = Button::create();
	buttonUp->setTouchEnabled(true);
	buttonUp->loadTextures("Icons_up.png", "Icons_up_active.png", "");
	buttonUp->setPosition(Point(900, 80));
	buttonUp->addTouchEventListener(this, toucheventselector(TollgateScene::upClick));
	this->addChild(buttonUp, 1);

	Button* buttonDown = Button::create();
	buttonDown->setTouchEnabled(true);
	buttonDown->loadTextures("Icons_down.png", "Icons_down_active.png", "");
	buttonDown->setPosition(Point(900, 20));
	buttonDown->addTouchEventListener(this, toucheventselector(TollgateScene::downClick));
	this->addChild(buttonDown, 1);

	Button* buttonLeft = Button::create();
	buttonLeft->setTouchEnabled(true);
	buttonLeft->loadTextures("Icons_left.png", "Icons_left_active.png", "");
	buttonLeft->setPosition(Point(860, 50));
	buttonLeft->addTouchEventListener(this, toucheventselector(TollgateScene::leftClick));
	this->addChild(buttonLeft, 1);

	Button* buttonRight = Button::create();
	buttonRight->setTouchEnabled(true);
	buttonRight->loadTextures("Icons_right.png", "Icons_right_active.png", "");
	buttonRight->setPosition(Point(940, 50));
	buttonRight->addTouchEventListener(this, toucheventselector(TollgateScene::rightClick));
	this->addChild(buttonRight, 1);

	resetMenu();


	// add back
	auto item4 = MenuItemImage::create("back2.png", "back2_click.png", CC_CALLBACK_1(TollgateScene::menuItem4Callback, this));

	auto menu22 = Menu::create(item4, NULL);
	menu22->setPosition(48, visibleSize.height - item4->getContentSize().height + 10);
	this->addChild(menu22, 1);

	//add progressbar
	auto loadBg = Sprite::create("pg_down.png");//进程条的底图
	loadBg->setPosition(Point(visibleSize.width / 2, visibleSize.height-50));
	this->addChild(loadBg, 4);

	auto progressSprite = Sprite::create("pg_up.png");
	pT = ProgressTimer::create(progressSprite);
	pT->setType(ProgressTimer::Type::BAR);
	pT->setMidpoint(Point(0, 0));
	pT->setBarChangeRate(Point(1, 0));
	pT->setPercentage(100.0f);//设置初始值为100
	pT->setPosition(Point(visibleSize.width / 2, visibleSize.height -49));
	this->addChild(pT, 4);

	// add count label
	timeLabel = Label::createWithTTF("50s", "fonts/Marker Felt.ttf", 20);
	timeLabel->setColor(Color3B::GREEN);
	timeLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height-50));
	this->addChild(timeLabel, 4);

	//add scheduler
	schedule(schedule_selector(TollgateScene::updateTime), 0.1f);

	/* ------------ 创建玩家移动控制器 -------------- */
	moveControll = SimpleMoveController::create();
	moveControll->setiXSpeed(0);
	moveControll->setiYSpeed(0);

	/* 控制器要添加到场景中才能获得update事件 */
	this->addChild(moveControll);

	/* 设置控制器到主角身上 */
	mPlayer->setController(moveControll);

	mPlayer->viewWholeMap();
}

void TollgateScene::menuItem4Callback(cocos2d::Ref* pSender) {
	auto scene = SecondScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void TollgateScene::updateTime(float dt) {
	if (!mPlayer->isViewing()) {
		count -= 1;
		char t[10];
		sprintf(t, "%ds", count/10);
		timeLabel->setString(t);
		pT->setPercentage(pT->getPercentage() - 0.2);
		if (pT->getPercentage() < 1) {
			this->stopAllActions();
			auto scene = LostScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
	}
}
