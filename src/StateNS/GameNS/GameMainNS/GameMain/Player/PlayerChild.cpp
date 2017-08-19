#include "PlayerChild.h"
#include "..\Stage.h"

//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

PlayerChild::PlayerChild(int _x, int _y, float _move, float _jump, int _jumpCount, int _hp) : 
Character(_hp, _x, _y, MyData::PLAYER_CHIP_WIDTH, MyData::PLAYER_CHIP_HEIGHT),
maxMoveSpeed(_move),
maxJumpPower(_jump),
maxJumpCount(_jumpCount)
{
	initialize();
}

void PlayerChild::initialize()
{
	this->moveSpeed = maxMoveSpeed;
	this->jumpPower = 0.0f;
	this->nowJumpCount = 0;
	this->prePush = false;

	post_x = MyData::MAP_WIDTH / 2;
	post_y = MyData::MAP_HEIGHT / 2;

	animationTime = 0;
}

void PlayerChild::draw() const
{
	
	int draw_x = 320 + (p->pos_x() - camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y() - camera->pos_y()) / MyData::vectorRate;

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);

	draw_other();
	draw_changingAnimation(draw_x, draw_y);

	//for Debug
	DrawBox(60, 20, 60 + hpController.getHP() * 5, 50, MyData::GREEN, true);
	DrawFormatString(0, 50, MyData::BLACK, "%d %d", p->x(), p->y());
	DrawFormatString(0, 70, MyData::BLACK, "%d %d", collision->p->x(), collision->p->y());
}


//================================================
//����private�֐�
//================================================
void PlayerChild::standardAction(const Stage* _stage)
{
	move(_stage);
	changeCharacter();
}

//�L�����ύX�A�j���[�V����
void PlayerChild::changeCharacter(/*Chara��enum next*/)
{
	if (Input_CHANGE())
	{
		animationTime = max(animationTime, 1);
	}
	if (animationTime == 0)return;

	++animationTime;

}


//�ύX�A�j���[�V�������I����ăL�����ύX�ł��邩�ǂ���
bool PlayerChild::canChangeCharacter()
{
	return animationTime > 30;
}

void PlayerChild::draw_changingAnimation(int _draw_x, int _draw_y) const
{
	if (animationTime == 0)return;
	DrawCircle(_draw_x, _draw_y, animationTime * 2, MyData::WHITE);
}

//�ړ�
void PlayerChild::move(const Stage* _stage)
{
	//�L������㒆�Ȃ�return
	if (animationTime > 0)return;

	int dx = next_dx;
	int dy = next_dy;

	next_dx = next_dy = 0;

	//����
	if (Input_RIGHT())dx += (int)(moveSpeed * MyData::vectorRate);
	if (Input_LEFT())dx -= (int)(moveSpeed * MyData::vectorRate);

	//�n��ɂ���Ȃ�
	if (jumpPower == 0 && isOnGround(_stage))
	{
		nowJumpCount = 0;
	}

	//�W�����v
	if (Input_JUMP() && !prePush && nowJumpCount < maxJumpCount)
	{
		jumpPower = maxJumpPower;
		nowJumpCount++;
	}

	//�c�ړ�
	dy += gravity() - jump();

	dx = getHorizontalDiffer(_stage, dx);
	dy = jumpPower > 0.5f ? getTopDiffer(_stage, dy) : getBottomDiffer(_stage, dy);

	//�V��ɓ���������
	if (abs(dy) <= 1000)jumpPower = 0;

	p->raw_x += dx;
	p->raw_y += dy;

	int dx_onScreen = p->x() - post_x;
	int dy_onScreen = p->y() - post_y;

	nextStageMove = GameMain::MOVE_NONE;
	if (dx_onScreen < -MyData::MAP_WIDTH / 2)
	{
		nextStageMove = GameMain::MOVE_RIGHT;
		//p->pos_x() -= (MyData::MAP_WIDTH * MyData::vectorRate);
	}
	else if (dx_onScreen > MyData::MAP_WIDTH / 2)
	{
		nextStageMove = GameMain::MOVE_LEFT;
		//p->pos_x() += MyData::MAP_WIDTH * MyData::vectorRate;
	}
	else if (dy_onScreen > MyData::MAP_HEIGHT / 2)
	{
		nextStageMove = GameMain::MOVE_UP;
		//p->pos_y() += MyData::MAP_HEIGHT * MyData::vectorRate;
	}
	else if (dy_onScreen < -MyData::MAP_HEIGHT / 2)
	{
		nextStageMove = GameMain::MOVE_DOWN;
		//p->pos_y() %= MyData::MAP_HEIGHT;
	}
	post_x = p->x();
	post_y = p->y();


	//�J�����ʒu���X�V	
	*camera = Vector2(
		max(320, min(MyData::MAP_WIDTH  - 320, p->x())),
		max(240, min(MyData::MAP_HEIGHT - 240, p->y()))
	);
	
	prePush = Input_JUMP();
}

