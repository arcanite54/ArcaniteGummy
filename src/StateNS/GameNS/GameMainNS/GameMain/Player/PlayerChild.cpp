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

	avoidSinking(_stage);
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

	//�c�ړ�
	int nextX = max(0, min(MyData::MAP_WIDTH  * MyData::vectorRate, p->pos_x + dx)) / MyData::vectorRate;
	int nextY = max(0, min(MyData::MAP_HEIGHT * MyData::vectorRate, p->pos_y + dy)) / MyData::vectorRate;

	//�ړ��悪������ꏊ�Ȃ� �̌`��

	//X������
	//���̍s���悪�ʂ��Ȃ�
	Stage::ChipType chipType = _stage->getChipType(Vector2(nextX, p->y()));
	if (!_stage->isRigid(chipType))
	{
		p->pos_x = nextX * MyData::vectorRate;
	}

	//Y������
	chipType = _stage->getChipType(Vector2(p->x(), nextY));
	if (!_stage->isRigid(chipType))
	{
		p->pos_y = nextY * MyData::vectorRate;
	}
}

//�߂荞�݉��
void PlayerChild::avoidSinking(const Stage* _stage)
{
	Vector2 pos1;
	Vector2 pos2;

	Stage::ChipType chipType1;
	Stage::ChipType chipType2;

	//�W�����v���ɓǂ܂��
	if (jumpPower >= 0.5f)
	{
		//Y�������
		Vector2 pos1 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);
		Vector2 pos2 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() - MyData::PLAYER_CHIP_HEIGHT / 2);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//���蔲�����Ȃ��Ȃ�ʒu������
		if (_stage->isRigid(chipType1) && _stage->isRigid(chipType2))
		{
			p->pos_y = (p->y() / MyData::PLAYER_CHIP_HEIGHT * MyData::PLAYER_CHIP_HEIGHT + MyData::PLAYER_CHIP_HEIGHT + 1) * MyData::vectorRate;
		}
	}
	else //�W�����v���łȂ��Ƃ��ɓǂ܂��
	{
		//Y��������
		pos1 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);
		pos2 = Vector2(p->x() + MyData::PLAYER_CHIP_WIDTH / 4 - 1, p->y() + MyData::PLAYER_CHIP_HEIGHT / 2);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//��ɏ���u���b�N�Ȃ�ʒu������
		if (_stage->isRide(chipType1) || _stage->isRide(chipType2))
		{
			p->pos_y = (p->y() / MyData::PLAYER_CHIP_HEIGHT * MyData::PLAYER_CHIP_HEIGHT + MyData::PLAYER_CHIP_HEIGHT / 2) * MyData::vectorRate;
		}
	}

	//�E�L�[��������Ă���Ƃ��ɓǂ܂��
	if (Input_RIGHT())
	{
		//X���E����
		pos1 = Vector2(p->x() + MyData::PLAYER_CHIP_WIDTH / 4, p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);
		pos2 = Vector2(p->x() + MyData::PLAYER_CHIP_WIDTH / 4, p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//���蔲�����Ȃ��Ȃ�ʒu������
		if (_stage->isRigid(chipType1) && _stage->isRigid(chipType2))
		{
			p->pos_x = (p->x() / MyData::PLAYER_CHIP_WIDTH * MyData::PLAYER_CHIP_WIDTH + MyData::PLAYER_CHIP_WIDTH * 3 / 4) * MyData::vectorRate;
		}
	}

	//���L�[��������Ă���Ƃ��ɓǂ܂��
	else if (Input_LEFT())
	{
		//X��������
		pos1 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);
		pos2 = Vector2(p->x() - MyData::PLAYER_CHIP_WIDTH / 4, p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);

		chipType1 = _stage->getChipType(pos1);
		chipType2 = _stage->getChipType(pos2);

		//���蔲�����Ȃ��Ȃ�ʒu������
		if (_stage->isRigid(chipType1) && _stage->isRigid(chipType2))
		{
			p->pos_x = (p->x() / MyData::PLAYER_CHIP_WIDTH * MyData::PLAYER_CHIP_WIDTH + MyData::PLAYER_CHIP_WIDTH / 4) * MyData::vectorRate;
		}
	}

	//�΂߃u���b�N�ɑ΂��鏈��
	pos1 = Vector2(p->x(), p->y() + MyData::PLAYER_CHIP_HEIGHT / 2 - 1);
	pos2 = Vector2(p->x(), p->y() + MyData::PLAYER_CHIP_HEIGHT / 4);

	chipType1 = _stage->getChipType(pos1);
	chipType2 = _stage->getChipType(pos2);

	if (_stage->isSlant(chipType1) || _stage->isSlant(chipType2))
	{
		p->pos_y -= ((p->x() % 32) * MyData::vectorRate);
	}
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
	return 5 * MyData::vectorRate;
}


}
}
}