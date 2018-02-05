#include "Player.h"
#include "WinScene.h"
#include "LostScene.h"

bool Player::init() {
	flagg = false;
	direction = 0;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	nowPos = Point(visibleSize.width*0.5, visibleSize.height / 2);

	viewed = false;
	viewingRowRight = true;
	viewingCol = false;
	nowCol = 0;
	delay = 0;
	delaying = false;

	return true;
}

void Player::stopactions() {
	m_sprite->stopAllActions();
}

void Player::setDirection(int dir) {
	direction = dir;
}

void Player::setanimation(int direction) {
	if (direction == 1) {
		frameCache->destroyInstance();
		frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("man.plist", "man.png");
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*> frameList;
		/* 创建精灵帧对象，添加到列表里 */
		for (int i = 1; i <= 8; i++) {
			frame = frameCache->getSpriteFrameByName(StringUtils::format("right_%d.png", i));
			frameList.pushBack(frame);
		}
		/* 根据精灵帧对象创建动画对象 */
		Animation* animation = Animation::createWithSpriteFrames(frameList);
		animation->setLoops(-1);    // 循环播放
		animation->setDelayPerUnit(0.08f);  // 每帧播放间隔
		/* 创建动画动作 */
		Animate* animate = Animate::create(animation);
		m_sprite->stopAllActions();
		m_sprite->runAction(animate);
	} else if (direction == 2) {
		frameCache->destroyInstance();
		frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("man.plist", "man.png");
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*> frameList;
		/* 创建精灵帧对象，添加到列表里 */
		for (int i = 1; i <= 8; i++) {
			frame = frameCache->getSpriteFrameByName(StringUtils::format("left_%d.png", i));
			frameList.pushBack(frame);
		}
		/* 根据精灵帧对象创建动画对象 */
		Animation* animation = Animation::createWithSpriteFrames(frameList);
		animation->setLoops(-1);    // 循环播放
		animation->setDelayPerUnit(0.08f);  // 每帧播放间隔
		/* 创建动画动作 */
		Animate* animate = Animate::create(animation);
		m_sprite->stopAllActions();
		m_sprite->runAction(animate);
	} else {
		frameCache->destroyInstance();
		frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("man.plist", "man.png");
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*> frameList;
		/* 创建精灵帧对象，添加到列表里 */
		for (int i = 1; i <= 8; i++) {
			frame = frameCache->getSpriteFrameByName(StringUtils::format("up_%d.png", i));
			frameList.pushBack(frame);
		}
		/* 根据精灵帧对象创建动画对象 */
		Animation* animation = Animation::createWithSpriteFrames(frameList);
		animation->setLoops(-1);    // 循环播放
		animation->setDelayPerUnit(0.08f);  // 每帧播放间隔
		/* 创建动画动作 */
		Animate* animate = Animate::create(animation);
		m_sprite->stopAllActions();
		m_sprite->runAction(animate);
	}
}

bool Player::putOutFire(int x, int y) {
	Size spriteSize = m_sprite->getContentSize();

	int flag = false;

	/* 获得当前主角前方坐标在地图中的格子位置 */
	Point tiledPos = tileCoordForPosition(Point(x, y));
	/* 获取地图格子的唯一标识 */

	// 火的坐标，前一格
	if (tiledPos.x == 44 && tiledPos.y == 3) {
		meta->removeTileAt(Point(43, 3));
		flag = true;
	}
	return flag;
}

void Player::setViewPointByPlayer() {
	if (m_sprite == NULL) {
		return;
	}
	Layer* parent = (Layer*)getParent();

	/* 地图方块数量 */
	Size mapTiledNum = m_map->getMapSize();

	/* 地图单个格子大小 */
	Size tiledSize = m_map->getTileSize();

	/*地图大小 */
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* 屏幕大小 */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 主角坐标 */
	Point spritePos = getPosition();

	/* 如果主角坐标小于屏幕的一半，则取屏幕中点坐标，否则取主角的坐标 */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/* 如果X、Y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出
	屏幕造成出现黑边的极限坐标） */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/* 目标点 */
	Point destPos = Point(x, y);

	/* 屏幕中点 */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* 计算屏幕中点和所要移动的目的点之间的距离 */
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);
}

void Player::viewWholeMap() {
	schedule(schedule_selector(Player::viewEachPoint), 0.01f);
}

bool Player::isViewing() {
	if (viewed) return false;
	else return true;
}

