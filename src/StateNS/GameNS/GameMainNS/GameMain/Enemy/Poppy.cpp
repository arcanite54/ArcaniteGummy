#include "Poppy.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Poppy::Poppy(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32, 1, 1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Poppy�摜�ǂݍ��݃G���[!");

	initialize();
};

Poppy::~Poppy()
{
	DeleteGraph(images);
}

void Poppy::initialize()
{
	mTime = 0;
	this->mDirection = false;
}

void Poppy::update(const StageChild* _stage, const Vector2* _camera)
{
	if(mTime == 0)this->mDirection = player->raw_x > this->p->raw_x;

	//���ɒ��i���邾��
	mTime++;

	standardAction(_stage);
}

void Poppy::move(const StageChild* _stage, int& _dx, int& _dy)
{
	int x = this->mDirection ? vectorRate : -vectorRate;
	
	_dx = getHorizontalDiffer(_stage, x, _dy < 0);
}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Poppy::hittedAction()
{

}


}
}
}