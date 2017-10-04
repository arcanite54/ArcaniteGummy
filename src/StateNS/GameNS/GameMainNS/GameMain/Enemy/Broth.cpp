#include "Broth.h"




namespace StateNS {
namespace GameNS {
namespace GameMainNS{
	
bool Broth::imgLoad = false;
int Broth::images[8];


Broth::Broth(int _x, int _y) : EnemyChild(100, _x, _y, 32, 32)
{
	loadImage();
	
	initialize();
};


Broth::~Broth()
{

}

void Broth::initialize()
{
	this->mDirection = false;
	this->moveSpeed = 0;
	this->mTime = 0;
}

void Broth::update(const StageChild* _stage,const Vector2* _camera)
{
	aTime++;
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
	mImage = images[actState * 2 + (aTime / 10) % 2];

}

void Broth::move(const StageChild* _stage, int& _dx, int& _dy)
{

	if (mTime >= 450)return;

	if (mTime % 60 <= 30) 
	{
		int tmp_dy = mTime % 60 < 15 ? getTopDiffer(_stage, -vectorRate, true) : getBottomDiffer(_stage, vectorRate, true);
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
void Broth::loadImage()
{
	if (!imgLoad)
	{
		int tmp = LoadDivGraph("Data/Image/Broth.png", 8, 8, 1, 32, 32, images);
		assert(tmp != -1 && "Broth�摜�ǂݍ��݃G���[");
	}
	imgLoad = true;
}

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
			a->setStatus(*player, mDirection);
			return;
		}
	}

	//���ׂĎg���Ă�����new����
	attacks.push_back(new Hammer(this, mDirection));
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
Broth::Hammer::Hammer(const Character* _parent, int _direction) :
Attack(_parent, _parent->getVector2()->raw_x, _parent->getVector2()->raw_y, 32, 32, ObjectID::ID_NONE)
{
	this->setStatus(Vector2::ZERO, _direction);

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

	this->p->raw_x += -dx;

	//0.866 ~= sin(Pi/3)
	float tmp = -8.0f * 0.866f * mTime + mTime * mTime/10.0f;
	this->p->raw_y = (int)(tmp * vectorRate) + sy;

}

void Broth::Hammer::draw(const Vector2* _camera) const
{
	//��ʓ��ɂ��Ȃ����return
	if (abs(p->raw_x - _camera->raw_x) > 480000 || abs(p->raw_y - _camera->raw_y) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, mTime * pi(1 / 15.0f), mImage, true, mDirection);
}

void Broth::Hammer::setStatus(Vector2 _player, int _direction)
{
	mTime = 0;
	this->isActive = true;
	this->mDirection = _direction;

	*(this->p) = *(parent->getVector2());

	sy = this->p->raw_y;

	this->dx = (int)GetRand(3) + 1;
	this->dx *= vectorRate;
	this->dx *= ((_direction) ? -1 : 1);
}

void Broth::Hammer::hittedAction()
{

}





}
}
}