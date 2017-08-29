#include "Character.h"
#include "Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Character::Character(int _hp, int _x, int _y, int _w, int _h) : 
DynamicObject(_x, _y, _w, _h),
hpController(HPController(this, _hp))
{
	width = _w;
	height = _h;
	next_dx = next_dy = 0;

	damaged = false;
	damagedTime = 0;
}

Character::~Character()
{

}

//�L������dx, dy�����ړ�������
void Character::moveCharacter(float _dx, float _dy)
{
	this->next_dx += (int)(_dx * MyData::vectorRate);
	this->next_dy += (int)(_dy * MyData::vectorRate);
}

//�L������x, y�̈ʒu�Ɉړ�������
void Character::arrangeCharacter(float _x, float _y)
{
	p->raw_x = (int)(_x * MyData::vectorRate);
	p->raw_y = (int)(_y * MyData::vectorRate);
}


int Character::getTopDiffer(const Stage* _stage, const int _dy) const
{
	//�΂߃u���b�N�Ȃ�

	//�`�b�v�̏�[
	RawVector2 pos = RawVector2(p->x(), p->y() - height / 2);
	Stage::ChipType chipType = _stage->getChipType(pos);

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
	chipType = _stage->getChipType(pos);

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
	chipType = _stage->getChipType(pos);

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

int Character::getBottomDiffer(const Stage* _stage, const int _dy) const
{
	//������
	//�`�b�v�̍ŉ��[��菭����
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 2 - 1);
	Stage::ChipType	chipType = _stage->getChipType(pos / MyData::vectorRate);

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
	chipType = _stage->getChipType(pos / MyData::vectorRate);

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
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
	if (_stage->isRigid_down(chipType))
	{
		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + (height * MyData::vectorRate) / 2);
	}

	return _dy;
}

int Character::getHorizontalDiffer(const Stage* _stage, const int _dx) const
{
	//�΂߃u���b�N�̏ꍇ�͂��̂܂ܕԂ�

	//�`�b�v�̏㔼���̐^��
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() - (height * MyData::vectorRate) / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;


	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x(), p->pos_y() + (height * MyData::vectorRate) / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;



	//�ʂ�Ȃ��u���b�N�Ȃ�return 0

	//�`�b�v�̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y());
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̏㔼���̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() - (height * MyData::vectorRate) / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() + (height * MyData::vectorRate) / 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}

}
}
}