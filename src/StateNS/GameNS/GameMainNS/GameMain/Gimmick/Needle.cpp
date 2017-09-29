#include "Needle.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {


Needle::Needle(int _x, int _y,float _angle) :
DynamicGimmickChild(_x, _y, 1.0)
{
	this->width  = 32;
	this->height = 32;


	this->angle = _angle;

	initialize();
}

Needle::~Needle()
{
	DeleteGraph(img);

}

void Needle::initialize()
{
	loadImage();


	this->mTime = 0;
}

void Needle::update(const StageChild* _stage)
{
	//if (0 + order * 180 <= mTime && mTime <= 180 + order * 180)isEmerge = true;
	//else isEmerge = false;

	move();
}

void Needle::draw(const Vector2* _camera) const
{

	//��ʓ��ɂ��Ȃ����return
	if (abs(p->pos_x() - _camera->pos_x()) > 480000 || abs(p->pos_y() - _camera->pos_y()) > 320000)return;

	int draw_x = 320 + p->x() - _camera->x();
	int draw_y = 240 + p->y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, angle, img, true, mDirection);



	//for Debug

}

void Needle::apply(Character* _character)
{
	if(_character->isPlayer)_character->hpController.damage(this->damageValue);
}

void Needle::hittedAction()
{
	/* do nothing */
}

void Needle::burnedAction()
{
	/* do nothing */
}

bool Needle::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);
}

bool Needle::onActiveArea(const Vector2* _player) const
{
	return
		abs(this->p->x() - _player->x()) <= MyData::CHIP_WIDTH*2/3 &&
		abs(this->p->y() - _player->y()) <= MyData::CHIP_HEIGHT*2/3;

}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Needle::loadImage()
{
	//TODO �o�[�i�[�p�̉摜�ɍ����ւ�
	this->img = LoadGraph("Data/Image/Needle.png");
	assert((img != -1)&& "Needle�摜�ǂݍ��݃G���[!");
}

void Needle::move()
{
	
}




}
}
}