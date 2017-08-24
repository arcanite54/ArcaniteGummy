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
	this->direction = false;
	this->animationTime = 0;

	post_x = MyData::MAP_WIDTH / 2;
	post_y = MyData::MAP_HEIGHT / 2;

}

void PlayerChild::draw() const
{
	
	int draw_x = 320 + (p->pos_x() - camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y() - camera->pos_y()) / MyData::vectorRate;

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, direction);
	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);

	draw_other();
	draw_changingAnimation(draw_x, draw_y);

	//for Debug
	DrawBox(60, 20, 60 + hpController.getHP() * 5, 50, MyData::GREEN, true);
	DrawFormatString(0, 50, MyData::BLACK, "%d %d", p->x(), p->y());
	DrawFormatString(0, 70, MyData::BLACK, "%d %d", collision->p->x(), collision->p->y());
}


//================================================
//����protected�֐�
//================================================
void PlayerChild::standardAction(const Stage* _stage)
{
	move(_stage);
	changeCharacter();
	processDamage();
}

//�ύX�A�j���[�V�������I����ăL�����ύX�ł��邩�ǂ���
bool PlayerChild::canChangeCharacter()
{
	return animationTime > 30;
}



//================================================
//����private�֐�
//================================================

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

void PlayerChild::draw_changingAnimation(int _draw_x, int _draw_y) const
{
	if (animationTime == 0)return;
	DrawCircle(_draw_x, _draw_y, animationTime * 2, MyData::WHITE);
}

void PlayerChild::processDamage()
{
	if (damaged)
	{
		++damagedTime;
		if(damagedTime < 3)hittedAction();
		if (damagedTime > 60)
		{
			damaged = false;
			damagedTime = 0;
		}
	}
}

void PlayerChild::hittedAction()
{
	//�m�b�N�o�b�N
	float dx = direction ? 10.0f : -10.0f;
	this->moveCharacter(dx, 0.0f);
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
	}
	else if (dx_onScreen > MyData::MAP_WIDTH / 2)
	{
		nextStageMove = GameMain::MOVE_LEFT;
	}
	else if (dy_onScreen > MyData::MAP_HEIGHT / 2)
	{
		nextStageMove = GameMain::MOVE_UP;
	}
	else if (dy_onScreen < -MyData::MAP_HEIGHT / 2)
	{
		nextStageMove = GameMain::MOVE_DOWN;
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