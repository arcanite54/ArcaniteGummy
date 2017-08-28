#include "Enemychild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

EnemyChild::EnemyChild(int _hp, int _x, int _y, int _w, int _h) : Character(_hp, _x, _y, _w, _h)
{
	initialize();
}

EnemyChild::~EnemyChild()
{

}

void EnemyChild::initialize()
{
	this->mTime = 0;
	this->isAlive = true;
	this->mDirection = false;
}

void EnemyChild::draw(const Vector2* _camera) const
{
	//��ʓ��ɂ��Ȃ����return
	if (abs(p->pos_x() - _camera->pos_x()) > 350000 || abs(p->pos_y() - _camera->pos_y()) > 270000)return;


	int draw_x = 320 + (p->pos_x() - _camera->pos_x()) / MyData::vectorRate;
	int draw_y = 240 + (p->pos_y() - _camera->pos_y()) / MyData::vectorRate;

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, 0.0, mImage, true, mDirection);
}

void EnemyChild::standardAction(const Stage* _stage)
{
	++mTime;
	standardMove(_stage);
}


void EnemyChild::standardMove(const Stage* _stage)
{
	//�L������㒆�Ȃ�return
	if (!isAlive)return;

	int dx = next_dx;
	int dy = next_dy;

	next_dx = next_dy = 0;


	//�ړ�
	//�����͎Q�Ɠn��
	this->move(_stage, dx, dy);

	p->raw_x += dx;
	p->raw_y += dy;
}

}
}
}