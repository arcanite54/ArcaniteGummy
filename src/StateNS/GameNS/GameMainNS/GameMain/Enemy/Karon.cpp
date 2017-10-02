#include "Karon.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Karon::Karon(int _x, int _y) : EnemyChild(100000, _x, _y, 32, 32)
{
	if(!imgLoad)loadImage();
	assert(*mImage != -1 && "Karon�摜�ǂݍ��݃G���[!");

	initialize();
};


Karon::~Karon()
{

}

void Karon::initialize()
{
	this->mDirection = true;
	this->moveSpeed = 1000;
	this->isAlive = true;

}

void Karon::update(const StageChild* _stage,const Vector2* _camera)
{
	aTime++;
	actState = ENE_ACT_WALK;
	if (damaged && isAlive) 
	{

		hpController.damage(-500);
		isAlive = false;
		hpController.isMuteki = true;
	}


	if (!isAlive) {
		actState = ENE_ACT_DEAD;
		mTime++;
	}
	else mTime = 0;

	if (mTime == 300) 
	{
		isAlive = true;
		hpController.isMuteki = false;
	}
	standardAction(_stage);
	

}

void Karon::move(const StageChild* _stage, int& _dx, int& _dy)
{
	if (!isAlive)return;
	_dy = getBottomDiffer(_stage, 4000, _dx < 0);

	//_dy��0�łȂ�������󒆂ɂ���
	if (_dy != 0)
	{
		/*�������R�����g�A�E�g����ƁC�����ŗ�����
		//�E���̃`�b�v
		RawVector2 pos = RawVector2(p->x() + 1, p->y() + 16);
		Stage::ChipType chipType_right = _stage->getChipType(pos, false);

		//�����̃`�b�v
		pos = RawVector2(p->x() - 1, p->y() + 16);
		Stage::ChipType chipType_left = _stage->getChipType(pos, false);
		
		//�E���ƍ������ǂƋ󒆂Ȃ�C�R�Ȃ�
		//�����]������
		if (
			(_stage->isRigid_down(chipType_right) && chipType_left == _stage->TYPE_BACK) ||
			(_stage->isRigid_down(chipType_left) && chipType_right == _stage->TYPE_BACK)
			)
		{
			_dy = 0;
			mDirection = !mDirection;
			moveSpeed = -moveSpeed;
		}
		else//*/
		{
			_dx = 0;
			return;
		}

	}

	_dx = getHorizontalDiffer(_stage, moveSpeed, _dy < 0);
	this->mDirection = _dx > 0;

	//_dx��0�ŕǂɂԂ���
	if (_dx == 0)
	{
		_dy = 0;
		mDirection = !mDirection;
		moveSpeed = -moveSpeed;
	}

}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================

void Karon::hittedAction()
{

}

}
}
}