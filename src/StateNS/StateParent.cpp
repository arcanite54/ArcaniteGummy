#include "StateParent.h"
#include "Title.h"
#include "Config.h"
#include "GameNS\Play.h"

#include "..\Data.h"


namespace StateNS{

Parent::Parent(int _stageNum)
{
	stageNum = _stageNum;
	initialize();
}

Parent::~Parent()
{
	
}

void Parent::initialize()
{
	//�Z�[�u�f�[�^�ǂݍ���
	//stageNum�X�V


	this->mChild = new GameNS::Play(stageNum);
	mNextSeq = NextSequence::SEQ_NONE;


}

Child* Parent::update(GrandParent* parent)
{
	Child* next = this;

	GameNS::Child* nextChild = mChild->update(this);

	//�V�[�P���X�J��
	if (nextChild != mChild)
	{
		SAFE_DELETE(mChild);
		mChild = nextChild;
	}

	nextChild = 0;


	//�V�[�P���X�ԑJ��
	switch (mNextSeq)
	{
	case SEQ_TITLE: next = new Title(); break;
	case SEQ_CONFIG: next = new Config(); break;

	}

	mNextSeq = SEQ_NONE;

	return next;
}

void Parent::draw() const
{
	mChild->draw();
}

void Parent::moveTo(NextSequence _next)
{
	mNextSeq = _next;
}

}