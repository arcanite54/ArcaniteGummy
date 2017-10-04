#include "Usagi.h"
#include "..\Stages\StageChild.h"



namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Usagi::Usagi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	if(!imgLoad)loadImage();
	assert(*mImage != -1 && "Usagi�摜�ǂݍ��݃G���[!");

	initialize();
};


Usagi::~Usagi()
{

}

void Usagi::initialize()
{
	this->mDirection = true;
	this->moveSpeed = 1000;
}

void Usagi::update(const StageChild* _stage,const Vector2* _camera)
{
	actState = ENE_ACT_WALK;
	aTime++;
	mTime++;

	standardAction(_stage);
	
}

void Usagi::move(const StageChild* _stage, int& _dx, int& _dy)
{
	_dx = getHorizontalDiffer(_stage, moveSpeed, _dy < 0);
	_dy = getBottomDiffer(_stage, 2000, _dx > 0);

	//�����̉��̃`�b�v��ChipType���Q�b�g
	RawVector2 pos = RawVector2(p->x(), p->y() + CHIP_HEIGHT);
	StageChild::ChipType chipType_under = _stage->getChipType(pos, false);

	//�����̑O�̃`�b�v��ChipType���Q�b�g
	pos = RawVector2(p->x() + CHIP_WIDTH / 4 * ((mDirection) ? 1: -1), p->y() - CHIP_HEIGHT / 2);
	StageChild::ChipType chipType_front = _stage->getChipType(pos, false);

	//�R���ǂŕ����]��
	if( !( _stage->isRigid_down(chipType_under) || _stage->isSlant(chipType_under) ) || 
		chipType_front == StageChild::ChipType::TYPE_RIGID )
	{
		_dy = 0;
		mDirection = !mDirection;
		moveSpeed = -moveSpeed;
		this->p->raw_x += moveSpeed * 5;
	}
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