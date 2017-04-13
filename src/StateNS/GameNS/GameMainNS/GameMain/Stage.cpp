#include "Stage.h"
#include "Gimmick\GimmickChild.h"

#include "..\..\..\..\Data.h"
#include "..\..\..\..\KeyInput.h"

#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Stage::Stage(){
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
	assert(mBackImg != -1 && "mBackImg�ǂݍ��݃G���[");
}

void Stage::update()
{


}

void Stage::draw(const Vector2* _player) const
{
	//DrawFormatString(0, 40, MyData::WHITE, "Stage");
	DrawGraph(0, 0, mBackImg, true);

	for (auto gimmick : mGimmicks)
	{
		gimmick->draw();
	}

}






//========================================================================
// ����private�֐�
//========================================================================
void Stage::drawBack(const Vector2* _player) const
{
	//�摜�̕`��ʒu
	//DrawGraph�֐����g������C�摜�̍���ɍ��킹��
	int draw_x = (_player->x < 640 * MyData::vectorRate) ? 0 : -640;

	//���@���^�񒆂ɂ���Ƃ�
	int draw_y = 240 - _player->y / MyData::vectorRate;

	//���[
	if (_player->y / MyData::vectorRate > MyData::MAP_HEIGHT - MyData::CY)draw_y = -480;

	//��[
	else if (_player->y / MyData::vectorRate < MyData::CY)draw_y = 0;


	DrawGraph(draw_x, draw_y, mBackImg, true);
}

//�}�b�v�`�b�v���ς���Ă��Ή��\
//�������Ƀ}�b�v�`�b�v�ւ̃|�C���^�������Ă��邽�߂�template���g�p
template<typename Arr>
void Stage::drawMap(Arr _mapData, const Vector2* _player) const
{
	//�}�b�v�`�������ۂɁC���@�̈ʒu�ˑ��ŕ`��ʒu��y���W���ς��
	//���@���^�񒆂ɂ���Ƃ�
	int draw_y = _player->y / MyData::vectorRate - MyData::CY;

	//���[
	if (_player->y / MyData::vectorRate > MyData::MAP_HEIGHT - MyData::CY)draw_y = MyData::MAP_HEIGHT - 480;

	//��[
	else if (_player->y / MyData::vectorRate < MyData::CY)draw_y = 0;


	//�E���ƍ����̃}�b�v�ɂ���Ƃ���for�������ϐ���x�͈̔͂��ς��
	int x_sub = (_player->x / MyData::vectorRate < MyData::MAP_WIDTH / 2) ? 0 : mapData[0].size() / 2;

	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = x_sub; x < x_sub + mapData[0].size() / 2; x++)
		{
			DrawGraph((x % (mapData[0].size() / 2)) * 32, y * 32 - draw_y, mapChip[_mapData[y][x]], true);
		}
	}
}


}
}
}