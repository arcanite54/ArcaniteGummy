#include "Stage31.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage31::Stage31() :
StageChild(2, 1) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage31::~Stage31()
{

}

void Stage31::initialize()
{
	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(31, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(31, 1, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(1936, 1552));
	maps[1]->addGimmick(flag);


	torches.push_back(new Torch(22 * 32 + 16, 48 * 32 + 16));
	torches.push_back(new Torch(4 * 32 + 16, 36 * 32 + 16));
	torches.push_back(new Torch(58 * 32 + 16, 6 * 32 + 16));
	torches.push_back(new Torch(62 * 32 + 16, 38 * 32 + 16));
	for (const auto& t : torches)maps[0]->addDynamicGimmick(t);

	torches2.push_back(new Torch(26 * 32 + 16, 5 * 32 + 16));
	for (const auto& t : torches2)maps[1]->addDynamicGimmick(t);

	SwitchWithBlock* s = new SwitchWithBlock(78 * 32 + 16, 5 * 32 + 16);
	for (int i = 0; i < 3; i++)s->push_block(new Block(78 * 32 + 16, (11 + i) * 32 + 16, 1.0), false);
	maps[1]->addSwitchWithBlock(s);


	startX = 144, startY = 1536;

}


void Stage31::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	gameMain->setFilter(FilterType::FILTER_DARK);
	for (const auto& t : torches)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
	for (const auto& t : torches2)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);


	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(31);
}

void Stage31::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage31::isClear() const
{
	return !flag->isActive;
}


}
}
}


