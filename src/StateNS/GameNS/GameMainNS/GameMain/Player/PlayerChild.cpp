#include "PlayerChild.h"

#include "..\Stage.h"

//for Debug
#include "..\Collision.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

PlayerChild::PlayerChild(int _x, int _y, float _move, float _jump, int _jumpCount, int _hp) :
Character(_hp, _x, _y, MyData::PLAYER_CHIP_WIDTH, MyData::PLAYER_CHIP_HEIGHT, true, _jump, _jumpCount),
maxMoveSpeed(_move)
{
	post_x = _x % MAP_WIDTH;
	post_y = _y % MAP_HEIGHT;
	this->camera = new Vector2(_x, _y);

	initialize();
	assert(*mImage != -1 && "���@�摜�ǂݍ��݃G���[");
}

PlayerChild::~PlayerChild()
{
	SAFE_DELETE(camera);

	for (auto& a : attacks)
	{
		SAFE_DELETE(a);
	}
	attacks.clear();
	attacks.shrink_to_fit();
}

void PlayerChild::initialize()
{
	this->moveSpeed = maxMoveSpeed;
	this->jumpPower = 0.0f;
	this->nowJumpCount = 0;
	this->prePush = false;
	this->direction = false;
	this->animationTime = 0;
	this->animeNum = 0;
	this->animeCount = 0;
	this->onGround = false;
	this->onLadder = false;
	this->actionState = ACT_NORMAL;
	this->canMove = true;
	this->prePushC = false;
	this->stopDynamics = StopType::TYPE_NONE;

	updateCamera();
}

void PlayerChild::draw() const
{
	int draw_x = MyData::CX + (p->x() - camera->x());
	int draw_y = MyData::CY + (p->y() - camera->y());

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage[animeNum], true);

	draw_other();
	draw_changingAnimation(draw_x, draw_y);

	//hpController.draw();
	//for Debug
	DrawBox(60, 20, 60 + hpController.getHP() * 5, 50, MyData::GREEN, true);

	//for Debug
	DrawCircle(draw_x, draw_y, 5, MyData::GREEN, true);
	//DrawBox(draw_x, draw_y, draw_x + 32, draw_y + 64, BLACK, false);
	DrawFormatString(2, 50, BLACK, "P: %d %d", p->raw_x, p->raw_y);
	DrawFormatString(2, 350, BLACK, "P: %d %d", p->x(), p->y());

}


//================================================
//����protected�֐�
//================================================
void PlayerChild::standardAction(const Stage* _stage)
{
	onGround = isOnGround(_stage);
	onLadder = isOnLadder(_stage);

	if (canMove)
	{
		in_right = Input_RIGHT();
		in_left  = Input_LEFT();
		in_up    = Input_UP();
		in_down  = Input_DOWN();
		in_jump  = Input_JUMP();
	}
	else
	{
		in_right = false;
		in_left  = false;
		in_up    = false;
		in_down  = false;
		in_jump  = false;
	}

	actCheck();
	animeNum = animation();

	move(_stage);
	updateCamera();
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
		stopDynamics = StopType::TYPE_CHENGE;
		canMove = false;
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
		if (damagedTime < 3)hittedAction();
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
	if (canMove &&actionState != ACT_SIT)
	{
		if (in_right)
		{
			dx += (int)((moveSpeed + (actionState == ACT_RUN || actionState == ACT_RUNJUMP) * 2.0f) * vectorRate);
			direction = false;
		}
		if (in_left)
		{
			dx -= (int)((moveSpeed + (actionState == ACT_RUN || actionState == ACT_RUNJUMP) * 2.0f) * vectorRate);
			direction = true;
		}
	}

	//�n��ɂ���Ȃ�
	if (jumpPower == 0 && onGround)
	{
		nowJumpCount = 0;
	}

	//�͂����ɂ̂ڂ�
	if (onLadder)
	{
		if (in_up)
		{
			dy -= (int)(moveSpeed * vectorRate);
			jumpPower = 0.0f;
			nowJumpCount = 0;
		}

		if (in_down)
		{
			dy += (int)(moveSpeed * vectorRate);
			jumpPower = 0.0f;
			nowJumpCount = 0;
		}
	}

	//�W�����v
	if (in_jump && !prePush && nowJumpCount < maxJumpCount)
	{
		jumpPower = maxJumpPower + (actionState == ACT_RUN)*3.0f;
		nowJumpCount++;
	}

	//�c�ړ�

	//�d�͂̒l
	//�͂����ɂ��邩�Cdy��0�łȂ�(moveCharacter���Ă΂�Ă���)�Ȃ�d�͂̒l��0
	int gravity_value = gravity() * (actionState != ACT_LADDER && actionState != ACT_LADDER_STOP) * (dy == 0) * !onGround;
	if (jumpPower > 0.0f && onLadder)gravity_value = gravity();

	dy += gravity_value - jump();


	dx = getHorizontalDiffer(_stage, dx, dy < 0);
	dy = dy < 0 ? getTopDiffer(_stage, dy, dx < 0) : getBottomDiffer(_stage, dy, dx < 0);
	if (actionState == ACT_SIT)dy += (int)(CHIP_HEIGHT / 2 * vectorRate);

	//�V��ɓ���������
	if (abs(dy) <= 1000)jumpPower = 0;

	//for Debug
	if (Input_D() && in_up) dy = getTopDiffer(_stage, -3000, dx < 0);
	if (Input_D() && in_down)dy = getBottomDiffer(_stage, 3000, dx < 0);

	p->raw_x += dx;
	p->raw_y += dy;



	//�}�b�v�Ԉړ�
	int dx_onScreen = p->x() - post_x;
	int dy_onScreen = p->y() - post_y;

	nextStageMove = GameMain::MOVE_NONE;
	if (abs(dx_onScreen) > MyData::MAP_WIDTH / 2)
	{
		if (dx_onScreen < 0)
		{
			nextStageMove = GameMain::MOVE_RIGHT;
		}
		else
		{
			nextStageMove = GameMain::MOVE_LEFT;
		}
	}
	if (abs(dy_onScreen) > MyData::MAP_HEIGHT / 2)
	{
		if (dy_onScreen > 0)
		{
			nextStageMove = GameMain::MOVE_UP;
		}
		else
		{
			nextStageMove = GameMain::MOVE_DOWN;
		}
	}

	post_x = p->x();
	post_y = p->y();

	prePush = in_jump;
}

