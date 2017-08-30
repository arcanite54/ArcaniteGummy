#include "Usagi.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Usagi::Usagi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Usagi�摜�ǂݍ��݃G���[!");

	initialize();
};


Usagi::~Usagi()
{

}

void Usagi::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 3000;
}

void Usagi::update(const Stage* _stage)
{
	mTime++;
	standardAction(_stage);
	
}

void Usagi::move(const Stage* _stage, int& _dx, int& _dy)
{
	_dx = 0;// getHorizontalDiffer(_stage, moveSpeed);
	_dy = getBottomDiffer(_stage, 4000);

	//_dx��0�ŕǂɂԂ���
	if (_dx == 0)
	{
		mDirection = !mDirection;
		moveSpeed = -moveSpeed;
	}

	//_dy��0�łȂ�������󒆂ɂ���
	if (_dy != 0)_dx = 0;
}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================

void Usagi::hittedAction()
{

}

}
}
}