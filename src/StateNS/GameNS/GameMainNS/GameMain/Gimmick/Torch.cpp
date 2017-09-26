#include "Torch.h"

#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


//���̃N���X�̊֐���Map.cpp�ł͂Ȃ�Stage00�ŌĂ�
//���Ƃɂ����, ��ʂ𖾂邭���鏈���Ȃǂ��ʂ̊֐����Ăׂ�̂Ŋy
//if(torches->isDark()){ this->chengeToDark(); }	�I�Ȃ�.
Torch::Torch(int _x, int _y) : 
DynamicGimmickChild(_x, _y, 1.0)
{
	initialize();
}

Torch::~Torch()
{
	DeleteGraph(mImage);
}

void Torch::initialize()
{
	loadImage();

	isActive = true;
	this->isBurned = false;
	this->mTime = 900;

	mImage = images[0];
}

void Torch::update(const StageChild* _stage)
{
	//�΂���������
	if (++mTime > 600)
	{
		isBurned = false;
		mImage = images[0];
	}
	else mImage = images[1];
}

void Torch::draw(const Vector2* _camera) const
{
	standardDraw(_camera, p, mImage, true);
}

void Torch::apply(Character* _character)
{
	//_character->���E���L������()
}

void Torch::hittedAction()
{

}

void Torch::burnedAction()
{
	this->isBurned = true;
	mTime = 0;
}

bool Torch::isOverlap(const Vector2* _player) const
{
	return standardOverLap(_player);

	/*
	int tmp_w = this->width  * vectorRate / 2;
	int tmp_h = this->height * vectorRate / 2;

	return
		this->p->raw_x - tmp_w < _player->raw_x &&
		this->p->raw_x + tmp_w > _player->raw_x &&
		this->p->raw_y - tmp_h < _player->raw_y &&
		this->p->raw_y + tmp_h > _player->raw_y;
	*/

	/* Collision�̓����蔻��
	return
		this->p->raw_x			      < other->p->raw_x + other->width  &&
		this->p->raw_x + this->width  > other->p->raw_x					&&
		this->p->raw_y			      < other->p->raw_y + other->height &&
		this->p->raw_y + this->height > other->p->raw_y;
	*/
}

bool Torch::onActiveArea(const Vector2* _player) const
{
	//�R���Ă�����return true
	return isBurned;
}

StageChild::ChipType Torch::getChipType() const
{
	return StageChild::ChipType::TYPE_BACK;
}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Torch::loadImage()
{
	//TODO �摜�����ւ�
	int tmp = LoadDivGraph("Data/Image/Torch.png", 2, 2, 1, 32, 32, images);
	assert(tmp != -1 && "�X�C�b�`�摜�ǂݍ��݃G���[�I");
}


}
}
}