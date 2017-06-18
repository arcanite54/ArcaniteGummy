#include "Stage.h"
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

}

void Stage::update()
{


}

void Stage::draw(const Vector2* _player) const
{
	drawMap(mapData, _player);

	for (auto gimmick : mGimmicks)
	{
		gimmick->draw();
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




//========================================================================
// ����private�֐�
//========================================================================

//�}�b�v�`�b�v���ς���Ă��Ή��\
//�������Ƀ}�b�v�`�b�v�ւ̃|�C���^�������Ă��邽�߂�template���g�p
template<typename Arr>
void Stage::drawMap(Arr _mapData, const Vector2* _player) const
{
	//�}�b�v�`�������ۂɁC���@�̈ʒu�ˑ��ŕ`��ʒu�̍��W���ς��

	//���@���^�񒆂ɂ���Ƃ�
	int draw_y = MyData::CY - _player->y();
	int draw_x = MyData::CX - _player->x();

	//���[
	if (_player->y() + MyData::CY > MyData::MAP_HEIGHT)
	{
		draw_y = 480 - MyData::MAP_HEIGHT;
	}

	//��[
	else if (_player->y() < MyData::CY)
	{
		draw_y = 0;
	}

	//�E�[
	if (_player->x() + MyData::CX > MyData::MAP_WIDTH) 
	{
		draw_x = 640 - MyData::MAP_WIDTH;
	}

	//���[
	else if (_player->x() < MyData::CX)
	{
		draw_x = 0;
	}

	//�}�b�v�`��
	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = 0; x < mapData[0].size(); x++)
		{
			DrawGraph(x * 32 + draw_x, y * 32 + draw_y, mapChip[_mapData[y][x]], true);
		}
	}
}

void Stage::loadMap(int _stageID)
{
	string imgFile = "Data/Image/block";
	imgFile += std::to_string(_stageID);
	imgFile += ".png";

	int tmp = LoadDivGraph(imgFile.c_str(), 3, 3, 1, 32, 32, mapChip);
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




}
}
}


