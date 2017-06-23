#include "PlayerChild.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

PlayerChild::PlayerChild(float _move, float _jump) : 
maxMoveSpeed(_move),
maxJumpPower(_jump)
{
	this->moveSpeed = 0.0f;
	this->jumpPower = 0.0f;
	now_jumping = false;
}

void PlayerChild::standardMove(const Stage* _stage)
{
	move(_stage);

	//avoidSinking(_stage);
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
	if (Input_JUMP())jumpPower = maxJumpPower;

	//�c�ړ�
	dy += gravity() - jump();

	p->pos_x += getHorizontalDiffer(_stage, dx);
	p->pos_y += getVerticalDiffer(_stage, dy);
}


int PlayerChild::getHorizontalDiffer(const Stage* _stage, int _dx) const
{
	//�ړ����chipType��get����...


	//�΂߃u���b�N�̏ꍇ�͂��̂܂ܕԂ�
	RawVector2 pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	if(_stage->isSlant(chipType))return _dx;


	pos = RawVector2(p->pos_x, p->pos_y - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;
	


	//�ʂ�Ȃ��u���b�N�Ȃ�return 0

	//�`�b�v�̐^��
	pos = RawVector2(p->pos_x + _dx, p->pos_y);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̏�
	pos = RawVector2(p->pos_x + _dx, p->pos_y - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̉�
	pos = RawVector2(p->pos_x + _dx, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}

int PlayerChild::getVerticalDiffer(const Stage* _stage, int _dy) const
{
	//�����
	if (jumpPower >= 0.5f)
	{
		RawVector2 pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);
		Stage::ChipType chipType = _stage->getChipType(pos);


		//�΂߃u���b�N�Ȃ�
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

	//������
	RawVector2 pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - 1);
	Stage::ChipType	chipType = _stage->getChipType(pos / MyData::vectorRate);

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

	pos = RawVector2(p->pos_x, p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
	if (_stage->isRigid_down(chipType))
	{
		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	}


	return _dy;
}


/*
//�߂荞�݉��
void PlayerChild::avoidSinking(const Stage* _stage)
{
	//���̈ړ����x
	int moveDiffer = (int)moveSpeed + 1;

	Vector2 pos1;
	Vector2 pos2;

	Stage::ChipType chipType1;
	Stage::ChipType chipType2;

	//�E�L�[��������Ă���Ƃ��ɓǂ܂��
	if (Input_RIGHT())
	{
		//X���E����
		pos1 = Vector2(p->x() + moveDiffer, p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);
		pos2 = Vector2(p->x() + moveDiffer, p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//���蔲�����Ȃ��Ȃ�ʒu������
		if (_stage->isRigid(chipType1) || _stage->isRigid(chipType2))
		{
			p->pos_x = (p->x() / MyData::CHIP_WIDTH * MyData::CHIP_WIDTH + MyData::PLAYER_CHIP_WIDTH * 3 / 4) * MyData::vectorRate;
		}
	}

	//���L�[��������Ă���Ƃ��ɓǂ܂��
	else if (Input_LEFT())
	{
		//X��������
		pos1 = Vector2(p->x() - moveDiffer, p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);
		pos2 = Vector2(p->x() - moveDiffer, p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//���蔲�����Ȃ��Ȃ�ʒu������
		if (_stage->isRigid(chipType1) || _stage->isRigid(chipType2))
		{
			p->pos_x = (p->x() / MyData::CHIP_WIDTH * MyData::CHIP_WIDTH + MyData::PLAYER_CHIP_WIDTH / 4) * MyData::vectorRate;
		}
	}

	//�W�����v���ɓǂ܂��
	if (jumpPower >= 0.5f)
	{
		//Y�������
		pos1 = Vector2(p->x() - moveDiffer, p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);
		pos2 = Vector2(p->x() + moveDiffer, p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//���蔲�����Ȃ��Ȃ�ʒu������
		if (_stage->isRigid(chipType1) && _stage->isRigid(chipType2))
		{
			p->pos_y = (p->y() / MyData::CHIP_HEIGHT * MyData::CHIP_HEIGHT + MyData::PLAYER_CHIP_HEIGHT  / 2) * MyData::vectorRate;
		}
	}
	else //�W�����v���łȂ��Ƃ��ɓǂ܂��
	{
		//Y��������
		pos1 = Vector2(p->x() - moveDiffer + 1, p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);
		pos2 = Vector2(p->x() + moveDiffer - 1, p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//��ɏ���u���b�N�Ȃ�ʒu������
		if (_stage->isRide(chipType1) && _stage->isRide(chipType2))
		{
			p->pos_y = (p->y() / MyData::CHIP_HEIGHT * MyData::CHIP_HEIGHT) * MyData::vectorRate;
		}
	}

	if (jumpPower <= 0.5f)
	{
		//�΂߃u���b�N�ɑ΂��鏈��
		pos1 = Vector2(p->x(), p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);
		pos2 = Vector2(p->x(), p->y() + MyData::PLAYER_CHIP_HEIGHT / 2 - 1);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		int s_dy = 0;

		if (_stage->isSlant(chipType1))
		{
			s_dy = (chipType1 == _stage->TYPE_SLANT_LEFT) ? p->x() % MyData::CHIP_HEIGHT : 32 - p->x() % MyData::CHIP_HEIGHT;
			p->pos_y = (p->y() / MyData::CHIP_HEIGHT * MyData::CHIP_HEIGHT + s_dy) * MyData::vectorRate;
		}
		else if (_stage->isSlant(chipType2))
		{
			p->pos_y -= gravity();
			s_dy = (chipType2 == _stage->TYPE_SLANT_LEFT) ? p->x() % MyData::CHIP_HEIGHT : 32 - p->x() % MyData::CHIP_HEIGHT;
			p->pos_y = (p->y() / MyData::CHIP_HEIGHT * MyData::CHIP_HEIGHT + s_dy) * MyData::vectorRate;
		}
	}

}
//*/

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
	return 5 * MyData::vectorRate;
}


}
}
}