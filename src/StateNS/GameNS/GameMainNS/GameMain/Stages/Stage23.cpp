#include "Stage23.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Player\PlayerChild.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Gimmick\Door.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage23::Stage23() :
StageChild(3, 3) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage23::~Stage23()
{
	//torches��Map��DynamickGimmicks�ƈꏏ��delete����邩��C�����ł�delete���Ȃ�
	/*
	for (auto& t : torches)
	{
			SAFE_DELETE(t);
	}
	torches.clear();
	torches.shrink_to_fit();
	*/
}

void Stage23::initialize()
{

	//�ύX�ł���L�����N�^�[��ݒ�
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;


	time = 0;
	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(23, 0, MapPos::POS_DOWN_FREE));
	this->maps.push_back(new Map(23, 1, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(23, 2, MapPos::POS_LEFT_FREE));
	this->maps.push_back(new Map(23, 3, MapPos::POS_RIGHT_LEFT));
	this->maps.push_back(new Map(23, 4, MapPos::POS_RIGHT_LEFT));
	this->maps.push_back(new Map(23, 5, MapPos::POS_SINGLE));
	this->maps.push_back(new Map(23, 6, MapPos::POS_LEFT_DOWN));
	this->maps.push_back(new Map(23, 7, MapPos::POS_RIGHT_DOWN));
	this->maps.push_back(new Map(23, 8, MapPos::POS_LEFT_UP));

	flag = new ClearFlag(Vector2(16, 16));
	maps[8]->addGimmick(flag);

	Door* d = new Door(new Vector2(9 * 32 + 16, 13 * 32 + 16), new Vector2(72 * 32 + 16, 31 * 32 + 16));
	maps[2]->addGimmick(d);

	maps[2]->addEnemy(BOSS_JUNKO, 88 * 32, 48 * 32);


	SwitchWithBlock* s = new SwitchWithBlock(44 * 32 + 16, 14 * 32 + 16, 330);
	for (int i = 0; i < 3; i++)s->push_block(new Block((46 + i) * 32 + 16, 46 * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[3]->addSwitchWithBlock(s);
	SwitchWithBlock* s2 = new SwitchWithBlock(50 * 32 + 16, 24 * 32 + 16, 330);
	for (int i = 0; i < 3; i++)s2->push_block(new Block((46 + i) * 32 + 16, 47 * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[3]->addSwitchWithBlock(s2);
	SwitchWithBlock* s3 = new SwitchWithBlock(44 * 32 + 16, 35 * 32 + 16, 330);
	for (int i = 0; i < 3; i++)s3->push_block(new Block((46 + i) * 32 + 16, 48 * 32 + 16, 1.0, BlockType::TYPE_LOCK), false);
	maps[3]->addSwitchWithBlock(s3);

	startX = 144, startY = 1536;

	imageJunko = LoadGraph("Data/Image/Character/haribote_junko.png");
	converseFlag0 = true;
	converseFlag0fin = false;
	converseFlag1 = true;

}


void Stage23::update(GameMain* gameMain, PlayerChild* _player)
{
	
	if (!converseFlag0)
	{
		converseFlag0fin = true;
		DeleteGraph(imageJunko);
	}
	if (converseFlag0)
	{
		gameMain->startConverse(230);
		converseFlag0 = false;
	}


	if (now_stage_num == 2 && converseFlag1 &&_player->getVector2()->y() == 1536)
	{
		gameMain->startConverse(231);
		converseFlag1 = false;
	}

	
	standardUpdate(_player);
	time++;
	if (time % 360 == 0)maps[0]->addEnemy(ENE_TERESA, _player->getVector2(), (1 + GetRand(1) * 30) * 32, 31 * 32);

}

void Stage23::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
	if (!converseFlag0fin)DrawRotaGraph(360, 416, 1.0, 0.0, imageJunko, TRUE);

}

bool Stage23::isClear() const
{
	return !flag->isActive;
}



}
}
}


