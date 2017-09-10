#include "GameMain.h"

#include "Converse.h"

#include "GameMain\Stage.h"
#include "GameMain\System.h"
#include "GameMain\Player\Mokou.h"
#include "GameMain\Player\Sakuya.h"

#include "GameMain\Enemy\EnemyController.h"
#include "GameMain\Enemy\EnemyChild.h"

#include "GameMain\Gimmick\DynamicGimmickChild.h"

#include "..\..\..\Data.h"
#include "..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


GameMain::GameMain(int _stageNum){
	initialize(_stageNum);
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

void GameMain::initialize(int _stageNum)
{
	//for Debug
	for (int i = 0; i <= 1; i++)
	{
		mStages.push_back(new Stage(_stageNum, i));
	}

	//�X�e�[�W�̑S�̓I�ȏc�Ɖ��̐���ݒ�

	//TODO ���l���t�@�C�����擾
	int stage_x = 2;
	int stage_y = 1;
	nowStageNum = 0;

	//TODO �Ȃ�Őݒ肵���񂾂���...�H
	for (auto& stage : mStages)
	{
		stage->setStageSize(stage_x, stage_y);//�悱�A����
	}

	mPlayer = new Sakuya(96, 1500, 100);
	mSystem = new System(nowStageNum, stage_x, stage_y);
	mEController = new EnemyController();

	changed = false;
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	//����stage��ݒ�
	nowStageNum = mSystem->getNowStage();
	Stage* stage = mStages[nowStageNum];

	//Stage��update
	stage->update(mPlayer);

	//Player��update
	PlayerChild* nextPlayer = mPlayer->update(stage);
	changed = false;
	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
		changed = true;
	}

	//enemy��update
	mEController->update(stage);

	//�Փ˔���
	processCollision(stage);

	//for Debug
	mPlayer->hpController.recover(1);

	//System��update
	if(changed)mSystem->update(HowStageMove::MOVE_NONE);
	else mSystem->update(mPlayer->getStageMove());

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
	//if (changed)return;

	//DrawFormatString(0, 20, MyData::WHITE, "GameMain");
	mStages[nowStageNum]->draw(mPlayer->getCamera());
	mEController->draw(mPlayer->getCamera());
	mPlayer->draw();
	mSystem->draw();
}



//==============================================
//�����v���C�x�[�g�֐�
//==============================================

void GameMain::processCollision(Stage* _stage)
{
	//TODO -> ������������
	//�Ⴄ�X�e�[�W�̂��̂͏������Ȃ��Ƃ�

	//�G
	auto enemies = mEController->getEnemies();

	//�v���C���[�̍U��
	auto p_attacks = mPlayer->getAtacks();

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
			if (attack->isActive)
			{
				if (attack->isHit(gimmick))
				{
					gimmick->hittedAction();
					attack->hittedAction();

					if(attack->id == ObjectID::A_FIRE)
						gimmick->burnedAction();
				}
			}
		}

	}

}

}
}
}