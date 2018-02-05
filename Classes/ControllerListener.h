#ifndef _ControllerListener_H_
#define _ControllerListener_H_

#include "cocos2d.h"

using namespace cocos2d;

class ControllerListener {
public:
    /* ����Ŀ������ */
    virtual bool setTagPosition(int x, int y) = 0;

    /* ��ȡĿ������ */
    virtual Point getTagPosition() = 0;
};

#endif