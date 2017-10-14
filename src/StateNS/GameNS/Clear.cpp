#include "Clear.h"
#include "..\StateParent.h"

#include "Play.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {

Clear::Clear()
{

}


Clear::~Clear()
{

}

void Clear::initialize()
{

}

Child* Clear::update(StateNS::Parent* _parent)
{
	Child* next = this;

	if (Input_C())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	//���̃X�e�[�W��
	if (_parent->stageNum % 10 == 3 || Input_Z())
	{
		int nextStage = _parent->stageNum;
	
		//�N���A������
		if (nextStage == 53)nextStage = 11;
		else if (nextStage % 10 == 3)nextStage += 8;
		else ++nextStage;

		_parent->stageNum = nextStage;
		next = new Play(nextStage);
	}

	return next;
}

void Clear::draw() const
{
	DrawFormatString(250, 220, MyData::WHITE, "���肠�[�I");
	DrawFormatString(250, 320, MyData::WHITE, "Z�Ŏ���");

}






}
}

