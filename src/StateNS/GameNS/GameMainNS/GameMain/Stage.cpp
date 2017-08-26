#include "Stage.h"
#include "Player\PlayerChild.h"
#include "Gimmick\GimmickChild.h"
#include "Gimmick\AllGimmicks.h"

#include "..\..\..\..\KeyInput.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Stage::Stage(int _stageID, int _mapID)
{
	initialize();

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
}

void Stage::initialize()
{
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(80, 176)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(112, 176)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(112, 208)));
	mGimmicks.push_back(new BeltConveyor(2.0, Vector2(144, 208)));
	mGimmicks.push_back(new BeltConveyor(0.5, Vector2(176, 208)));
	mGimmicks.push_back(new BeltConveyor(2.0, Vector2(208, 208)));
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
}

void Stage::draw(const Vector2* _camera) const
{
	DrawGraph(0, 0, mBackImg, true);
	drawMap(mapData, _camera);

	for (const auto& gimmick : mGimmicks)
	{
		if(gimmick->isActive)gimmick->draw(_camera);
	}
}

Stage::ChipType Stage::getChipType(const Vector2& _player) const
{

	int sub_x = _player.raw_x / MyData::vectorRate / MyData::CHIP_WIDTH;
	int sub_y = _player.raw_y / MyData::vectorRate / MyData::CHIP_HEIGHT;

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
Stage::ChipType Stage::getChipType(const RawVector2& _player) const
{
	return getChipType(Vector2(_player.pos_x, _player.pos_y));

	/*
	//�͈͊O(������̒[)�Ȃ�TYPE_RIGID��Ԃ�
	if (_player.pos_y() < 0 || _player.pos_x() < 0)
		return ChipType::TYPE_RIGID;

	int sub_y = _player.pos_y() / 32;
	int sub_x = _player.pos_x() / 32;

	//�͈͊O(�E�����̒[)�Ȃ�TYPE_RIGID��Ԃ�
	if (MyData::MAP_HEIGHT_NUM <= sub_y || MyData::MAP_WIDTH_NUM <= sub_x)
		return ChipType::TYPE_RIGID;

	return chip[mapData[sub_y][sub_x]].getChipType();
	//*/
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

	int tmp = LoadDivGraph(imgFile.c_str(), 7, 7, 1, 32, 32, mapChip);
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


