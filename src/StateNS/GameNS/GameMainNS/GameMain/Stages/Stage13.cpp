#include "Stage13.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\DynamicGimmickChild.h"
#include "..\Player\PlayerChild.h"
#include "..\Gimmick\Door.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage13::Stage13() :
StageChild(4, 1) //エリアの数: よこ，たて
{
	initialize();
}

Stage13::~Stage13()
{
	sound->deleteSound("bgm1");
	sound->deleteSound("boss1");
}

void Stage13::initialize()
{
	sound->setSound("Data/Sound/stage1.wav", "bgm1");
	sound->setSound("Data/Sound/Invisible_Full_Moon.wav", "boss1");
	sound->playSound("bgm1", LOOP, false);

	//変更できるキャラクターを設定
	this->changeableCharacter |= CHARA_MOKOU;

	//左上から右にpushしていく
	//StageID, 0から昇順, エリアの形
	this->maps.push_back(new Map(13, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(13, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(13, 2, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(13, 3, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(3056, 1264));
	maps[0]->addGimmick(flag);

	Door* d = new Door(new Vector2(8 * 32 + 16, 27 * 32 + 16), new Vector2(78 * 32 + 16, 32 * 32 + 16));
	maps[3]->addGimmick(d);

	SwitchWithBlock* s = new SwitchWithBlock(76 * 32 + 16, 37 * 32 + 16, 390);
	for (int i = 0; i < 4; i++)s->push_block(new Block(76 * 32 + 16, (40 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s);

	reisen = new Reisen(88 * 32, 48 * 32);

	startX = 208, startY = 1440;
	cTime = 0;
	converseFlag0 = true;
	converseFlag0fin = false;
	converseFlag1 = true;
	converseFlag2 = true;
	findRestartPoint();
}


void Stage13::update(GameMain* gameMain, PlayerChild* _player)
{
	
	updateConverse(gameMain, _player);
	
	standardUpdate(_player);

}

void Stage13::updateConverse(GameMain* gameMain,PlayerChild* _player) 
{
	if (!converseFlag0 && !converseFlag0fin) {
		converseFlag0fin = true;
		sound->StopSound("bgm1");
		sound->playSound("boss1");
	}
	if (now_stage_num == 3 && converseFlag0 &&_player->getVector2()->y() == 1536)
	{
		reisen->setPlayer(_player->getVector2());
		maps[3]->addEnemy(reisen);
		gameMain->startConverse(130);
		converseFlag0 = false;
	}
	if (!reisen->isAlive())
	{
		cTime++;
		_player->lock = true;
	}
	if (cTime > 90 && converseFlag2) 
	{
		gameMain->startConverse(132);
		converseFlag2 = false;

	}
	if (converseFlag1 && !reisen->isAlive())
	{
		gameMain->startConverse(131);
		converseFlag1 = false;
	}

}

void Stage13::draw(const Vector2* _camera) const
{
	standardDraw(_camera);

}

void Stage13::draw_front(const Vector2* _camera) const
{


	if(cTime>30)DrawBox(0, 0, 640, 480, BLACK, TRUE);

}


bool Stage13::isClear() const
{
	return !converseFlag2 && cTime>=92;
}


}
}
}