void PlayerChild::updateCamera()
{
	//�J�����ʒu���X�V
	int tmp_x = p->raw_x / MyData::vectorRate;
	int tmp_y = p->raw_y / MyData::vectorRate;
	if (actionState == ACT_SIT)tmp_y -= PLAYER_CHIP_HEIGHT / 4;

	if (tmp_x % MyData::MAP_WIDTH  <                     MyData::CX)tmp_x = MyData::MAP_WIDTH * (tmp_x / MyData::MAP_WIDTH) + MyData::CX;
	if (tmp_x % MyData::MAP_WIDTH  > MyData::MAP_WIDTH - MyData::CX)tmp_x = MyData::MAP_WIDTH * (tmp_x / MyData::MAP_WIDTH) + MyData::MAP_WIDTH - MyData::CX;

	if (tmp_y % MyData::MAP_HEIGHT <                      MyData::CY)tmp_y = MyData::MAP_HEIGHT * (tmp_y / MyData::MAP_HEIGHT) + MyData::CY;
	if (tmp_y % MyData::MAP_HEIGHT > MyData::MAP_HEIGHT - MyData::CY)tmp_y = MyData::MAP_HEIGHT * (tmp_y / MyData::MAP_HEIGHT) + MyData::MAP_HEIGHT - MyData::CY;


	*camera = Vector2(tmp_x, tmp_y);
}

bool PlayerChild::isOnGround(const Stage* _stage)
{
	//pos�̓L�����̍ŉ��[���ЂƂ�
	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 + 1000);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, true);


	//�E��Ɍ������΂߃u���b�N�Ȃ�
	if (chipType == Stage::ChipType::TYPE_DOWN_SLANT_RIGHT)
	{
		pos.pos_y -= (MyData::CHIP_WIDTH_RATE() - p->pos_x() % MyData::CHIP_WIDTH_RATE());
		chipType = _stage->getChipType(pos / MyData::vectorRate, true);
	}

	//����Ɍ������΂߃u���b�N�Ȃ�
	else if (chipType == Stage::ChipType::TYPE_DOWN_SLANT_LEFT)
	{
		pos.pos_y -= p->pos_x() % MyData::CHIP_WIDTH_RATE();
		chipType = _stage->getChipType(pos / MyData::vectorRate, true);
	}

	return !(chipType & (Stage::ChipType::TYPE_BACK | Stage::ChipType::TYPE_LADDER));
}

bool PlayerChild::isOnLadder(const Stage* _stage) const
{

	RawVector2 pos = RawVector2(p->pos_x(), p->pos_y() + MyData::PLAYER_CHIP_HEIGHT_RATE() / 2 - 1);
	Stage::ChipType chipType = _stage->getChipType(pos / MyData::vectorRate, true);

	return chipType == Stage::ChipType::TYPE_LADDER || chipType == Stage::ChipType::TYPE_LADDER_TOP;
}

int PlayerChild::animation() 
{
	int num = 0 + direction;
	switch (actionState) 
	{
	case ACT_WALK:
		num = 8 + (animeCount / 10) % 4 + 8 * direction;
		break;
	case ACT_RUN:
		num = 12 + (animeCount / 10) % 4 + 8 * direction;
		break;
	case ACT_SIT:
//		num = 24 + (animeCount >= 10);
		num = 25;
		break;
	case ACT_ATTACK:
		num = 26 + direction;
		break;
	case ACT_LADDER:
		num = 28 + (animeCount / 10) % 2;
		break;
	case ACT_LADDER_STOP:
		num = 28 + direction;//���ƂŏC�����邩��
		break;
	default:
		animeCount = 0;
		break;
	}

	animeCount++;

	assert(!(num < 0 || 40 <= num) && "���@�摜�͈͊O");
	return num;
}

void PlayerChild::actCheck()
{
	ActionState preAction = actionState;
	if (onLadder)
	{
		actionState = ACT_LADDER_STOP;
		if (in_up || in_down)
		{
			actionState = ACT_LADDER;
		}

		if (in_left || in_right)
		{
			actionState = ((onGround) ? ACT_WALK : ACT_AIR);
		}

		if (onGround && !in_up)
		{
			actionState = ACT_NORMAL;
			if (in_down)actionState = ACT_SIT;
		}
	}
	else if (Input_ATTACK())actionState = ACT_ATTACK;
	else if (!onGround) {
		if (actionState == ACT_RUN || actionState==ACT_RUNJUMP)actionState = ACT_RUNJUMP;
		else actionState = ACT_AIR;
	}
	else if (in_down)actionState = ACT_SIT;
	else if (in_left || in_right)
	{
		actionState = ACT_WALK;
		if (Input_LSHIFT())actionState = ACT_RUN;
	}
	else actionState = ACT_NORMAL;

	if (actionState != preAction)animeCount = 0;
}



}		
}
}