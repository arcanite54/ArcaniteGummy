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


Stage::Stage(int _stageID, int _stage_num,int _stage_max_x,int _stage_max_y)
{
	loadMap(_stageID, _stage_num);
	this->stage_num = _stage_num;

	stage_max_x = _stage_max_x;
	stage_max_y = _stage_max_y;

	initialize();
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
	stage_num_x = stage_num % (stage_max_x + 1);
	stage_num_y = stage_num / (stage_max_x + 1);

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
	mDynamicGimmicks.push_back(new FireBar(300, 1500));
	mSwitchWithBlocks.push_back(new SwitchWithBlock(200, 1472));
	
	mSwitchWithBlocks[0]->push_block(new Block(208, 1296, 1.0));
	mSwitchWithBlocks[0]->push_block(new Block(256, 1312, 2.0));

	//loadGimmick()
	//�Ƃ������֐��ŊO���̃e�L�X�g�f�[�^����ǂݍ���
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

	updateDynamicGimmick(mDynamicGimmicks, _player);
	updateDynamicGimmick(mSwitchWithBlocks, _player);

	//�X�C�b�`�̃u���b�N��update
	for (auto& s_b : mSwitchWithBlocks)
		updateDynamicGimmick(s_b->getBlocks(), _player);

	/*
	for (auto& d_gimmick : mDynamicGimmicks)
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

	for (auto& s_b : mSwitchWithBlocks)
	{
		if (s_b->isActive)s_b->update(this);

		if (s_b->onActiveArea(_player->getVector2()))
			s_b->apply(_player);

		if (s_b->rideOnGimmick(_player->getVector2()))
			_player->moveCharacter(s_b->getDX(), s_b->getDY());
	}
	*/
}

void Stage::draw(const Vector2* _camera) const
{
	DrawGraph(0, 0, mBackImg, true);
	drawMap(mapData, _camera);

	//�X�C�b�`�֘A�̕`��
	for (const auto& s_b : mSwitchWithBlocks)
	{
		if (s_b->isActive)s_b->draw(_camera);
	}

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

	//�X�C�b�`�̃u���b�N��update
	for (auto& s_b : mSwitchWithBlocks)
	{
		for (auto& b : s_b->getBlocks())
		{
			b->draw(_camera);
		}
	}

}

int Stage::getTopPosition(const Vector2* _pos, const int& _dy) const
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

int Stage::getBottomPosition(const Vector2* _pos, const int& _dy) const
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


Stage::ChipType Stage::getChipType(const Vector2& _other, bool isPlayer) const
{
	int sub_x = _other.raw_x / CHIP_WIDTH_RATE();
	if (_other.raw_x < 0)--sub_x;

	int sub_y = _other.raw_y / CHIP_HEIGHT_RATE();
	if (_other.raw_y < 0)--sub_y;

	if (Input_S() && isPlayer)
	{
		int gomi = 0;
	}

	//Stage�͈̔͊O(�E�̒[)�Ȃ�
	if (MyData::MAP_WIDTH_NUM <= sub_x)
	{
		if (stage_num_x == stage_max_x)
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	//Stage�͈̔͊O(���̒[)�Ȃ�
	if (sub_x < 0)
	{
		if (stage_num_x == 0)
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}

	//Stage�͈̔͊O(��̒[)�Ȃ�
	if (sub_y < 0)
	{
		if (stage_num_y == 0)
			return ChipType::TYPE_RIGID;

		//else
		return ChipType::TYPE_BACK;
	}
	//Stage�͈̔͊O(���̒[)�Ȃ�
	if (MyData::MAP_HEIGHT_NUM <= sub_y)
	{
		if (stage_num_y == stage_max_y)
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
Stage::ChipType Stage::getChipType(const Vector2& _other) const
{
	return getChipType(_other, true);
}

Stage::ChipType Stage::getChipType(const RawVector2& _other, bool _isPlayer) const
{
	return getChipType(Vector2(_other.pos_x, _other.pos_y), _isPlayer);
}

bool Stage::isClear() const
{
	return !clearFlag->isActive;
}

//========================================================================
// ����private�֐�
//========================================================================
template<typename D_Gmk>
void Stage::updateDynamicGimmick(D_Gmk d_gmk, PlayerChild* _player)
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



void Stage::loadMap(int _stageID, int _mapID)
{
	//string imgFile = "Data/Image/block";
	//imgFile += std::to_string(_stageID);
	//imgFile += ".png";
	string imgFile = "Data/Image/block0.png";

	//256*480
	int tmp = LoadDivGraph(imgFile.c_str(), 120, 8, 15, 32, 32, mapChip);
	assert(tmp != -1 && "�}�b�v�`�b�v�ǂݍ��݃G���[");

	string textFile = "Data/Text/stage";
	textFile += std::to_string(_stageID);
	textFile += "/stage";
	textFile += std::to_string(_mapID);

	string textFile2 = textFile + "a";
	textFile += ".txt";
	textFile2 += ".txt";


	std::ifstream fin(textFile);
	std::ifstream fin2("Data/Text/stage0a.txt");

	assert(fin && "�}�b�v�f�[�^�ǂݍ��݃G���[");
	assert(fin2 && "�M�~�b�N�ǂݍ��݃G���[");

	for (auto& mapY : mapData)
	{
		for (auto& mapX : mapY)
		{
			fin >> mapX;
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


void Stage::loadGimmick(int _x, int _y, int _n)
{

	//Dynamic����Ȃ����̂�y���W��+16
	switch (_n) {
	case 56:mDynamicGimmicks.push_back(new Block(_x * 32, _y * 32, 3.0)); break;//�͂�
	case 57:mGimmicks.push_back(new Spring(Vector2(_x*32 + 16, _y*32+16))); break;//�΂�
	case 58:mGimmicks.push_back(new BeltConveyor(2.0, Vector2(_x*32 + 16,_y*32+16))); break;//�x���g�R���x�A
	case 59:mDynamicGimmicks.push_back(new Dossunn(_x*32, _y*32, 1.0)); break;//�h�b�X��
	//case 60:mDynamicGimmicks.push_back(new UFO(_x * 32, _y * 32, 1.0)); break;//�ʂ���UFO
	}

}





}
}
}


