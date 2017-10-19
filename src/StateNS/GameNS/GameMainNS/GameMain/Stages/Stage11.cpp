#include "Stage11.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\ClearFlag.h"
#include "..\Gimmick\Guide.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage11::Stage11() :
StageChild(2, 1) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage11::~Stage11()
{
	sound->deleteSound("bgm1");
}

void Stage11::initialize()
{
	this->mBackImg = LoadGraph("Data/Image/back1.jpg");
	sound->setSound("Data/Sound/stage1.wav", "bgm1");
	sound->playSound("bgm1", LOOP, false);

	//�ύX�ł���L�����N�^�[��ݒ�
	this->changeableCharacter |= CHARA_MOKOU;
	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(11, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(11, 1, MapPos::POS_LEFT_FREE));

	//this->maps[0]->addEnemy(BOSS_JUNKO, 540, 1488);
	/*
	vector<string> message
	{
		"        �K�C�h��",
		"           ��_��",
		"          (*߁[�) �Q�Q�Q�Q",
		"           / �^ | �^ |",
		"    �`�@�@ | �P�P�P�P | . |",
		" �����i/�@ | AA���\ | �^, , , , ,",
	};
	*/
	vector<string> message
	{
		"���g�̃T�|�[�g��",
		"���A�㔒��d����",
		"�C���Ă���",
		"������Ȃ����Ƃ���������",
		"���������񂾂�",
	};

	Guide* guide = new Guide(272, 1552, message);
	maps[0]->addGimmick(guide);


	flag = new ClearFlag(Vector2(3056, 1264));
	maps[1]->addGimmick(flag);
	
	startX = 144, startY = 1536;
	converseFlag0 = true;

	//����
	bool restart = findRestartPoint();
	//�����������b�t���O��܂�
	if (restart)
	{
		converseFlag0 = false;
	}
}


void Stage11::update(GameMain* gameMain, PlayerChild* _player)
{
	updateConverse(gameMain, _player);
	standardUpdate(_player);
}

void Stage11::updateConverse(GameMain* gameMain, PlayerChild* _player)
{
	if (converseFlag0)
	{
		gameMain->startConverse(110);
		converseFlag0 = false;
	}
}

void Stage11::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage11::isClear() const
{
	return !flag->isActive;
}


}
}
}


