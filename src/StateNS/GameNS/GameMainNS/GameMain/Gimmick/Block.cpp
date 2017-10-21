#include "Block.h"

#include "..\Character.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

bool Block::imgLoad = false;
int Block::image[4];

Block::Block(int _x, int _y, double _scale) :
	Block(_x, _y, _scale, TYPE_FRAGILE){ }

Block::Block(int _x, int _y, double _scale, BlockType _blockType) :
DynamicGimmickChild(_x, _y, _scale),
isBreakable(_blockType & 0b0001),
blockType(_blockType)
{
	this->width  = (int)(32 * _scale);
	this->height = (int)(32 * _scale);
	
	initialize();
}

Block::~Block()
{
	//DeleteGraph�͂��Ȃ�
}

void Block::initialize()
{
	loadImage();

	//�摜�̃^�C�v��ݒ�
	int imageNum = 0;
	for (int i = 0; i < 4; i++)
	{
		if (blockType & (1 << i))imageNum = i;
	}

	mImage = image[imageNum];

	dy = 0;
}

void Block::update(const StageChild* _stage)
{
	standardMove(_stage);


	//this->dy = getBottomDiffer(_stage, 4000);
	//this->p->raw_y += this->dy;
}

void Block::draw(const Vector2* _camera) const
{
	standardDraw(_camera, scale, mImage, mDirection);
}

void Block::apply(Character* _character)
{
	_character->moveCharacter(0.0f, (float)dy);
}

void Block::hittedAction()
{
	if(isBreakable)this->isActive = false;
}

void Block::burnedAction()
{
	//TODO -> �A�j���[�V����������

	//�R�₳���Ə�����
	this->isActive = false;
}

bool Block::isOverlap(const Vector2* _player) const
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

bool Block::onActiveArea(const Vector2* _player) const
{
	return false;
}

//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Block::loadImage()
{
	if (!imgLoad)
	{
		this->image[0] = LoadGraph("Data/Image/block_fragile.png");
		this->image[1] = LoadGraph("Data/Image/block_wood.png");
		this->image[2] = LoadGraph("Data/Image/block_switch.png");
		this->image[3] = LoadGraph("Data/Image/block_lock.png");

		assert(image[0] != -1 && "block_fragile�ǂݍ��݃G���[!");
		assert(image[1] != -1 && "block_wood�ǂݍ��݃G���[!");
		assert(image[2] != -1 && "block_switch�ǂݍ��݃G���[!");
		assert(image[3] != -1 && "block_lock�ǂݍ��݃G���[!");
	}
	imgLoad = true;
}


}
}
}