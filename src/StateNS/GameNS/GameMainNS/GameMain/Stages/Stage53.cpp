#include "Stage53.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Enemy\Kaguya.h"
#include "..\Enemy\EnemyController.h"
#include "..\Player\PlayerChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage53::Stage53() :
StageChild(3, 1) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage53::~Stage53()
{

}

void Stage53::initialize()
{
	//�ύX�ł���L�����N�^�[��ݒ�
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(43, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(43, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(43, 2, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(2384, 1360));

	//�P��ݒ�
	kaguya = new Kaguya(800, 1536);
	maps[2]->addEnemy(kaguya);



	now_stage_num = 2;
	startX = 600, startY = 1536;

	//this->torches.push_back(new Torch(304, 1488));
	//this->maps[0]->addGimmick(torches[0]);
}


void Stage53::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//�Èłɂ���
	if (kaguya->makeDark())
	{
		gameMain->setFilter(FilterType::FILTER_DARK);
	}
	else
	{
		gameMain->setFilter(FilterType::FILTER_NONE);
	}

	//�P�邪�G�𐶐�����
	if (kaguya->makeEnemy())
	{
		kaguya->setMuteki(true);
		for (int i = 0; i < kaguya->maxCreateEnemyNum; i++)
		{
			int ene_num = GetRand(5);

			//�n��̓G
			if (ene_num <= 3)
			{
				maps[2]->addEnemy(itoE(ene_num), _player->getVector2(), kaguya->getVector2()->x(), kaguya->getVector2()->y() + 16);
			}
			else
			{
				maps[2]->addEnemy(itoE(ene_num), _player->getVector2(), kaguya->getVector2()->x(), kaguya->getVector2()->y() - 100);
			}
		}
	}
	auto enes = maps[2]->getEController()->getEnemies();

	//�P��ȊO�ɓG������Ȃ�
	if (maps[2]->getEController()->getEnemies().size() != 1)
	{
		maps[2]->getEController()->minimize_enemies();

		//�T�C�Y��1�ɂȂ��Ă�����
		if(maps[2]->getEController()->getEnemies().size() == 1)kaguya->setMuteki(false);
	}
}

void Stage53::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage53::isClear() const
{
	return !kaguya->isAlive();
}


}
}
}


