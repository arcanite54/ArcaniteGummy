#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild
{
public:
	virtual ~EnemyChild() {};
	virtual void update() = 0;
	virtual void draw() = 0;

	//����2�͂���Ȃ���������Ȃ�
	virtual void move() = 0;
	virtual void attack() = 0;

	//Character�̊֐�
	virtual void damagedAction() = 0;

protected:
	Vector2* point;
};



}
}
}