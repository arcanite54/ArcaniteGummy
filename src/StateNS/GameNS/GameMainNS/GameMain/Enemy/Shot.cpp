#include "Shot.h"
#include "..\Character.h"
#include <cmath>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


bool Shot::imgLoad = false;
int Shot::images[3];

//画像使用バージョン
Shot::Shot(const Character* parent, int _x, int _y, float _angle, float _speed, int _damage) :
Attack(parent, _x, _y, 15, 15)
{
	this->angle = pi(1 / 180.0f) * _angle;
	this->dx = (int)(_speed * cos(angle));
	this->dy = (int)(_speed * sin(angle));
	this->damageValue = _damage;

	initialize();
}


Shot::~Shot() 
{
	//DeleteGraphはしない
}

void Shot::initialize()
{
	isActive = true;
	//loadImage();
	assert(mImage != -1 && "Shot画像読み込みエラー!");
}

void Shot::update() 
{

	//画面外にあったらreturn
	if (!isActive)return;

	++time;

	//移動
	p->raw_x += dx;
	p->raw_y += dy;
}

void Shot::draw(const Vector2* _camera) const 
{
	//画面外にあったら描画なし
	if (!isActive)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true);
}

void Shot::setStatus_2args(Vector2 pos, int _angle, int _speed)
{
	this->isActive = true;
	if (pos != Vector2::ZERO)*p = pos;
	this->angle = pi(1 / 180.0f) * _angle;

	if (_speed != 0)
	{
		this->dx = (int)(_speed * cosf(angle));
		this->dy = (int)(_speed * sinf(angle));
	}
}

void Shot::loadImage() 
{
	if (!imgLoad)
	{
		images[0] = LoadGraph("Data/Images/Shot1.png");
		assert(images[0] != -1 && "shot1画像読み込みエラー");

		images[1] = LoadGraph("Data/Images/Shot2.png");
		assert(images[1] != -1 && "shot2画像読み込みエラー");

		images[2] = LoadGraph("Data/Images/Shot3.png");
		assert(images[2] != -1 && "shot3画像読み込みエラー");
	}
	imgLoad = true;
}


float sinf_degree(int degree) { return sinf(pi(degree / 180.0f)); }
float cosf_degree(int degree) { return cosf(pi(degree / 180.0f)); }



}
}
}