#include "StageChild.h"
#include "Map.h"

#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


StageChild::StageChild(int _stage_max_x,int _stage_max_y)
{
	stage_max_x = _stage_max_x;
	stage_max_y = _stage_max_y;

	initialize();
	mBackImg = LoadGraph("Data/Image/back.jpg");
	assert(mBackImg != -1 && "�w�i�摜�ǂݍ��݃G���[");
}

StageChild::~StageChild()
{
	for (auto& map : maps)
	{
		SAFE_DELETE(map);
	}
	maps.clear();
	maps.shrink_to_fit();
}

void StageChild::initialize()
{
	this->now_stage_num = 0;
	this->changeableCharacter = ChangeableCharacter::CHARA_NONE;
}

void StageChild::standardUpdate(PlayerChild* _player)
{
	maps[now_stage_num]->update(_player, this);
}

void StageChild::standardDraw(const Vector2* _camera) const
{
	DrawGraph(0, 0, mBackImg, true);
	maps[now_stage_num]->draw(_camera);
}

void StageChild::draw_front(const Vector2* _camera) const
{
	maps[now_stage_num]->draw_front(_camera);
}

StageChild::ChipType StageChild::getChipType(const Vector2& _other, bool colliWithGimmick) const
{
	return maps[now_stage_num]->getChipType(_other, colliWithGimmick);
}

//�|�����[�t�B�Y��
StageChild::ChipType StageChild::getChipType(const Vector2& _other) const
{
	return getChipType(_other, true);
}

//�|�����[�t�B�Y��
StageChild::ChipType StageChild::getChipType(const RawVector2& _other, bool colliWithGimmick) const
{
	return getChipType(Vector2(_other.pos_x, _other.pos_y), colliWithGimmick);
}

int StageChild::getTopPosition(const Vector2* _pos, const int& _dy) const
{
	return maps[now_stage_num]->getTopPosition(_pos, _dy);
}

int StageChild::getBottomPosition(const Vector2* _pos, const int& _dy) const
{
	return maps[now_stage_num]->getBottomPosition(_pos, _dy);
}

vector< DynamicGimmickChild* > StageChild::getDynamicGimmicks()
{
	return maps[now_stage_num]->getDynamicGimmicks();
}

vector< SwitchWithBlock* > StageChild::getSwitchWithBlocks()
{
	return maps[now_stage_num]->getSwitchWithBlocks();
}

EnemyController* StageChild::getEController()
{
	return maps[now_stage_num]->getEController();
}

void StageChild::moveStage(HowStageMove _stageMove)
{
	switch (_stageMove)
	{
	case MOVE_RIGHT:
		now_stage_num++;
		break;
	case MOVE_LEFT:
		now_stage_num--;
		break;
	case MOVE_UP:
		now_stage_num -= stage_max_y;
		break;
	case MOVE_DOWN:
		now_stage_num += stage_max_y;
		break;
	}
	assert(now_stage_num < maps.size() && "StageChild: map index out of range!");
}

void StageChild::processDynamcCollision(PlayerChild* _player)
{
	maps[now_stage_num]->processDynamicCollision(_player);
}

//========================================================================
// ����protected�֐�
//========================================================================



//========================================================================
// ����private�֐�
//========================================================================




}
}
}


