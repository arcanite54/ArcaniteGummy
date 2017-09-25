#include "Poppy.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Poppy::Poppy(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Poppy�摜�ǂݍ��݃G���[!");

	initialize();
};


Poppy::~Poppy()
{
	this->mDirection = player->raw_x > this->p->raw_x;
}

void Poppy::initialize()
{

}

void Poppy::update(const StageChild* _stage, const Vector2* _camera)
{
	//���ɒ��i���邾��
	mTime++;

	standardAction(_stage);
}

void Poppy::move(const StageChild* _stage, int& _dx, int& _dy)
{
	int x = this->mDirection ? 1 : -1;
	_dx = getHorizontalDiffer(_stage, x * vectorRate, _dy < 0);
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