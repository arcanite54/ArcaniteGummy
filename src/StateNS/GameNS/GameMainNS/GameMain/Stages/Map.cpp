#include "Map.h"

#include "..\Player\PlayerChild.h"
#include "..\Gimmick\GimmickChild.h"
#include "..\Gimmick\DynamicGimmickChild.h"
#include "..\Gimmick\AllGimmicks.h"

#include "..\..\..\..\..\KeyInput.h"
#include <fstream>

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


Map::Map(int _stageID, int _mapID, MapPos _mapPos)
{
	loadMap(_stageID, _mapID);
	this->mapPos = _mapPos;

	initialize();
}

Map::~Map()
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

void Map::initialize()
{
	//TODO�v����

	//mGimmicks��0�Ԗڂ�clearFlag
	this->clearFlag = new ClearFlag(Vector2(400, 1552));
	mGimmicks.push_back(clearFlag);

	for (unsigned y = 0; y < gimmickData.size(); y++)
	{
		for (unsigned x = 0; x < gimmickData[0].size(); x++)
		{
			loadGimmick(x, y,gimmickData[y][x]);
			//DrawGraph(x * 32 - draw_x, y * 32 - draw_y, mapChip[_mapData[y][x]], true);
		}
	}

	// for Debug
	//mDynamicGimmicks.push_back(new MovingFloor(300, 1400, 360, 1200, 3.0));
	//mDynamicGimmicks.push_back(new FireBar(304, 1488,true));
	//mDynamicGimmicks.push_back(new Block(656, 1488, 1.0));
	//mDynamicGimmicks.push_back(new Block(688, 1488, 1.0, false));
	//mSwitchWithBlocks.push_back(new SwitchWithBlock(208, 1488));
	
	//mSwitchWithBlocks[0]->push_block(new Block(208, 1296, 1.0));
	//mSwitchWithBlocks[0]->push_block(new Block(256, 1312, 2.0));

}

int Map::getTopPosition(const Vector2* _pos, const int& _dy) const
{
	//����������W�ɑ���Object����������A����Object�̏��y���W��Ԃ�

	int ret = fixToVectorHeight(_pos->pos_y() + _dy);

	//*
	//���������[�N����
	Vector2* tmp = new Vector2(_pos->pos_x(), _pos->pos_y() + _dy, true);

	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		//������RIGID��d_gimmick������Ȃ�
		if (d_gimmick->isActive)
		{
			if (d_gimmick->isOverlap(tmp) && isRigid_down(d_gimmick->getChipType()))
			{
				ret = d_gimmick->getTopPosition();
			}
		}
	}

	//���������[�N����
	SAFE_DELETE(tmp);
	//*/


	return ret;
}

int Map::getBottomPosition(const Vector2* _pos, const int& _dy) const
{
	//����������W�ɑ���Object����������A����Object�̒��y���W��Ԃ�

	int ret = fixToVectorHeight(_pos->pos_y() + _dy) +CHIP_HEIGHT_RATE();

	//*
	//���������[�N����
	Vector2* tmp = new Vector2(_pos->pos_x(), _pos->pos_y() + _dy, true);

	for (const auto& d_gimmick : mDynamicGimmicks)
	{
		//�����RIGID��d_gimmick������Ȃ�
		if (d_gimmick->isActive)
		{
			if (d_gimmick->isOverlap(tmp) && isRigid_up(d_gimmick->getChipType()))
			{
				ret = d_gimmick->getBottomPosition();
			}
		}
	}

	//���������[�N����
	SAFE_DELETE(tmp);
	//*/


	return ret;
}


