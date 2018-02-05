#include "SimpleMoveController.h"
#include "TollgateScene.h"

bool SimpleMoveController::init() {
	this->m_iXSpeed=0;
	this->m_iYSpeed=0;
	/* ÿһ֡��Ҫ����update����������Ҫ�������� */
	abled = false;

	this->scheduleUpdate();

	return true;
}

void SimpleMoveController::update(float dt) {
	if (m_controllerListener==NULL) {
		return;
	}

	/* �����ƶ������x����ֵ */
	Point pos=m_controllerListener->getTagPosition();
	pos.x+=m_iXSpeed;
	pos.y+=m_iYSpeed;
	if (abled)
		m_controllerListener->setTagPosition(pos.x, pos.y);
}

void SimpleMoveController::setAble(bool flag) {
	abled = flag;
}

void SimpleMoveController::setiXSpeed(int iSpeed) {
	this->m_iXSpeed=iSpeed;
}
void SimpleMoveController::setiYSpeed(int iSpeed) {
	this->m_iYSpeed=iSpeed;
}