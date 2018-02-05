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
		/* ��������֡������ӵ��б��� */
		for (int i = 1; i <= 8; i++) {
			frame = frameCache->getSpriteFrameByName(StringUtils::format("right_%d.png", i));
			frameList.pushBack(frame);
		}
		/* ���ݾ���֡���󴴽��������� */
		Animation* animation = Animation::createWithSpriteFrames(frameList);
		animation->setLoops(-1);    // ѭ������
		animation->setDelayPerUnit(0.08f);  // ÿ֡���ż��
		/* ������������ */
		Animate* animate = Animate::create(animation);
		m_sprite->stopAllActions();
		m_sprite->runAction(animate);
	} else if (direction == 2) {
		frameCache->destroyInstance();
		frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("man.plist", "man.png");
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*> frameList;
		/* ��������֡������ӵ��б��� */
		for (int i = 1; i <= 8; i++) {
			frame = frameCache->getSpriteFrameByName(StringUtils::format("left_%d.png", i));
			frameList.pushBack(frame);
		}
		/* ���ݾ���֡���󴴽��������� */
		Animation* animation = Animation::createWithSpriteFrames(frameList);
		animation->setLoops(-1);    // ѭ������
		animation->setDelayPerUnit(0.08f);  // ÿ֡���ż��
		/* ������������ */
		Animate* animate = Animate::create(animation);
		m_sprite->stopAllActions();
		m_sprite->runAction(animate);
	} else {
		frameCache->destroyInstance();
		frameCache = SpriteFrameCache::getInstance();
		frameCache->addSpriteFramesWithFile("man.plist", "man.png");
		SpriteFrame* frame = NULL;
		Vector<SpriteFrame*> frameList;
		/* ��������֡������ӵ��б��� */
		for (int i = 1; i <= 8; i++) {
			frame = frameCache->getSpriteFrameByName(StringUtils::format("up_%d.png", i));
			frameList.pushBack(frame);
		}
		/* ���ݾ���֡���󴴽��������� */
		Animation* animation = Animation::createWithSpriteFrames(frameList);
		animation->setLoops(-1);    // ѭ������
		animation->setDelayPerUnit(0.08f);  // ÿ֡���ż��
		/* ������������ */
		Animate* animate = Animate::create(animation);
		m_sprite->stopAllActions();
		m_sprite->runAction(animate);
	}
}

