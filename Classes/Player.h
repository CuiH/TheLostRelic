#ifndef _Player_H_
#define _Player_H_

#include "Entity.h"

class Player: public Entity {
	public:
	CREATE_FUNC(Player);
	virtual bool init();

	virtual bool setTagPosition(int x, int y) override;
	void run();
	void setViewPointByPlayer();
	void setTiledMap(TMXTiledMap* map);
	bool getFlag();
	void resetFlag();

	void setanimation(int direction);
	void stopactions();
	bool putOutFire(int x, int y);
	void setDirection(int);
	void viewWholeMap();
	void viewEachPoint(float time);
	bool isViewing();

	private:
	int direction; //1-left,2-right,3-up,4-down,0-none
	TMXTiledMap* m_map;
	SpriteFrameCache* frameCache;
	bool flagg;
	/* 检测碰撞的地图层 */
	TMXLayer* meta;
	/* 将像素坐标转换为地图格子坐标*/
	Point tileCoordForPosition(Point pos);
	Point nowPos;
	bool viewed;
	bool viewingCol;
	/* 1=正向，2=反向 */
	bool viewingRowRight;
	int nowCol;
	int delay;
	bool delaying;
};
#endif