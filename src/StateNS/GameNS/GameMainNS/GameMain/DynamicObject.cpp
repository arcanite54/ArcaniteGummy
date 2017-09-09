#include "DynamicObject.h"


#include "Collision.h"
#include "Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


DynamicObject::DynamicObject(int _x, int _y, int _w, int _h, float _jump,int _jumpCount):
maxJumpPower(_jump),
maxJumpCount(_jumpCount)
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
void DynamicObject::standardDraw(const Vector2* _camera, const Vector2* _pos, const int& _image, const bool& _direction) const
{

	//TODO ������ const Vector2* _pos ���Ă���ˁ[�����
	/*
	if (//�����X�e�[�W�ɂ��Ȃ����return
		_pos->raw_x / MAP_WIDTH_RATE() != _camera->raw_x / MAP_WIDTH_RATE() ||
		_pos->raw_y / MAP_HEIGHT_RATE() != _camera->raw_y / MAP_HEIGHT_RATE()
		)
		return;
	//*/
	
	//��ʓ��ɂ��Ȃ����return
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, _image, true, _direction);
}

//camera�𒆐S�Ƃ����`�� scale����o�[�W����
void DynamicObject::standardDraw(const Vector2* _camera, const Vector2* _pos, const double& scale, const int& _image, const bool& _direction) const
{
	/*
	if (//�����X�e�[�W�ɂ��Ȃ����return
		_pos->raw_x / MAP_WIDTH_RATE() != _camera->raw_x / MAP_WIDTH_RATE() ||
		_pos->raw_y / MAP_HEIGHT_RATE() != _camera->raw_y / MAP_HEIGHT_RATE()
	)
	return;
	//*/

	//��ʓ��ɂ��Ȃ����return
	if (abs(_pos->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

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

int DynamicObject::getTopDiffer(const Stage* _stage, const int _dy, bool _isPlayer) const
{
	//�΂߃u���b�N�Ȃ�

	//�`�b�v�̏�[
	RawVector2 pos = RawVector2(p->x(), p->y() - height / 2);
	Stage::ChipType chipType = _stage->getChipType(pos, _isPlayer);

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
	pos = RawVector2(p->x(), p->y() - height / 4);
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

	//�`�b�v�̏�[��菭����
	pos = RawVector2(p->x(), p->y() - height / 2 - 1);
	chipType = _stage->getChipType(pos, _isPlayer);

	//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
	if (_stage->isRigid_up(chipType))
	{
		int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - height)) * MyData::vectorRate;

		//�V��ɓ������Ă���ꍇ��fixToStageHeight�̌��ʂ������ς�邩�璲��
		if (pos.pos_y < 0)dy -= (height * MyData::vectorRate) / 2;
		return dy;
	}

	return _dy;
}


//========================================================================
// ����protected�֐�
//========================================================================
int DynamicObject::getBottomDiffer(const Stage* _stage, const int _dy, bool _isPlayer) const
{
	//������
	//�`�b�v�̍ŉ��[��菭����
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + (height * vectorRate) / 2 - 1);
	Stage::ChipType	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

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


	//�`�b�v�̉������̒��S
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 4);
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


	//�`�b�v�̍ŉ��[
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * vectorRate) / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

	//TODO 
	//_stage->getTopPosition�͍������ł���

	//�ړ�������̃`�b�v�̍ŉ��[
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * vectorRate) / 2 + _dy);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);

	//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
	if (_stage->isRigid_down(chipType))
	{
		const int quart_height = PLAYER_CHIP_HEIGHT_RATE() / 4;
		int differ = _stage->getTopPosition(p, quart_height * 3) - fixToVectorHeight(p->pos_y() + quart_height * 3);
		differ %= (quart_height * 2);
		return fixToVectorHeight(p->pos_y() + quart_height) - p->pos_y() + differ;
	}

	return _dy;
}

int DynamicObject::getHorizontalDiffer(const Stage* _stage, const int _dx, bool _isPlayer) const
{
	//�΂߃u���b�N�̏ꍇ�͂��̂܂ܕԂ�

	//�`�b�v�̏㔼���̐^��
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() - (height * MyData::vectorRate) / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (_stage->isSlant(chipType))return _dx;


	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (_stage->isSlant(chipType))return _dx;


	//�ʂ�Ȃ��u���b�N�Ȃ�return 0

	//�`�b�v�̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y());
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̏㔼���̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() - (height * MyData::vectorRate) / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate, _isPlayer);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() + (height * MyData::vectorRate) / 2 - MyData::vectorRate);
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