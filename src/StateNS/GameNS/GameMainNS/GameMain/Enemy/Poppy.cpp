#include "Poppy.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Poppy::imgLoad = false;
int Poppy::images[8];


Poppy::Poppy(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	if(!imgLoad)loadImage();
	//assert(*mImage != -1 && "Poppy�摜�ǂݍ��݃G���[!");
	initialize();
};

Poppy::~Poppy()
{
	//DeleteGraph�͂��Ȃ�
}

void Poppy::initialize()
{
	mTime = 0;
	this->mDirection = false;
	actState = ENE_ACT_WALK;
}

void Poppy::update(const StageChild* _stage, const Vector2* _camera)
{
	if (actState == ENE_ACT_DEAD && aTime >= 60)actState = ENE_ACT_WALK;

	aTime++;

	if(mTime == 0)this->mDirection = player->raw_x > this->p->raw_x;

	//���ɒ��i���邾��
	mTime++;

	standardAction(_stage);
	mImage = images[actState * 2 + (aTime / 10) % 2];

}

void Poppy::move(const StageChild* _stage, int& _dx, int& _dy)
{
	int x = this->mDirection ? vectorRate : -vectorRate;
	
	_dx = getHorizontalDiffer(_stage, x, _dy < 0);
	if (_dx == 0)mDirection = !mDirection;
	
}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Poppy::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Poppy.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Poppy�摜�ǂݍ��݃G���[");
	}
	imgLoad = true;
}

void Poppy::hittedAction()
{
	aTime = 0;
	actState = ENE_ACT_DEAD;
}


}
}
}