bool PlayerChild::isOnGround(const Stage* _stage)
{
	//pos�̓L�����̍ŉ��[���ЂƂ�
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	
	
	//�E��Ɍ������΂߃u���b�N�Ȃ�
	if (chipType == Stage::ChipType::TYPE_DOWN_SLANT_RIGHT)
	{
		pos.pos_y -= (MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE());
		chipType = _stage->getChipType(pos / MyData::vectorRate);
	}

	//����Ɍ������΂߃u���b�N�Ȃ�
	else if (chipType == Stage::ChipType::TYPE_DOWN_SLANT_LEFT)
	{
		pos.pos_y -= p->pos_x() % MyData::CHIP_WIDTH_RATE();
		chipType = _stage->getChipType(pos / MyData::vectorRate);
	}

	return chipType != Stage::ChipType::TYPE_BACK;
}

/*
int PlayerChild::getHorizontalDiffer(const Stage* _stage, const int _dx) const
{
	//�΂߃u���b�N�̏ꍇ�͂��̂܂ܕԂ�

	//�`�b�v�̏㔼���̐^��
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (_stage->isSlant(chipType))return _dx;


	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if(_stage->isSlant(chipType))return _dx;



	//�ʂ�Ȃ��u���b�N�Ȃ�return 0

	//�`�b�v�̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y());
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;


	//�`�b�v�̏㔼���̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() - MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 + MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;
	

	//�`�b�v�̉������̐^��
	pos = RawVector2(p->pos_x() + _dx, p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - MyData::vectorRate);
	chipType = _stage->getChipType(pos / MyData::vectorRate);
	if (chipType == _stage->TYPE_RIGID)return 0;

	return _dx;
}
//*/

/*
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
			// ���̃u���b�N
			// ____
			// \==|
			//  \=|
			//   \|
			
	
			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - MyData::PLAYER_CHIP_WIDTH_RATE() + p->pos_x() % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
			return dy;
		}
		if (chipType == _stage->TYPE_UP_SLANT_RIGHT)
		{
			//���̃u���b�N
			// _____
			// |==/
			// |=/
			// |/


			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - p->pos_x() % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
			return dy;
		}

		//�`�b�v�̏㔼���̒��S
		pos = RawVector2(p->x(), p->y() - MyData::PLAYER_CHIP_HEIGHT / 4);
		chipType = _stage->getChipType(pos);

		if (chipType == _stage->TYPE_UP_SLANT_LEFT)
		{
			//���̃u���b�N
			// ____
			// \==|
			//  \=|
			//   \|

			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - MyData::PLAYER_CHIP_WIDTH_RATE() + p->pos_x() % MyData::PLAYER_CHIP_WIDTH_RATE();
			if (pos.pos_y < 0)dy -= MyData::PLAYER_CHIP_HEIGHT_RATE() / 2;
			return dy;
		}
		if (chipType == _stage->TYPE_UP_SLANT_RIGHT)
		{
			//���̃u���b�N
			// _____
			// |==/
			// |=/
			// |/

			int dy = (MyData::fixToStageHeight(pos.pos_y) - (p->y() - MyData::PLAYER_CHIP_HEIGHT - 1)) * MyData::vectorRate - p->pos_x() % MyData::PLAYER_CHIP_WIDTH_RATE();
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
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - 1);
	Stage::ChipType	chipType= _stage->getChipType(pos / MyData::vectorRate);
	
	//�΂߃u���b�N�Ȃ�
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		//���̃u���b�N�Ȃ�
		// |\
		// |=\
		// |==\

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}

	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		//���̃u���b�N�Ȃ�
		//   /|
		//  /=|
		// /==|

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}


	//�`�b�v�̉������̒��S
	pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 4);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//�΂߃u���b�N�Ȃ�
	if (chipType == _stage->TYPE_DOWN_SLANT_LEFT)
	{
		//���̃u���b�N�Ȃ�
		// |\
		// |=\
		// |==\

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}

	if (chipType == _stage->TYPE_DOWN_SLANT_RIGHT)
	{
		//���̃u���b�N�Ȃ�
		//   /|
		//  /=|
		// /==|

		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2) + MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE();
	}



	//�`�b�v�̍ŉ��[
	pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	chipType = _stage->getChipType(pos / MyData::vectorRate);

	//�ړ��悪�ʂ�Ȃ��u���b�N�Ȃ�
	if (_stage->isRigid_down(chipType))
	{
		return MyData::fixToVectorHeight(pos.pos_y) - (p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2);
	}

	return _dy;
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
	return 7 * MyData::vectorRate;
}


}
}
}