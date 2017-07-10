#pragma once

#include "..\..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;

class GimmickChild
{
public:
	virtual ~GimmickChild() {};
	virtual void update(PlayerChild*) = 0;
	virtual void draw() const = 0;

	//��ʏ�ɕ\�����āA�X�V���邩�ǂ�����public�ϐ�
	bool isActive;
};




}
}
}