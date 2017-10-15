#include "Stage13.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"

#include "..\Gimmick\DynamicGimmickChild.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage13::Stage13() :
StageChild(4, 1) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage13::~Stage13()
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

void Stage13::initialize()
{

	//�ύX�ł���L�����N�^�[��ݒ�
	this->changeableCharacter |= CHARA_MOKOU;

	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(13, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(13, 1, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(13, 2, MapPos::POS_UP_DOWN));
	this->maps.push_back(new Map(13, 3, MapPos::POS_LEFT_FREE));

	flag = new ClearFlag(Vector2(3056, 1264));
	maps[0]->addGimmick(flag);

	SwitchWithBlock* s = new SwitchWithBlock(76 * 32 + 16, 37 * 32 + 16, 99);
	for (int i = 0; i < 4; i++)s->push_block(new Block(76 * 32 + 16, (40 + i) * 32 + 16, 1.0, BlockType::TYPE_SWITCH), false);
	maps[1]->addSwitchWithBlock(s);

	maps[3]->addEnemy(BOSS_REISEN, 78 * 32, 48 * 32);

	startX = 208, startY = 1440;

//	this->torches.push_back(new Torch(304, 1488));
//	this->maps[0]->addGimmick(torches[0]);


}


void Stage13::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

//	gameMain->setFilter(FilterType::FILTER_DARK);
//	if (torches[0]->isBurned())gameMain->setFilter(FilterType::FILTER_NONE);
}

void Stage13::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage13::isClear() const
{
	return !flag->isActive;
}


}
}
}


