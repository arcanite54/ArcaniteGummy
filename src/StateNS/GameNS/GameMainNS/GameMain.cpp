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

	stopDynamicObject = false;
}

Child* GameMain::update(GameParent* _parent)
{
	Child* next = this;

	//����stage��ݒ�
	nowStageNum = mSystem->getNowStage();
	Stage* stage = mStages[nowStageNum];

	//DynamicObject���X�V
	if(!stopDynamicObject)updateDynamics(stage);

	//Player��update
	PlayerChild* nextPlayer = mPlayer->update(stage);
	stopDynamicObject = mPlayer->setStopDynamicObject();
	if (nextPlayer != mPlayer)
	{
		SAFE_DELETE(mPlayer);
		mPlayer = nextPlayer;
	}

	//�Փ˔���
	processCollision(stage);

	//for Debug
	mPlayer->hpController.recover(1);

	//System��update
	//if(changed)mSystem->update(HowStageMove::MOVE_NONE);
	//else 
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
	mStages[nowStageNum]->draw(mPlayer->getCamera());
	mEController->draw(mPlayer->getCamera());
	mPlayer->draw();
	mSystem->draw();
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