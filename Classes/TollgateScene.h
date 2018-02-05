#ifndef _TollgateScene_H_
#define _TollgateScene_H_

#include "SimpleMoveController.h"
#include "editor-support/cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d::ui;
using namespace cocostudio;

using namespace cocos2d;

class TollgateScene: public Layer {
	public:
	static Scene* createScene();
	CREATE_FUNC(TollgateScene);
	virtual bool init();
	void upClick(Ref*, TouchEventType type);
	void downClick(Ref*, TouchEventType type);
	void leftClick(Ref*, TouchEventType type);
	void rightClick(Ref*, TouchEventType type);
	void menuItem4Callback(cocos2d::Ref* pSender);
	void addMessage();
	void menuCloseCallback(Ref* sender);
	void menuCallback(Ref* sender);
	void resetMenu();
	void changeMenu();
	void updateTime(float);

	private:
	void addPlayer(TMXTiledMap* map);
	SimpleMoveController* moveControll;
	Player* mPlayer;
	Layer* message;
	Menu *menu2;
	Sprite* mfire;
	Sprite* mwin;
	TMXTiledMap* mymap;
	bool fflag;
	ProgressTimer* pT;
	Label* timeLabel;
	int count;
};
#endif