#ifndef _Entity_H_
#define _Entity_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "ControllerListener.h"
#include "Controller.h"
class Entity : public Node, public ControllerListener {
public:
    /* 绑定精灵对象 */
    void bindSprite(Sprite* sprite);

    /* 设置控制器 */
    void setController(Controller* controller);

    /* 实现SimpleMoveListener接口的方法 */
    virtual bool setTagPosition(int x, int y);
    virtual Point getTagPosition();
	Sprite* m_sprite;
protected:
    
    Controller* m_controller;
};

#endif