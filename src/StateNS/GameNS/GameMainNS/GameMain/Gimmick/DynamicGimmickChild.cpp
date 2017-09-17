#include "DynamicGimmickChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


DynamicGimmickChild::DynamicGimmickChild(int _x, int _y, double _scale) : 
DynamicObject(_x, _y, (int)(32 * _scale), (int)(32 * _scale), 0, 0)
{
	dx = dy = 0;
	mDirection = false;
	scale = _scale;
	assert((_x + width / 2) % 32 == 0 && (_y + height / 2) % 32 == 0 && "DynamicGimmickの座標が (32 * n + 16) じゃないです");
}

DynamicGimmickChild::~DynamicGimmickChild()
{

}

//==============================================
//内部protected関数
//==============================================
void DynamicGimmickChild::standardMove(const Stage* _stage)
{
	dx = getHorizontalDiffer(_stage, dx, dy < 0);
	dy = ((dy < 0) ? getTopDiffer(_stage, dy, dx < 0) : getBottomDiffer(_stage, dy, dx < 0));
	
	this->p->raw_x += dx;
	this->p->raw_y += dy;
}


bool DynamicGimmickChild::rideOnGimmick(const Vector2* _player) const 
{
	return
		abs( p->y() - (_player->y() + PLAYER_CHIP_HEIGHT / 2) ) <= height / 32 * 16 &&
		abs( p->x() - _player->x() ) < width / 32 * 16;
}

bool DynamicGimmickChild::standardOverLap(const Vector2* _player) const
{
	int tmp_w = this->width  * vectorRate / 2;
	int tmp_h = this->height * vectorRate / 2;

	return
		this->p->raw_x - tmp_w < _player->raw_x &&
		this->p->raw_x + tmp_w > _player->raw_x &&
		this->p->raw_y - tmp_h < _player->raw_y &&
		this->p->raw_y + tmp_h > _player->raw_y;
}



int DynamicGimmickChild::getTopDiffer(const Stage* _stage, const int _dy, bool _moveLeft) const { return DynamicObject::getTopDiffer(_stage, _dy, _moveLeft, false); }
int DynamicGimmickChild::getBottomDiffer(const Stage* _stage, const int _dy, bool _moveLeft) const { return DynamicObject::getBottomDiffer(_stage, _dy, _moveLeft, false); }
int DynamicGimmickChild::getHorizontalDiffer(const Stage* _stage, const int _dx, bool _moveUp) const { return DynamicObject::getHorizontalDiffer(_stage, _dx, _moveUp, false); }




}
}
}