#include "Character.h"
#include "Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Character::Character(int hp, int x, int y, int w, int h, float jump, int jumpCount):
Character(hp, x, y, w, h, false, jump, jumpCount)
{ }

Character::Character(int _hp, int _x, int _y, int _w, int _h, bool _isPlayer, float _jump,int _jumpCount) : 
DynamicObject(_x, _y, _w, _h,_jump,_jumpCount),
hpController(HPController(this, _hp))
{
	width = _w;
	height = _h;
	next_dx = next_dy = 0;

	isPlayer = _isPlayer;
	damaged = false;
	damagedTime = 0;
}

Character::~Character()
{

}

//�L������dx, dy�����ړ�������
void Character::moveCharacter(float _dx, float _dy)
{
	this->next_dx += (int)(_dx * vectorRate);
	this->next_dy += (int)(_dy * vectorRate);
}

//�L������x, y�̈ʒu�Ɉړ�������
void Character::warpCharacter(float _x, float _y)
{
	p->raw_x = (int)(_x * vectorRate);
	p->raw_y = (int)(_y * vectorRate);
}

int Character::getTopDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const { return DynamicObject::getTopDiffer(_stage, dy, _moveLeft, true); }
int Character::getBottomDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const { return DynamicObject::getBottomDiffer(_stage, dy, _moveLeft, true); }
int Character::getHorizontalDiffer(const StageChild* _stage, const int dx, bool _moveUp) const { return DynamicObject::getHorizontalDiffer(_stage, dx, _moveUp, true); }



}
}
}