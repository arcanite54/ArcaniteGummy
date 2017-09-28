#include "Broth.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Broth::Broth(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32,1,1)
{
	if(!imgLoad)loadImage();
	assert(mImage != -1 && "Broth�摜�ǂݍ��݃G���[!");

	initialize();
};


Broth::~Broth()
{
	DeleteGraph(mImage);
}

void Broth::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 0;
	this->mTime = 0;
}

void Broth::update(const StageChild* _stage,const Vector2* _camera)
{
	mTime++;
	mTime %= 630;
	standardAction(_stage);
	this->mDirection = player->raw_x > this->p->raw_x;

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

void Broth::move(const StageChild* _stage, int& _dx, int& _dy)
{

	if (mTime >= 450)return;

	if (mTime % 60 < 30) 
	{
		int tmp_dy = mTime % 60 < 15 ? getTopDiffer(_stage, -1 * vectorRate, true) : getBottomDiffer(_stage, 1 * vectorRate, true);
		_dy = tmp_dy;
	}
	
	if (mTime%60 == 15)
	{
		attack(_stage);
	}


}


//==============================================
//�����v���C�x�[�g�֐�
//==============================================

void Broth::hittedAction()
{

}

void Broth::attack(const StageChild* _stage)
{
	int dx = mDirection ? 5 : -5;

	//�g���Ă��Ȃ��I�u�W�F�N�g���ė��p
	for (auto& a : attacks)
	{
		if (!a->isActive)
		{
			a->setStatus(*player, 5000);
			return;
		}
	}

	//���ׂĎg���Ă�����new����
	attacks.push_back(new Hammer(this, _stage, player->raw_x, player->raw_y, 5000));
}

void Broth::draw_other(const Vector2* _camera) const
{
	for (const auto& a : attacks)
	{
		if (a->isActive)a->draw(_camera);
	}
}

//==============================================
//Hammer�N���X
//==============================================
Broth::Hammer::Hammer(const Character* _parent, const StageChild* _stage, int _x, int _y, int _speed) :
Attack(_parent, _parent->getVector2()->raw_x, _parent->getVector2()->raw_y, 32, 32, ObjectID::ID_NONE),
stage(_stage)
{
	this->setStatus(Vector2(_x, _y, true), _speed);

	//for Debug
	this->damageValue = 20;

	mImage = LoadGraph("Data/Image/BrothAttack.png");
	assert(mImage != -1 && "BrothAttack�摜�ǂݍ��݃G���[");
}

Broth::Hammer::~Hammer()
{
	DeleteGraph(mImage);
}

void Broth::Hammer::update()
{
	mTime++;
//	int dx_tmp = getHorizontalDiffer(stage, -vectorRate, false, false);
//	int dy_tmp = getHorizontalDiffer(stage, (2*mTime-100)/30.0f*vectorRate, false, false);

//	this->p->raw_x += dx_tmp;
//	this->p->raw_y += dy_tmp;

	this->p->raw_x += -dx*vectorRate;
	float tmp =-8.0f*sinf(Pi/3)*mTime+mTime*mTime/10.0f;
	this->p->raw_y = tmp*vectorRate+sy;


	//if (dx_tmp == 0 || dy_tmp == 0)this->isActive = false;
}

void Broth::Hammer::draw(const Vector2* _camera) const
{
	//��ʓ��ɂ��Ȃ����return
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, mTime * pi(1 / 15.0f), mImage, true, mDirection);
}

void Broth::Hammer::setStatus(Vector2 _player, int _speed)
{
	mTime = 0;
	this->isActive = true;
	this->mDirection = this->dx < 0;

	*(this->p) = *(parent->getVector2());

	float differ_x = (float)(this->p->raw_x - _player.raw_x);
	float differ_y = (float)(this->p->raw_y - _player.raw_y);

	sy = this->p->raw_y;

	float angle = atan2f(differ_y, differ_x) + Pi;
	this->dx = (int)GetRand(3)+1;
//	this->dy = (int)(_speed * sinf(angle));
}

void Broth::Hammer::hittedAction()
{
	this->isActive = false;
}





}
}
}