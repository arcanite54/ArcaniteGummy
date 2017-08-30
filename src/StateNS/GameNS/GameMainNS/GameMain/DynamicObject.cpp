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
//����protected�֐�
//==============================================
//camera�𒆐S�Ƃ����`��
void DynamicObject::standardDraw(const Vector2* _camera, const Vector2* _pos, const int& _image, const bool& _direction) const
{

	if (//�����X�e�[�W�ɂ��Ȃ����return
		_pos->raw_x / MAP_WIDTH_RATE() != _camera->raw_x / MAP_WIDTH_RATE() ||
		_pos->raw_y / MAP_HEIGHT_RATE() != _camera->raw_y / MAP_HEIGHT_RATE()
		)
	return;

	//��ʓ��ɂ��Ȃ����return
	if (abs(_pos->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, _image, true, _direction);
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


//==============================================
//�����v���C�x�[�g�֐�
//==============================================

//����Ȃ��̂͂Ȃ�



}
}
}