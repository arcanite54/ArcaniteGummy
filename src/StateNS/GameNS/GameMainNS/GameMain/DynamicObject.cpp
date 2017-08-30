#include "DynamicObject.h"


#include "Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


DynamicObject::DynamicObject(int _x, int _y, int _w, int _h,float _jump,int _jumpCount):
	maxJumpPower(_jump),
	maxJumpCount(_jumpCount)
{
	p = new Vector2(_x, _y);
	collision = new Collision(this, _w, _h);
	jumpPower = 0;
	nowJumpCount = 0;
}

DynamicObject::~DynamicObject()
{
	SAFE_DELETE(p);
	SAFE_DELETE(collision);
}

bool DynamicObject::isHit(const DynamicObject* _other) const
{
	return this->collision->isHit(_other->collision);
}


//�W�����v�ł̈ړ��ʂ�Ԃ�
//���̒l�ŏ����
int DynamicObject::jump()
{
	jumpPower = max(0.0f, jumpPower - 1.0f);
	return (int)(jumpPower * MyData::vectorRate);
}

//������d�͂�Ԃ�
//���̒l�ŉ�����
int DynamicObject::gravity()
{
	//for Debug
	//���̂܂܂����Ȃ�constexpr��
	return 7 * MyData::vectorRate;
}






//for Debug
int DynamicObject::getColliX() const
{
	return collision->p->raw_x;
}

//for Debug
int DynamicObject::getColliY() const
{
	return collision->p->raw_y;
}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================

//����Ȃ��̂͂Ȃ�



}
}
}