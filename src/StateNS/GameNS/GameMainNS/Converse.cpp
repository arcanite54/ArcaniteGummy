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
	allPassages.push_back(Passage("sakuya", "tes�Ă��e�X�g1"));
	allPassages.push_back(Passage("sakuya", "tes�Ă��e�X�g2"));
	allPassages.push_back(Passage("sakuya", "�΁[��"));
}

Child* Converse::update(GameParent* _parent)
{
	Child* next = this;

	bool finish = false;
	if (Input_Z() && !prePush)finish = nextPassage();

	prePush = Input_Z();

	//for Debug
	if (finish)next = main;

	return next;
}

void Converse::draw() const
{
	main->draw();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	DrawBox(0, 0, 640, 480, BLACK, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 200);

	allPassages[passageNum].show();

	//for Debug
	DrawFormatString(560, 320, WHITE, "%d / %d", passageNum + 1, allPassages.size());
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

	DrawString(480, 450, "press Z to next", WHITE);

	//���͕\��

	//���O
	DrawString(20, 260, speaker.c_str(), WHITE);
	//����
	DrawString(20, 320, passage.c_str(), WHITE);
}

bool Converse::nextPassage()
{
	++passageNum;
	if (passageNum >= allPassages.size())
	{
		passageNum = allPassages.size() - 1;
		return true;
	}
	return false;
}





}
}
}
