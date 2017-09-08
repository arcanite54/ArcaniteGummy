#include "Stage.h"
#include "Player\PlayerChild.h"
#include "Gimmick\GimmickChild.h"
#include "Gimmick\DynamicGimmickChild.h"
#include "Gimmick\AllGimmicks.h"

#include "..\..\..\..\KeyInput.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Stage::Stage(int _stageID, int _mapID)
{
	initialize();

	//for Debug
	loadMap(_stageID, _mapID);
	mBackImg = LoadGraph("Data/Image/back.jpg");
	assert(mBackImg != -1 && "�w�i�摜�ǂݍ��݃G���[");
}

Stage::~Stage()
{
	for (auto& gimmick : mGimmicks)
	{
		SAFE_DELETE(gimmick);
	}
	mGimmicks.clear();
	mGimmicks.shrink_to_fit();

	for (auto& gimmick : mDynamicGimmicks)
	{
		SAFE_DELETE(gimmick);
	}
	mDynamicGimmicks.clear();
	mDynamicGimmicks.shrink_to_fit();
}

void Stage::initialize()
{
	//loadGimmick()
	//�Ƃ������֐��ŊO���̃e�L�X�g�f�[�^����ǂݍ���

	mDynamicGimmicks.push_back(new Block(700, 1520, 3.0));
	mDynamicGimmicks.push_back(new Block(560, 1536, 2.0));
	mDynamicGimmicks.push_back(new Block(500, 1552, 1.0));

	mDynamicGimmicks.push_back(new Block(160, 1500, 3.0));
	mDynamicGimmicks.push_back(new Block(280, 1500, 2.0));
	mDynamicGimmicks.push_back(new Block(400, 1500, 1.0));


	/*
	//for Debug
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(80, 176)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(112, 176)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(112, 208)));
	mGimmicks.push_back(new BeltConveyor(2.0, Vector2(144, 208)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(176, 208)));
	mGimmicks.push_back(new BeltConveyor(2.0, Vector2(208, 208)));

	mGimmicks.push_back(new Spring(2.0, Vector2(240, 384)));
	mDynamicGimmicks.push_back(new Block(80, 176, 32, 32));
	*/
}

void Stage::update(PlayerChild* _player)
{
	for (auto& gimmick : mGimmicks)
	{
		if (gimmick->isActive)
		{
			gimmick->update();

			if (gimmick->onActiveArea(_player->getVector2()))
				gimmick->apply(_player);
		}
	}

	for (auto& d_gimmick : mDynamicGimmicks)
	{
		if (d_gimmick->isActive)
		{
			d_gimmick->update(this);
		}
	}

}

void Stage::draw(const Vector2* _camera) const
{
	DrawGraph(0, 0, mBackImg, true);
	drawMap(mapData, _camera);

	//�M�~�b�N�̕`��
	for (const auto& gimmick : mGimmicks)
	{
		if(gimmick->isActive)gimmick->draw(_camera);
	}

	//�_�C�i�~�b�N�M�~�b�N�̕`��
	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		if(d_gimmick->isActive)d_gimmick->draw(_camera);
	}
}

int Stage::getTopPosition(const Vector2* _pos, const int& _dy) const
{
	//����������W�ɑ���Object����������A����Object�̏��y���W��Ԃ�

	int ret = fixToVectorHeight(_pos->pos_y());

	//*
	//���������[�N����
	Vector2* tmp = new Vector2(_pos->pos_x(), _pos->pos_y() + _dy, true);

	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		//������RIGID��d_gimmick������Ȃ�
		if (d_gimmick->isOverlap(tmp) && isRigid_down(d_gimmick->getChipType()))
		{
			ret = d_gimmick->getTopPosition();
		}
	}

	//���������[�N����
	SAFE_DELETE(tmp);
	//*/


	return ret;
}

Stage::ChipType Stage::getChipType(const Vector2& _other, bool isPlayer) const
{
	int sub_x = _other.raw_x / MyData::vectorRate / MyData::CHIP_WIDTH;
	int sub_y = _other.raw_y / MyData::vectorRate / MyData::CHIP_HEIGHT;

	//Stage�͈̔͊O(������̒[)�Ȃ�TYPE_RIGID��Ԃ�
	if (sub_y < 0 || sub_x < 0)
		return ChipType::TYPE_RIGID;


	//Stage�͈̔͊O(�E�����̒[)�Ȃ�TYPE_RIGID��Ԃ�
	if (MyData::MAP_HEIGHT_NUM * stage_max_y <= sub_y || 
		MyData::MAP_WIDTH_NUM  * stage_max_x <= sub_x)
		return ChipType::TYPE_RIGID;

	
	ChipType ret = TYPE_BACK;
	if(sub_y < MyData::MAP_HEIGHT_NUM && sub_x < MyData::MAP_WIDTH_NUM)
		ret = chip[mapData[sub_y][sub_x]].getChipType();

	if (!isPlayer)return ret;

	//Player�Ȃ�ȉ���ǂ�

	//TODO
	//���̂܂܂��ƁAGimmick�̂ق���D�悵���Ⴄ
	//�܂�ARIGID��DynamicGimmick��BACK��Gimmick���d�Ȃ�Ɠ��߂����Ⴄ
	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		if (d_gimmick->isActive)
		{
			if (d_gimmick->isOverlap(&_other))
			{
				ret = d_gimmick->getChipType();
			}
		}
	}

	//for Debug
	return ret;

	for (const auto& gimmick : mGimmicks)
	{
		if (gimmick->isActive)
		{
			if (gimmick->isOverlap(sub_x, sub_y))
			{
				ret = gimmick->getChipType();
			}
		}
	}
	return ret;
}

//�|�����[�t�B�Y��
Stage::ChipType Stage::getChipType(const Vector2& _other) const
{
	return getChipType(_other, true);
}

Stage::ChipType Stage::getChipType(const RawVector2& _other, bool _isPlayer) const
{
	return getChipType(Vector2(_other.pos_x, _other.pos_y), _isPlayer);
}



//========================================================================
// ����private�֐�
//========================================================================
void Stage::loadMap(int _stageID, int _mapID)
{
	//string imgFile = "Data/Image/block";
	//imgFile += std::to_string(_stageID);
	//imgFile += ".png";
	string imgFile = "Data/Image/block0.png";

	int tmp = LoadDivGraph(imgFile.c_str(), 9, 9, 1, 32, 32, mapChip);
	assert(tmp != -1 && "�}�b�v�`�b�v�ǂݍ��݃G���[");

	string textFile = "Data/Text/stage";
	textFile += std::to_string(_mapID);
	textFile += ".txt";

	std::ifstream fin(textFile);
	assert(fin && "�}�b�v�f�[�^�ǂݍ��݃G���[");

	for (auto& mapY : mapData)
	{
		for (auto& mapX : mapY)
		{
			fin >> mapX;
		}
	}

}



//�}�b�v�`�b�v���ς���Ă��Ή��\
//�������Ƀ}�b�v�`�b�v�ւ̃|�C���^�������Ă��邽�߂�template���g�p
template<typename Arr>
void Stage::drawMap(Arr _mapData, const Vector2* _camera) const
{
	//�}�b�v�`�������ۂɁC�J�����̈ʒu�ˑ��ŕ`��ʒu�̍��W���ς��
	int draw_x = _camera->x() - MyData::CX;
	int draw_y = _camera->y() - MyData::CY;


	//�}�b�v�`��
	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = 0; x < mapData[0].size(); x++)
		{
			DrawGraph(x * 32 - draw_x, y * 32 - draw_y, mapChip[_mapData[y][x]], true);
		}
	}
}





}
}
}


