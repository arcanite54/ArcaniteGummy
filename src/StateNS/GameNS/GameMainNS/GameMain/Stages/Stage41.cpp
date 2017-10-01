#include "Stage41.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage41::Stage41() :
StageChild(2, 1) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage41::~Stage41()
{

}

void Stage41::initialize()
{
	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(41, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(41, 1, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(3056, 240));
	maps[1]->addGimmick(flag);

	startX = 144, startY = 1536;

}


void Stage41::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(12);
}

void Stage41::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage41::isClear() const
{
	return false;
}


}
}
}