bool Player::putOutFire(int x, int y) {
	Size spriteSize = m_sprite->getContentSize();

	int flag = false;

	/* ��õ�ǰ����ǰ�������ڵ�ͼ�еĸ���λ�� */
	Point tiledPos = tileCoordForPosition(Point(x, y));
	/* ��ȡ��ͼ���ӵ�Ψһ��ʶ */

	// ������꣬ǰһ��
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

	/* ��ͼ�������� */
	Size mapTiledNum = m_map->getMapSize();

	/* ��ͼ�������Ӵ�С */
	Size tiledSize = m_map->getTileSize();

	/*��ͼ��С */
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* ��Ļ��С */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* �������� */
	Point spritePos = getPosition();

	/* �����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ���ǵ����� */
	float x = std::max(spritePos.x, visibleSize.width / 2);
	float y = std::max(spritePos.y, visibleSize.height / 2);

	/* ���X��Y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ����
	��Ļ��ɳ��ֺڱߵļ������꣩ */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/* Ŀ��� */
	Point destPos = Point(x, y);

	/* ��Ļ�е� */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* ������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ��� */
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

	/* ��ͼ�������� */
	Size mapTiledNum = m_map->getMapSize();

	/* ��ͼ�������Ӵ�С */
	Size tiledSize = m_map->getTileSize();

	/* ��ͼ��С */
	Size mapSize = Size(
		mapTiledNum.width * tiledSize.width,
		mapTiledNum.height * tiledSize.height);

	/* ��Ļ��С */
	Size visibleSize = Director::getInstance()->getVisibleSize();

	/* ��ǰ������ĵ� */
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

	/* �����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ���ǵ����� */
	float x = std::max(nowPos.x, visibleSize.width / 2);
	float y = std::max(nowPos.y, visibleSize.height / 2);

	/* ���X��Y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ָ���õ�ͼ����
	��Ļ��ɳ��ֺڱߵļ������꣩ */
	x = std::min(x, mapSize.width - visibleSize.width / 2);
	y = std::min(y, mapSize.height - visibleSize.height / 2);

	/* Ŀ��� */
	Point destPos = Point(x, y);

	/* ��Ļ�е� */
	Point centerPos = Point(visibleSize.width / 2, visibleSize.height / 2);

	/* ������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ��� */
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
	/* -----------------�ж�ǰ���Ƿ񲻿�ͨ��---------------- */
	/* ȡ����ǰ�������� */
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

	/* ��õ�ǰ����ǰ�������ڵ�ͼ�еĸ���λ�� */
	Point tiledPos = tileCoordForPosition(Point(dstPos.x, dstPos.y));
	
	/* ��ȡ��ͼ���ӵ�Ψһ��ʶ */
	int tiledGid = meta->getTileGIDAt(tiledPos);

	/* ��Ϊ0���������������� */
	if (tiledGid != 0) {
		/*
		��ȡ�õ�ͼ���ӵ��������ԣ�Ŀǰ����ֻ��һ��Collidable����
		����������meta��ģ���ͬʱҲ������������ͼ�ģ������ڻ�ȡ���ӵ���������
		ʱ��ͨ������Ψһ��ʶ�ڵ�ͼ��ȡ��
		*/
		Value properties = m_map->getPropertiesForGID(tiledGid);
		ValueMap propertiesMap = properties.asValueMap();

		if (propertiesMap.find("Collidable") != propertiesMap.end()) {
			/* ȡ�ø��ӵ�Collidable����ֵ */
			Value prop = propertiesMap.at("Collidable");
			// if (prop.asString().compare("true")==0&&isJumping==false) {
			if (prop.asString().compare("true") == 0) {
				return false;
			}
		}

		if (propertiesMap.find("fire") != propertiesMap.end()) {
			/* ȡ�ø��ӵ�Collidable����ֵ */
			Value prop = propertiesMap.at("fire");
			// if (prop.asString().compare("true")==0&&isJumping==false) {
			if (prop.asString().compare("true") == 0) {
				return false;
			}
		}

		if (propertiesMap.find("food") != propertiesMap.end()) {
			/* ȡ�ø��ӵ�food����ֵ���ж��Ƿ�Ϊtrue������ǣ����ø����ϵ�������ʧ */
			Value prop = properties.asValueMap().at("food");
			if (prop.asString().compare("true") == 0) {
				/* ���ϰ���������ǰ���ӵ����� */
				TMXLayer* barrier = m_map->getLayer("barrier");
				barrier->removeTileAt(tiledPos);
				meta->removeTileAt(tiledPos);
			}
			flag = 1;
			flagg = true;
		}
		if (propertiesMap.find("win") != propertiesMap.end()) {
			/* ȡ�ø��ӵ�food����ֵ���ж��Ƿ�Ϊtrue������ǣ����ø����ϵ�������ʧ */
			Value prop = properties.asValueMap().at("win");
			if (prop.asString().compare("true") == 0) {
				/* ȡ�ø��ӵ�win����ֵ���ж��Ƿ�Ϊtrue������ǣ�����Ϸʤ������ת��ʤ������ */
				Director::getInstance()->replaceScene(WinScene::createScene());
			}
		}
	}

	Entity::setTagPosition(x, y);

	/* ������Ϊ�����ƶ���ͼ */
	setViewPointByPlayer();

	return flag;
}

void Player::setTiledMap(TMXTiledMap* map) {
	m_map = map;

	/* ����metaͼ������� */
	this->meta = m_map->getLayer("meta");
	this->meta->setVisible(false);
}

Point Player::tileCoordForPosition(Point pos) {
	Size mapTiledNum = m_map->getMapSize();
	Size tiledSize = m_map->getTileSize();

	int x = (0+pos.x) / tiledSize.width;

	/* Cocos2d-x��Ĭ��Y�������������ϵģ�����Ҫ��һ��������� */
	int y = (1750 - pos.y) / tiledSize.height;

	return Point(x, y);
}