#include "PlayerChild.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

PlayerChild::PlayerChild(float _move, float _jump, int _jumpCount, int _hp) : Character(_hp),
maxMoveSpeed(_move),
maxJumpPower(_jump),
maxJumpCount(_jumpCount)
{
	this->moveSpeed = 0.0f;
	this->jumpPower = 0.0f;
	this->nowJumpCount = 0;
	this->prePush = false;
}

void PlayerChild::draw() const
{
	DrawFormatString(0, 60, MyData::WHITE, "Mokou");

	int draw_x = 320 + (p->pos_x - camera->pos_x) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y - camera->pos_y) / MyData::vectorRate;

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, img, true);
	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);

	draw_other();
}


//================================================
//����private�֐�
//================================================
void PlayerChild::standardMove(const Stage* _stage)
{
	move(_stage);
}

//�ړ�
void PlayerChild::move(const Stage* _stage)
{
	int dx = 0;
	int dy = 0;

	//����
	if (Input_RIGHT())dx += (int)(moveSpeed * MyData::vectorRate);
	if (Input_LEFT())dx -= (int)(moveSpeed * MyData::vectorRate);

	//�W�����v
	if (Input_JUMP() && !prePush)jumpPower = maxJumpPower;

	//�c�ړ�
	dy += gravity() - jump();

	dx = getHorizontalDiffer(_stage, dx);
	dy = getVerticalDiffer(_stage, dy);

	p->pos_x += dx;
	p->pos_y += dy;


	//�J�����ʒu���X�V	
	*camera = Vector2(
		max(320, min(MyData::MAP_WIDTH  - 320, p->x())),
		max(240, min(MyData::MAP_HEIGHT - 240, p->y()))
	);
	
	prePush = Input_JUMP();
}


int PlayerChild::getHorizontalDiffer(const Stage* _stage, const int _dx) const
{
	//�΂߃u���b�N�̏ꍇ�͂��̂܂ܕԂ�

	//�`�b�v�̏㔼���̐^��
	RawVector2 pos = RawVector2(p->pos_x, p->pos_y - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;


	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if(_stage->isSlant(chipType))return _dx;



	//�ʂ�Ȃ��u���b�N�Ȃ�return 0

	//�`�b�v�̐^��
	pos = RawVector2(p->pos_x + _dx, p->pos_y);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̏㔼���̐^��
	pos = RawVector2(p->pos_x + _dx, p->pos_y - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;
	

	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x + _dx, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}

int PlayerChild::getVerticalDiffer(const Stage* _stage, const int _dy) const
{
	//�����
	if (jumpPower >= 0.5f)
	{
		//�΂߃u���b�N�Ȃ�

		//�`�b�v�̏�[
		RawVector2 pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);
		Stage::ChipType chipType = _stage->getChipType(pos);

		if (chipType == _stage->TYPE_UP_SLANT_LEFT)
		{
			/* ���̃u���b�N

			____
			\==|
			 \=|
			  \|

			*/

			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - MyData::PLAYER_CHIP_WIDTH_RATE() + p->pos_x % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
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

			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - p->pos_x % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
			return dy;
		}

		//�`�b�v�̏㔼���̒��S
		pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);
		chipType = _stage->getChipType(pos);

		if (chipType == _stage->TYPE_UP_SLANT_LEFT)
		{
			/* ���̃u���b�N

			____
			\==|
			 \=|
			  \|

			*/

			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - MyData::PLAYER_CHIP_WIDTH_RATE() + p->pos_x % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
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

			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - p->pos_x % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
			return dy;
		}

		//�`�b�v�̏�[��菭����
		pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 2 - 1);
		chipType = _stage->getChipType(pos);

		//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
		if (_stage->isRigid_up(chipType))
		{
			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT)) * MyData::vectorRate;
	
			//�V��ɓ������Ă���ꍇ��fixToStageHeight�̌��ʂ������ς�邩�璲��
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
			return dy;
		}

		return _dy;
	}
	//�����܂ŏ�����̔���



	//������
	//�`�b�v�̍ŉ��[��菭����
	RawVector2 pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - 1);
	Stage::ChipType	chipType= _stage->getChipType(pos / MyData::vectorRate);
	
	//�΂߃u���b�N�Ȃ�
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		/* ���̃u���b�N�Ȃ�

		|\
		|=\
		|==\

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + p->pos_x % MyData::CHIP_WIDTH_RATE();
	}

	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		/* ���̃u���b�N�Ȃ�

		  /|
		 /=|
		/==|

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x % MyData::CHIP_WIDTH_RATE();
	}


	//�`�b�v�̉������̒��S
	pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 4);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//�΂߃u���b�N�Ȃ�
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		/* ���̃u���b�N�Ȃ�

		|\
		|=\
		|==\

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + p->pos_x % MyData::CHIP_WIDTH_RATE();
	}

	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		/* ���̃u���b�N�Ȃ�

		  /|
		 /=|
		/==|

		*/

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x % MyData::CHIP_WIDTH_RATE();
	}



	//�`�b�v�̍ŉ��[
	pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
	if (_stage->isRigid_down(chipType))
	{
		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	}

	return _dy;
}

//�W�����v�ł̈ړ��ʂ�Ԃ�
//���̒l�ŏ����
int PlayerChild::jump()
{
	jumpPower = max(0.0f, jumpPower - 1.0f);
	return (int)(jumpPower * MyData::vectorRate);
}

//������d�͂�Ԃ�
//���̒l�ŉ�����
int PlayerChild::gravity()
{
	//for Debug
	//���̂܂܂����Ȃ�constexpr��
	return 7 * MyData::vectorRate;
}


}
}
}