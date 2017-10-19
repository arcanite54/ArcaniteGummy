#include "Clear.h"
#include "..\StateParent.h"

#include "Play.h"

#include "..\..\Data.h"
#include "..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {

Clear::Clear()
{
	initialize();
}


Clear::~Clear()
{
	sound->stopSoundOfFile();

}

void Clear::initialize()
{
	saved = false;
	sound->playSoundWithPath("Data/Sound/clear.mp3", BACK);
	LoadDivGraph("Data/Image/Character/chip_mokou.png", 32, 8, 4, 32, 64, images, TRUE);
	assert(*images != -1 && "���@�摜�ǂݍ��݃G���[");
	backImg = LoadGraph("Data/Image/clear.png");
}

Child* Clear::update(StateNS::Parent* _parent)
{
	if (!saved)
	{
		int nextStage = _parent->stageNum;

		//�N���A������
		if (nextStage == 53)nextStage = 11;
		else if (nextStage % 10 == 3)nextStage += 8;
		else ++nextStage;

		saveData->save(nextStage);
		saveData->resetCheckPoint();
		saved = true;
	}

	Child* next = this;

	if (Input_C())
	{
		_parent->moveTo(_parent->NextSequence::SEQ_TITLE);
	}

	//���̃X�e�[�W��
	if (Input_Z())
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
	DrawGraph(0, 0, backImg, FALSE);
	DrawGraph(100, 300, images[0], TRUE);
	DrawFormatString(250, 220, MyData::WHITE, "���肠�[�I");
	DrawFormatString(250, 320, MyData::WHITE, "Z�Ŏ���");
	DrawFormatString(250, 350, MyData::WHITE, "C�Ń^�C�g����");
}






}
}

