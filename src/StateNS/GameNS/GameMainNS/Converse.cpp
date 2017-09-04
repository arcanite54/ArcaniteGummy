#include "Converse.h"

#include "GameMain.h"
#include "..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Converse::Converse(GameMain* _main, int _convNum)
{
	main = _main;
	initialize();
}

Converse::~Converse()
{

}

void Converse::initialize()
{
	passageNum = 0;

	//for Debug
	allPassages.push_back(Passage("sakuya", "tes�Ă��e�X�g"));
}

Child* Converse::update(GameParent* _parent)
{
	Child* next = this;

	//for Debug
	if (CheckHitKey(KEY_INPUT_2))
		next = main;

	return next;
}

void Converse::draw() const
{
	main->draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, 640, 480, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	allPassages[passageNum].show();
}

//==============================================
//�����v���C�x�[�g�����o
//==============================================
Converse::Passage::Passage(string _speaker, string _passage)
{
	speaker = _speaker;
	passage = _passage;
}

Converse::Passage::~Passage()
{

}

void Converse::Passage::show() const
{
	//for Debug

	//�t���[���\��
	DrawBox(10, 250, 150, 290, BLACK, true);
	DrawBox(10, 300, 630, 470, BLACK, true);
	//�g
	DrawBox(10, 250, 150, 290, WHITE, false);
	DrawBox(10, 300, 630, 470, WHITE, false);


	//���͕\��

	//���O
	DrawString(20, 260, speaker.c_str(), WHITE);
	//����
	DrawString(20, 320, passage.c_str(), WHITE);
}

void Converse::nextPassage()
{

}





}
}
}
