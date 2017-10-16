#include "Stage43.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\DynamicGimmickChild.h"
#include "..\Gimmick\Torch.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage43::Stage43() :
StageChild(3, 1) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage43::~Stage43()
{

}

void Stage43::initialize()
{
	//�ύX�ł���L�����N�^�[��ݒ�
	this->changeableCharacter |= CHARA_MOKOU;

	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(43, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(43, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(43, 2, MapPos::POS_LEFT_FREE));

	torches.push_back(new Torch(27 * 32 + 16, 46 * 32 + 16));
	torches.push_back(new Torch(5 * 32 + 16, 36 * 32 + 16));
	torches.push_back(new Torch(10 * 32 + 16, 6 * 32 + 16));
	torches.push_back(new Torch(53 * 32 + 16, 6 * 32 + 16));
	for (const auto& t : torches)maps[0]->addDynamicGimmick(t);

	torches2.push_back(new Torch(9 * 32 + 16, 3 * 32 + 16));
	torches2.push_back(new Torch(42 * 32 + 16, 8 * 32 + 16));
	torches2.push_back(new Torch(71 * 32 + 16, 6 * 32 + 16));
	torches2.push_back(new Torch(10 * 32 + 16, 26 * 32 + 16));
	torches2.push_back(new Torch(71 * 32 + 16, 19 * 32 + 16));
	torches2.push_back(new Torch(84 * 32 + 16, 35 * 32 + 16));
	torches2.push_back(new Torch(6 * 32 + 16, 48 * 32 + 16));
	torches2.push_back(new Torch(30 * 32 + 16, 48 * 32 + 16));
	torches2.push_back(new Torch(68 * 32 + 16, 48 * 32 + 16));

	for (const auto& t : torches2)maps[1]->addDynamicGimmick(t);



	startX = 144, startY = 1536;

	flag = new ClearFlag(Vector2(16, 16));
	maps[0]->addGimmick(flag);
	converseFlag0 = true;
	converseFlag1 = true;
	findRestartPoint();
}


void Stage43::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);
	gameMain->setFilter(FilterType::FILTER_DARK);
	if(converseFlag0)gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==0)for (const auto& t : torches)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
	if(now_stage_num==1)for (const auto& t : torches2)if (t->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
}

void Stage43::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
}

void Stage43::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage43::isClear() const
{
	return !flag->isActive;
}


}
}
}


