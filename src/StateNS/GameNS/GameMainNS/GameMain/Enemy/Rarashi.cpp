#include "Rarashi.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Rarashi::imgLoad = false;
int Rarashi::images[8];


Rarashi::Rarashi(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	loadImage();
	
	initialize();
};


Rarashi::~Rarashi()
{
	//DeleteGraph�͂��Ȃ�
}

void Rarashi::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 3000;
	actState = ENE_ACT_WALK;
	//���G
	hpController.isMuteki = true;
}

void Rarashi::update(const StageChild* _stage,const Vector2* _camera)
{
	actState = ENE_ACT_WALK;
	aTime++;
	mTime++;
	standardAction(_stage);	
	mImage = images[actState * 2 + (aTime / 10) % 2];

}

void Rarashi::move(const StageChild* _stage, int& _dx, int& _dy)
{
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
void Rarashi::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Rarashi.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Rarashi�摜�ǂݍ��݃G���[");
	}
	imgLoad = true;
}

void Rarashi::hittedAction()
{
	DrawCircle(100, 200, 5, GREEN);
}



}
}
}