void Player::viewEachPoint(float time) {
	if (viewed == true) {
		return;
	}

	if (delay < 100) {
		delay++;
		return;
	}

	Layer* parent = (Layer*)getParent();

	/* 地图方块数量 */
	Size mapTiledNum = m_map->getMapSize();

	/* 地图单个格子大小 */
	Size tiledSize = m_map->getTileSize();

	/* 地图大小 */
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* 屏幕大小 */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* 当前浏览到的点 */
	if (nowPos.x > mapSize.width - visibleSize.width / 2) {
		if (!viewingCol) nowCol += 1;
		viewingCol = true;
		viewingRowRight = false;
	} else if (nowPos.x < visibleSize.width*0.47) {
		if (!viewingCol) nowCol += 1;
		viewingCol = true;
		viewingRowRight = true;
	}

	if ((nowPos.y >(nowCol + 0.5)*visibleSize.height) || (nowPos.y > (mapSize.height - visibleSize.height/2))) {
		viewingCol = false;
	}
	
	if (viewingCol) {
		nowPos.y += 10;
	} else if (viewingRowRight) {
		nowPos.x += 10;
	} else {
		nowPos.x -= 10;
	}

	if (nowPos.x > mapSize.width - visibleSize.width / 2 && nowPos.y > mapSize.height - visibleSize.height / 2) {
		nowPos.x = 0;
		nowPos.y = 0;
		viewed = true;
	}

	/* 如果主角坐标小于屏幕的一半，则取屏幕中点坐标，否则取主角的坐标 */
	float x = std::max(nowPos.x, visibleSize.width / 2);
	float y = std::max(nowPos.y, visibleSize.height / 2);

	/* 如果X、Y的坐标大于右上角的极限值，则取极限值的坐标（极限值是指不让地图超出
	屏幕造成出现黑边的极限坐标） */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/* 目标点 */
	Point destPos = Point(x, y);

	/* 屏幕中点 */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* 计算屏幕中点和所要移动的目的点之间的距离 */
	Point viewPos = centerPos - destPos;

	parent->setPosition(viewPos);
}

bool Player::getFlag() {
	return flagg;
}

void Player::resetFlag() {
	flagg = false;
}

bool Player::setTagPosition(int x, int y) {
	/* -----------------判断前面是否不可通行---------------- */
	/* 取主角前方的坐标 */
	Size spriteSize = m_sprite->getContentSize();
	Point dstPos;

	int flag = 0;

	//1-left,2-right,3-up,4-down,0-none
	if (direction == 1) {
		dstPos = Point(x - spriteSize.width / 2+20, y - spriteSize.height / 2);
	} else if (direction == 2){
		dstPos = Point(x + spriteSize.width / 2-20, y - spriteSize.height / 2);
	} else if (direction == 3) {
		dstPos = Point(x, y + 70-spriteSize.height / 2-5);
	} else if (direction == 4) {
		dstPos = Point(x, y - spriteSize.height / 2);
	}

	/* 获得当前主角前方坐标在地图中的格子位置 */
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	
	/* 获取地图格子的唯一标识 */
	int tiledGid = meta->getTileGIDAt(tiledPos);

	/* 不为0，代表存在这个格子 */
	if (tiledGid != 0) {
		/*
		获取该地图格子的所有属性，目前我们只有一个Collidable属性
		格子是属于meta层的，但同时也是属于整个地图的，所以在获取格子的所有属性
		时，通过格子唯一标识在地图中取得
		*/
		Value properties = m_map->getPropertiesForGID(tiledGid);
		ValueMap propertiesMap = properties.asValueMap();

		if (propertiesMap.find("Collidable") != propertiesMap.end()) {
			/* 取得格子的Collidable属性值 */
			Value prop = propertiesMap.at("Collidable");
			// if (prop.asString().compare("true")==0&&isJumping==false) {
			if (prop.asString().compare("true") == 0) {
				return false;
			}
		}

		if (propertiesMap.find("fire") != propertiesMap.end()) {
			/* 取得格子的Collidable属性值 */
			Value prop = propertiesMap.at("fire");
			// if (prop.asString().compare("true")==0&&isJumping==false) {
			if (prop.asString().compare("true") == 0) {
				return false;
			}
		}

		if (propertiesMap.find("food") != propertiesMap.end()) {
			/* 取得格子的food属性值，判断是否为true，如果是，则让格子上的物体消失 */
			Value prop = properties.asValueMap().at("food");
			if (prop.asString().compare("true") == 0) {
				/* 从障碍物层清除当前格子的物体 */
				TMXLayer* barrier = m_map->getLayer("barrier");
				barrier->removeTileAt(tiledPos);
				meta->removeTileAt(tiledPos);
			}
			flag = 1;
			flagg = true;
		}
		if (propertiesMap.find("win") != propertiesMap.end()) {
			/* 取得格子的food属性值，判断是否为true，如果是，则让格子上的物体消失 */
			Value prop = properties.asValueMap().at("win");
			if (prop.asString().compare("true") == 0) {
				/* 取得格子的win属性值，判断是否为true，如果是，则游戏胜利，跳转到胜利场景 */
				Director::getInstance()->replaceScene(WinScene::createScene());
			}
		}
	}

	Entity::setTagPosition(x, y);

	/* 以主角为中心移动地图 */
	setViewPointByPlayer();

	return flag;
}

void Player::setTiledMap(TMXTiledMap* map) {
	m_map = map;

	/* 保存meta图层的引用 */
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}

Point Player::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = (0+pos.x) / tiledSize.width;

	/* Cocos2d-x的默认Y坐标是由下至上的，所以要做一个相减操作 */
	int y = (1750 - pos.y) / tiledSize.height;

	return Point(x, y);
}