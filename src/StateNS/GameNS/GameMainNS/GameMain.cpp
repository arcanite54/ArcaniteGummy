#include "GameMain.h"

#include "Converse.h"

#include "GameMain\Stage.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"
#include "GameMain\Player\Sakuya.h"
#include "GameMain\Player\Nue.h"

#include "GameMain\Enemy\EnemyController.h"
#include "GameMain\Enemy\EnemyChild.h"

#include "GameMain\Gimmick\DynamicGimmickChild.h"
#include "GameMain\Gimmick\Block.h"
#include "GameMain\Gimmick\Switches\SwitchWithBlock.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(int _n,int _x,int _y){
	xNum = _x, yNum = _y;
	stageID = _n;
	initialize();
}

GameMain::~GameMain()
{
	for (auto& stage : mStages)
	{
		SAFE_DELETE(stage);
	}
	mStages.clear();
	mStages.shrink_to_fit();

	SAFE_DELETE(mPlayer);
	SAFE_DELETE(mSystem);
	SAFE_DELETE(mEController);
}

void GameMain::initialize()
{
	for (int i = 0; i < xNum * yNum; i++)
	{
		mStages.push_back(new Stage(stageID, i, xNum - 1, yNum - 1));
	}

	//�X�e�[�W�̑S�̓I�ȏc�Ɖ��̐���ݒ�

	//TODO ���l���t�@�C�����擾
	int stage_x = 2;
	int stage_y = 1;
	nowStageNum = 0;

	mPlayer = new Nue(96, 1500, 100);
	mSystem = new System(nowStageNum, xNum, yNum);

	mEController = new EnemyController();
	mEController->setPlayerPos(mPlayer->getVector2());

	stopDynamicObject = StopType::TYPE_NONE;
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	//����stage��ݒ�
	nowStageNum = mSystem->getNowStage();
	Stage* stage = mStages[nowStageNum];

	//�����~�܂��Ă��邩�X�V
	stopDynamicObject = mPlayer->getStopDynamicObject();

	//DynamicObject���X�V
	if(stopDynamicObject == StopType::TYPE_NONE)updateDynamics(stage);

	//Player��update
	PlayerChild* nextPlayer = mPlayer->update(stage);

	//Player���
	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
		mEController->setPlayerPos(mPlayer->getVector2());
	}

	//�Փ˔���
	processCollision(stage);

	//for Debug
	mPlayer->hpController.recover(1);

	//System��update
	mSystem->update(mPlayer->getStageMove());

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		next = new Converse(this, 1,1);
	
	//�N���A
	if (stage->isClear())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_CLEAR);
	}

	return next;
}

void GameMain::draw() const
{
	if (stopDynamicObject == StopType::TYPE_SAKUYA)
	{
		DrawBox(0, 0, 640, 480, WHITE, true);
		SetDrawBlendMode(DX_BLENDMODE_SUB, 200);
	}
	mStages[nowStageNum]->draw(mPlayer->getCamera());
	mEController->draw(mPlayer->getCamera());

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	mPlayer->draw();
	mSystem->draw(mPlayer->getVector2());
}



//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void GameMain::updateDynamics(Stage* stage)
{
	//Stage��update
	stage->update(mPlayer);

	//enemy��update
	mEController->update(stage);
}

void GameMain::processCollision(Stage* _stage)
{
	//TODO -> ������������
	//�Ⴄ�X�e�[�W�̂��̂͏������Ȃ��Ƃ�

	//�G
	auto enemies = mEController->getEnemies();

	//�v���C���[�̍U��
	auto p_attacks = mPlayer->getAttacks();

	//�G�̍U��
	//...

	for (auto& enemy : enemies)
	{
		if (!enemy->isAlive())continue;

		//�v���C���[�ƓG�̏Փ�
		if (mPlayer->isHit(enemy))
		{
			mPlayer->hpController.damage(5);
		}

		//�v���C���[�̍U���ƓG�̏Փ�
		for (auto& attack : p_attacks)
		{
			if (attack->isActive)
			{
				if (attack->isHit(enemy))
				{
					enemy->hpController.damage(attack->getDamageValue());
					attack->hittedAction();
				}
			}
		}
	}

	//DynamicGimmick
	auto d_gimmicks = _stage->getDynamicGimmicks();

	for (auto& gimmick : d_gimmicks)
	{
		if (!gimmick->isActive)continue;

		//�v���C���[��DynamicGimmick�̏Փ�
		if (mPlayer->isHit(gimmick))
		{

		}

		//�v���C���[�̍U����DynamicGimmick�̏Փ�
		//�v���C���[�̍U���ƓG�̏Փ�
		for (auto& attack : p_attacks)
		{
			if (attack->isActive && attack->isHit(gimmick))
			{
				gimmick->hittedAction();
				attack->hittedAction();

				if (attack->id == ObjectID::A_FIRE)
					gimmick->burnedAction();
			}
		}

		auto s_b = _stage->getSwitchWithBlocks();

		//TODO �l�X�g���炵����
		for (auto& s : s_b)
		{
			for (auto& attack : p_attacks)
			{
				if (attack->isActive && attack->isHit(s))
				{
					s->hittedAction();
					attack->hittedAction();
					s->checkOnActiveArea(attack->getVector2());
				}
			}
		}
	}
}


}
}
}