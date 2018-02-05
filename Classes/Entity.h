#ifndef _Entity_H_
#define _Entity_H_

#include "cocos2d.h"
using namespace cocos2d;

#include "ControllerListener.h"
#include "Controller.h"
class Entity : public Node, public ControllerListener {
public:
    /* �󶨾������ */
    void bindSprite(Sprite* sprite);

    /* ���ÿ����� */
    void setController(Controller* controller);

    /* ʵ��SimpleMoveListener�ӿڵķ��� */
    virtual bool setTagPosition(int x, int y);
    virtual Point getTagPosition();
	Sprite* m_sprite;
protected:
    
    Controller* m_controller;
};

#endif