ChipType Map::getChipType(const Vector2& _other, bool isPlayer) const
{
	int sub_x = _other.raw_x / CHIP_WIDTH_RATE();
	if (_other.raw_x < 0)--sub_x;

	int sub_y = _other.raw_y / CHIP_HEIGHT_RATE();
	if (_other.raw_y < 0)--sub_y;

	//Map�͈̔͊O(�E�̒[)�Ȃ�
	if (MyData::MAP_WIDTH_NUM <= sub_x)
	{
		if (isRight(mapPos))
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	//Map�͈̔͊O(���̒[)�Ȃ�
	if (sub_x < 0)
	{
		if (isLeft(mapPos))
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	//Map�͈̔͊O(��̒[)�Ȃ�
	if (sub_y < 0)
	{
		if (isUp(mapPos))
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}
	//Map�͈̔͊O(���̒[)�Ȃ�
	if (MyData::MAP_HEIGHT_NUM <= sub_y)
	{
		if (isDown(mapPos))
			return ChipType::TYPE_RIGID;

		//else
		//return ChipType::TYPE_LESAL;
		return ChipType::TYPE_BACK;
	}

	
	ChipType ret = ChipType::TYPE_BACK;
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

	for (const auto& s_b : mSwitchWithBlocks)
	{
		for (auto& b : s_b->getBlocks())
		{
			if (b->isOverlap(&_other))
			{
				ret = b->getChipType();
			}
		}
	}
	
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
ChipType Map::getChipType(const Vector2& _other) const
{
	return getChipType(_other, true);
}

ChipType Map::getChipType(const RawVector2& _other, bool _isPlayer) const
{
	return getChipType(Vector2(_other.pos_x, _other.pos_y), _isPlayer);
}

bool Map::isClear() const
{
	return !clearFlag->isActive;
}

//�}�b�v�`�b�v���ς���Ă��Ή��\
//�������Ƀ}�b�v�`�b�v�ւ̃|�C���^�������Ă��邽�߂�template���g�p
//template<typename Arr>
void Map::drawMap(const Vector2* _camera) const
{
	//�}�b�v�`�������ۂɁC�J�����̈ʒu�ˑ��ŕ`��ʒu�̍��W���ς��
	int draw_x = _camera->x() - MyData::CX;
	int draw_y = _camera->y() - MyData::CY;


	//�}�b�v�`��
	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = 0; x < mapData[0].size(); x++)
		{
			DrawGraph(x * 32 - draw_x, y * 32 - draw_y, mapChip[mapData[y][x]], true);
		}
	}
}


//========================================================================
// ����private�֐�
//========================================================================
template<typename D_Gmk>
void Map::updateDynamicGimmick(D_Gmk d_gmk, PlayerChild* _player)
{
	for (auto& d_gimmick : d_gmk)
	{
		if (d_gimmick->isActive)
		{
			d_gimmick->update(this);

			if (d_gimmick->onActiveArea(_player->getVector2()))
				d_gimmick->apply(_player);

			if (d_gimmick->rideOnGimmick(_player->getVector2()))
				_player->moveCharacter(d_gimmick->getDX(), d_gimmick->getDY());
		}
	}
}



void Map::loadMap(int _stageID, int _mapID)
{
	//string imgFile = "Data/Image/block";
	//imgFile += std::to_string(_stageID);
	//imgFile += ".png";
	string imgFile = "Data/Image/block0.png";

	//256*480
	int tmp = LoadDivGraph(imgFile.c_str(), 256, 8, 15, 32, 32, mapChip);
	assert(tmp != -1 && "�}�b�v�`�b�v�ǂݍ��݃G���[");

	string textFile = "Data/Text/stage";
	textFile += std::to_string(_stageID);
	textFile += "/stage";
	textFile += std::to_string(_mapID);

	string textFile2 = textFile + "a";
	textFile += ".txt";
	textFile2 += ".txt";


	std::ifstream fin(textFile);
	std::ifstream fin2(textFile);

	assert(fin && "�}�b�v�f�[�^�ǂݍ��݃G���[");
	assert(fin2 && "�M�~�b�N�ǂݍ��݃G���[");

	for (auto& mapY : mapData)
	{
		for (auto& mapX : mapY)
		{
			fin >> mapX;
		}
	}

	//�M�~�b�N��G�z�u�̌��͔w�i�Ƃ���B
	for (unsigned y = 0; y < mapData.size(); y++)
	{
		for (unsigned x = 0; x < mapData[0].size(); x++)
		{
			if (mapData[y][x] > 111)mapData[y][x] = 0;
		}
	}


	for (auto& gimmickY : gimmickData)
	{
		for (auto& gimmickX : gimmickY)
		{
			fin2 >> gimmickX;
		}
	}

}

void Map::loadGimmick(int _x, int _y, int _n)
{
	//TODO �ύX�r��

	//Dynamic����Ȃ����̂�y���W��+16
	switch (_n) {
		//�΂�
	case 113:mGimmicks.push_back(new Spring(Vector2(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2))); break;
		//���x���g�R���x�A
	case 114:mGimmicks.push_back(new BeltConveyor(-2.0, Vector2(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2))); break;
		//�E�x���g�R���x�A
	case 115:mGimmicks.push_back(new BeltConveyor(2.0, Vector2(_x * CHIP_WIDTH + CHIP_WIDTH / 2, _y * CHIP_HEIGHT + CHIP_HEIGHT / 2))); break;
		//�R����u���b�N�H���Ԃ�Ⴄ
	case 116:mDynamicGimmicks.push_back(new Block(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, 1.0)); break;
		//����u���b�N
	case 117:mDynamicGimmicks.push_back(new Block(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, 1.0)); break;
		//�傫���h�b�X��
	case 118:mDynamicGimmicks.push_back(new Dossunn(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, 3.0)); break;
		//�������h�b�X��
	case 119:mDynamicGimmicks.push_back(new Dossunn(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, 1.0)); break;
		//������g�Q
	case 120:break;
		//�������g�Q
	case 121:break;
		//�E�����g�Q
	case 122:break;
		//�������g�Q
	case 123:break;
		//�����v���t�@�C�A�o�[
	case 124:mDynamicGimmicks.push_back(new FireBar(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, false)); break;
		//���v���t�@�C�A�o�[
	case 125:mDynamicGimmicks.push_back(new FireBar(_x * CHIP_WIDTH, _y * CHIP_HEIGHT, true)); break;
		//���Ɨ����鏰
	case 126:break;
		//���Əオ�鏰
	case 127:break;
		//�������F�㉺�F��
	case 128:break;
		//�������F�㉺�F��
	case 129:break;
		//�������F���E�F��
	case 130:break;
		//�������F���E�F��
	case 131:break;
		//�������F�E��΂߁F��
	case 132:break;
		//�������F�E��΂߁F��
	case 133:break;
		//�������F�E���΂߁F��
	case 134:break;
		//�������F�E���΂߁F��
	case 135:break;
		//�������F�~�F��
	case 136:break;
		//�������F�~�F��
	case 137:break;
		//�������F�A�X�e���C�h�F��
	case 138:break;
		//�������F�A�X�e���C�h�F��
	case 139:break;
		//�������F��ɓʂȕ������F��
	case 140:break;
		//�������F��ɓʂȕ������F��
	case 141:break;
		//�������F���ɓʂȕ������F��
	case 142:break;
		//�������F���ɓʂȕ������F��
	case 143:break;
		//����
	case 144:break;

	

	}

}





}
}
}

