#include "Stage00.h"
#include "Map.h"
#include "..\..\GameMain.h"
#include "..\Gimmick\AllGimmicks.h"

#include <fstream>


/////////////////////////////////////////////�f�o�b�O�p�X�e�[�W/////////////////////
namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Stage00::Stage00() :
StageChild(2, 1) //�G���A�̐�: �悱�C����
{
	initialize();
}

Stage00::~Stage00()
{
	
}

void Stage00::initialize()
{
	//���ォ��E��push���Ă���
	//StageID, 0���珸��, �G���A�̌`
	this->maps.push_back(new Map(0, 0, MapPos::POS_RIGHT_FREE));
	this->maps.push_back(new Map(0, 1, MapPos::POS_LEFT_FREE));
	
	//�ύX�ł���L�����N�^�[��ݒ�
	this->changeableCharacter |= CHARA_MOKOU;
	this->changeableCharacter |= CHARA_SAKUYA;
	this->changeableCharacter |= CHARA_NUE;

	flag = new ClearFlag(Vector2(3056, 1264));
	maps[1]->addGimmick(flag);

	//maps[0]->addEnemy(AllEnemies::BOSS_REISEN, 676, 1552);
	//maps[0]->addEnemy(AllEnemies::BOSS_FRAN, 356, 1536);

	vector<string> message
	{
	"           ��_��",
	"          (*߁[�) �Q�Q�Q�Q",
	"           / �^ | �^ |",
	"    �`�@�@ | �P�P�P�P | . |",
	" �����i/�@ | AA���\ | �^, , , , ,",
	};


	Guide* guide = new Guide(336, 1552, message);
	maps[0]->addGimmick(guide);

	Burner* b1 = new Burner(400, 1552, pi(1.5f), 0);
	Burner* b2 = new Burner(432, 1552, pi(0.5f), 1);

	Burner* b3 = new Burner(464, 1456, pi(1.0f), 0);
	Burner* b4 = new Burner(464, 1488, pi(0.0f), 1);


	maps[0]->addDynamicGimmick(b1);
	maps[0]->addDynamicGimmick(b2);
	maps[0]->addDynamicGimmick(b3);
	maps[0]->addDynamicGimmick(b4);


	startX = 144, startY = 1536;

	findRestartPoint();
}


void Stage00::update(GameMain* gameMain, PlayerChild* _player)
{
	standardUpdate(_player);

	//for Debug
	if(CheckHitKey(KEY_INPUT_1))
		gameMain->startConverse(11);
}

void Stage00::draw(const Vector2* _camera) const
{
	standardDraw(_camera);
}

bool Stage00::isClear() const
{
	return !flag->isActive;
}


}
}
}


