#pragma once

#include "..\..\..\..\Data.h"
#include "HPController.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


//���@�ƓG�ŋ��ʂ���s��
class Character
{
public:
	Character(int _hp) : hpController(HPController(this, _hp)){}
	virtual ~Character(){}
	virtual void damagedAction() = 0;
	HPController hpController;
};



}
}
}