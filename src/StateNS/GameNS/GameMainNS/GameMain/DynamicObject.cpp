#include "DynamicObject.h"


#include "Collision.h"
#include "Stages\StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

DynamicObject::DynamicObject(int x, int y, int w, int h, float jump, int jumpCount) :
DynamicObject(x, y, w, h, jump, jumpCount, false)
{ }

DynamicObject::DynamicObject(int _x, int _y, int _w, int _h, float _jump,int _jumpCount, bool _hasChild):
maxJumpPower(_jump),
maxJumpCount(_jumpCount),
hasChild(_hasChild)
{
	p = new Vector2(_x, _y);
	collision = new Collision(this, _w, _h);
	this->width = _w;
	this->height = _h;
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
void DynamicObject::standardDraw(const Vector2* _camera, const int& _image, const bool& _direction) const
{

	//��ʓ��ɂ��Ȃ����return
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, _image, true, _direction);
}

//camera�𒆐S�Ƃ����`�� scale����o�[�W����
void DynamicObject::standardDraw(const Vector2* _camera, const double& scale, const int& _image, const bool& _direction) const
{

	//��ʓ��ɂ��Ȃ����return
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, scale, 0.0, _image, true, _direction);
}


//==============================================
//�ړ��֘A
//==============================================
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

int DynamicObject::getTopDiffer(const StageChild* _stage, const int _dy, bool _moveLeft, bool _isPlayer) const
{
	//width��32����Ȃ�������C���̕����炵�Čv�Z����K�v������
	int extraDiffer = (width - CHIP_WIDTH) / 2;
	if (_moveLeft)extraDiffer *= -1;

	//�΂߃u���b�N�Ȃ�

	//�`�b�v�̏�[
	RawVector2 pos = RawVector2(p->x() + extraDiffer, p->y() - height / 2);
	StageChild::ChipType chipType = _stage->getChipType(pos, _isPlayer);

	if (chipType == _stage->TYPE_UP_SLANT_LEFT)
	{
		/* ���̃u���b�N

		____
		\==|
		 \=|
		  \|

		*/

		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height - 1)) * MyData::vectorRate - (width * MyData::vectorRate) + p->pos_x() % (width * MyData::vectorRate);
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}
	if (chipType == _stage->TYPE_UP_SLANT_RIGHT)
	{
		/* ���̃u���b�N

		_____
		|==/
		|=/
		|/

		*/

		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height - 1)) * MyData::vectorRate - p->pos_x() % (width * MyData::vectorRate);
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}

	//�`�b�v�̏㔼���̒��S
	pos = RawVector2(p->x() + extraDiffer, p->y() - height / 4);
	chipType = _stage->getChipType(pos, _isPlayer);

	if (chipType == _stage->TYPE_UP_SLANT_LEFT)
	{
		/* ���̃u���b�N

		____
		\==|
		 \=|
		  \|

		*/

		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height - 1)) * MyData::vectorRate - (width * MyData::vectorRate) + p->pos_x() % (width * MyData::vectorRate);
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}
	if (chipType == _stage->TYPE_UP_SLANT_RIGHT)
	{
		/* ���̃u���b�N

		_____
		|==/
		|=/
		|/

		*/

		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height - 1)) * MyData::vectorRate - p->pos_x() % (width * MyData::vectorRate);
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}

	//�΂߂���Ȃ��`�b�v�ɑ΂���

	//�ړ�������̃`�b�v�^�C�v���擾
	pos = RawVector2(p->pos_x() + extraDiffer, p->pos_y() - (height * vectorRate) / 2 + _dy);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

	//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
	if (_stage->isRigid_up(chipType))
	{
		const int half_height = (height * vectorRate) / 2;
		return _stage->getBottomPosition(p, -half_height + _dy) - (p->pos_y() - half_height);
	}

	return _dy;
}


//========================================================================
// ����protected�֐�
//========================================================================
int DynamicObject::getBottomDiffer(const StageChild* _stage, const int _dy, bool _moveLeft, bool _isPlayer) const
{
	//width��32����Ȃ�������C���̕����炵�Čv�Z����K�v������
	int extraDiffer = vectorRate * (width - CHIP_WIDTH) / 2;
	if(_moveLeft)extraDiffer *= -1;

	//������
	//�`�b�v�̍ŉ��[��菭����
	RawVector2 pos = RawVector2(p->pos_x() + extraDiffer, p->pos_y() + (height * vectorRate) / 2 - 1);
	StageChild::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (this->onRigidBlock())chipType = StageChild::ChipType::TYPE_RIGID;

	//�΂߃u���b�N�Ȃ�
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		/* ���̃u���b�N�Ȃ�

		|\
		|=\
		|==\

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * vectorRate) / 2) + p->pos_x() % CHIP_WIDTH_RATE();
	}

	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		/* ���̃u���b�N�Ȃ�

		  /|
		 /=|
		/==|

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}


	//�`�b�v�̉������̒��S
	pos = RawVector2(p->pos_x() + extraDiffer, p->pos_y() + (height * MyData::vectorRate) / 4);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

	//�΂߃u���b�N�Ȃ�
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		/* ���̃u���b�N�Ȃ�

		|\
		|=\
		|==\

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2) + p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}

	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		/* ���̃u���b�N�Ȃ�

		  /|
		 /=|
		/==|

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}

	//�΂߂���Ȃ��`�b�v�ɑ΂���

	//TODO 
	//_stage->getTopPosition�͍������ł���

	//�ړ�������̃`�b�v�^�C�v���擾
	pos = RawVector2(p->pos_x() + extraDiffer, p->pos_y() + (height * vectorRate) / 2 + _dy);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (this->onRigidBlock())chipType = StageChild::ChipType::TYPE_RIGID;

	//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
	if (_stage->isRigid_down(chipType))
	{
		const int half_height = (height * vectorRate) / 2;
		return _stage->getTopPosition(p, half_height + _dy) - (p->pos_y() + half_height);
		/*
		����
		int differ = _stage->getTopPosition(p, half_height + _dy) - fixToVectorHeight(p->pos_y() + half_height + _dy);
		differ %= half_height;
		return fixToVectorHeight(p->pos_y() + half_height + _dy) - (p->pos_y() + half_height) + differ;
		*/
	}
	
	return _dy;
}

int DynamicObject::getHorizontalDiffer(const StageChild* _stage, const int _dx, bool _moveUp, bool _isPlayer) const
{
	//�΂߃u���b�N�̏ꍇ�͂��̂܂ܕԂ�

	//�`�b�v�̏㔼���̐^��
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() - (height * MyData::vectorRate) / 4);
	StageChild::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (_stage->isSlant(chipType))return _dx;


	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 4);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (_stage->isSlant(chipType))return _dx;


	//�ʂ�Ȃ��u���b�N�Ȃ�return 0

	//�`�b�v�̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y());
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̏㔼���̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() - (height * MyData::vectorRate) / 4);//2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() + (height * MyData::vectorRate) / 4);// 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================

//����Ȃ��̂͂Ȃ�



}
}
}