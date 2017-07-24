#include "Stage.h"
#include "Player\PlayerChild.h"
#include "Gimmick\GimmickChild.h"

#include "..\..\..\..\KeyInput.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Stage::Stage(int _stageID)
{
	loadMap(_stageID);
	initialize();
}

Stage::~Stage()
{
	mGimmicks.clear();
	mGimmicks.shrink_to_fit();
}

void Stage::initialize()
{
	mBackImg = LoadGraph("Data/Image/back.jpg");
	assert(mBackImg != -1 && "�w�i�摜�ǂݍ��݃G���[");
}

void Stage::update(PlayerChild* _player)
{
	for (auto& gimmick : mGimmicks)
	{
		if (gimmick->isActive)gimmick->update(_player);
	}
}

void Stage::draw(const Vector2* _camera) const
{
	DrawGraph(0, 0, mBackImg, true);
	drawMap(mapData, _camera);

	for (const auto& gimmick : mGimmicks)
	{
		if(gimmick->isActive)gimmick->draw();
	}

}

Stage::ChipType Stage::getChipType(const Vector2 _player) const
{
	//�͈͊O(������̒[)�Ȃ�TYPE_RIGID��Ԃ�
	if (_player.pos_y < 0 || _player.pos_x < 0)
		return ChipType::TYPE_RIGID;

	int sub_y = _player.y() / 32;
	int sub_x = _player.x() / 32;

	//�͈͊O(�E�����̒[)�Ȃ�TYPE_RIGID��Ԃ�
	if (MyData::MAP_HEIGHT_NUM <= sub_y || MyData::MAP_WIDTH_NUM <= sub_x)
		return ChipType::TYPE_RIGID;

	return chip[mapData[sub_y][sub_x]].getChipType();
}

Stage::ChipType Stage::getChipType(const RawVector2 _player) const
{
	//�͈͊O(������̒[)�Ȃ�TYPE_RIGID��Ԃ�
	if (_player.pos_y < 0 || _player.pos_x < 0)
		return ChipType::TYPE_RIGID;

	int sub_y = _player.pos_y / 32;
	int sub_x = _player.pos_x / 32;

	//�͈͊O(�E�����̒[)�Ȃ�TYPE_RIGID��Ԃ�
	if (MyData::MAP_HEIGHT_NUM <= sub_y || MyData::MAP_WIDTH_NUM <= sub_x)
		return ChipType::TYPE_RIGID;

	return chip[mapData[sub_y][sub_x]].getChipType();
}



//========================================================================
// ����private�֐�
//========================================================================
void Stage::loadMap(int _stageID)
{
	string imgFile = "Data/Image/block";
	imgFile += std::to_string(_stageID);
	imgFile += ".png";

	int tmp = LoadDivGraph(imgFile.c_str(), 7, 7, 1, 32, 32, mapChip);
	assert(tmp != -1 && "�}�b�v�`�b�v�ǂݍ��݃G���[");

	string textFile = "Data/Text/stage";
	textFile += std::to_string(_stageID);
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
	//�}�b�v�`�������ۂɁC���@�̈ʒu�ˑ��ŕ`��ʒu�̍��W���ς��

	int draw_x = _camera->pos_x / MyData::vectorRate - MyData::CX;
	int draw_y = _camera->pos_y / MyData::vectorRate - MyData::CY;

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


