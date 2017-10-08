#include "Needle.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS {

bool Needle::imgLoad = false;
int Needle::image;

Needle::Needle(int _x, int _y, float _angle) :
GimmickChild(Vector2(_x, _y))
{
	this->angle = _angle;

	initialize();
}

Needle::~Needle()
{

}

void Needle::initialize()
{
	loadImage();


	this->mTime = 0;
}

void Needle::update()
{

}

void Needle::draw(const Vector2* _camera) const
{
	//��ʓ��ɂ��Ȃ����return
	if (abs(pos.raw_x - _camera->raw_x) > 480000 || abs(pos.raw_y - _camera->raw_y) > 320000)return;

	int draw_x = MyData::CX + pos.x() - _camera->x();
	int draw_y = MyData::CY + pos.y() - _camera->y();

	//�`��
	DrawRotaGraph(draw_x, draw_y, 1.0, angle, image, true, false);
}

void Needle::apply(Character* _character)
{
	if(_character->isPlayer)_character->hpController.damage(this->damageValue);
}

bool Needle::onActiveArea(const Vector2* _player) const
{
	return isOverlap(_player);
}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Needle::loadImage()
{
	if (!imgLoad)
	{
		this->image = LoadGraph("Data/Image/Needle.png");
		assert((image != -1) && "Needle�摜�ǂݍ��݃G���[!");
	}
	imgLoad = true;
}



}
}
}