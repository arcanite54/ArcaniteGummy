#include "Yachamo.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Yachamo::imgLoad = false;
int Yachamo::images[8];

Yachamo::Yachamo(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	loadImage();
	
	initialize();
};


Yachamo::~Yachamo()
{
	//DeleteGraph�͂��Ȃ�
}

void Yachamo::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 0;
}

void Yachamo::update(const StageChild* _stage, const Vector2* _camera)
{

	if (actState == ENE_ACT_ATTACK || actState == ENE_ACT_DEAD) {
		if (aTime >= 60)actState = ENE_ACT_NONE;
	}
	aTime++;
	mTime++;

	standardAction(_stage);
	this->mDirection = player->raw_x > this->p->raw_x;


	if (mTime % 150 == 0)
	{
		aTime = 0;
		actState = ENE_ACT_ATTACK;
		attack(_stage);
	}
	mImage = images[actState * 2 + (aTime / 10) % 2];


	//�U��
	for (auto& a : attacks)
	{
		if (a->isActive)
		{
			a->update();
			a->checkActive(_camera);
		}
	}





}

void Yachamo::move(const StageChild* _stage, int& _dx, int& _dy)
{
	

}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Yachamo::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Yachamo.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Yachamo�摜�ǂݍ��݃G���[");
	}
	imgLoad = true;
}

void Yachamo::hittedAction()
{
	aTime = 0;
	actState = ENE_ACT_DEAD;
}

void Yachamo::attack(const StageChild* _stage)
{
	int dx = mDirection ? 5 : -5;

	//�g���Ă��Ȃ��I�u�W�F�N�g���ė��p
	for (auto& a : attacks)
	{
		if (!a->isActive)
		{
			a->setStatus(*p, dx);
			a->isActive = true;
			return;
		}
	}

	//���ׂĎg���Ă�����new����
	attacks.push_back(new Fire(this, _stage, this->p->raw_x, this->p->raw_y, dx));
}

void Yachamo::draw_other(const Vector2* _camera) const
{
	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}
}

//==============================================
//Fire�N���X
//==============================================
Yachamo::Fire::Fire(const EnemyChild* _parent, const StageChild* _stage, int _x, int _y, int _dx) :
Attack(_parent, _x, _y, 32, 32, ObjectID::ID_NONE),
stage(_stage)
{
	this->dx = _dx * MyData::vectorRate;
	mDirection = _dx < 0;

	//for Debug
	this->damageValue = 20;

//	mImage = 0;
//	int tmp = LoadDivGraph("Data/Image/Fire.png", 3, 1, 3, 96, 32, images);
	mImage = LoadGraph("Data/Image/Yachamo_fire.png");
	assert(mImage != -1 && "���`����Fire�摜�ǂݍ��݃G���[");
}

Yachamo::Fire::~Fire()
{
	DeleteGraph(mImage);
}

void Yachamo::Fire::update()
{
	int dx_tmp = getHorizontalDiffer(stage, dx, false, false);
	this->p->raw_x += dx_tmp;

	if (dx_tmp == 0)this->isActive = false;
}

void Yachamo::Fire::setStatus(Vector2 _pos, int _dx)
{
	*(this->p) = _pos;
	this->dx = _dx * MyData::vectorRate;
	this->mDirection = _dx < 0;
}

void Yachamo::Fire::hittedAction()
{
	this->isActive = false;
}





}
}
}