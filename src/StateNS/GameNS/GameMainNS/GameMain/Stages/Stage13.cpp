#include "Stage13.h"
#include "Map.h"
#include "..\..\GameMain.h"

#include "..\Gimmick\DynamicGimmickChild.h"
#include "..\Gimmick\Torch.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage13::Stage13() :
StageChild(2, 2) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage13::~Stage13()
{
	for (auto& t : torches)
	{
			SAFE_DELETE(t);
	}
	torches.clear();
	torches.shrink_to_fit();
}

void Stage13::initialize()
{
	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(13, 0, MapPos::POS_LEFT_UP));
	this->maps.push_back(new Map(13, 1, MapPos::POS_RIGHT_UP));
	this->maps.push_back(new Map(13, 2, MapPos::POS_LEFT_DOWN));
	this->maps.push_back(new Map(13, 3, MapPos::POS_RIGHT_DOWN));

	this->torches.push_back(new Torch(304, 1488));

	this->maps[0]->addGimmick(torches[0]);

}


void Stage13::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	gameMain->setFilter(FilterType::FILTER_DARK);
	if (torches[0]->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
}

void Stage13::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage13::isClear() const
{
	return false;
}


}
}
}


