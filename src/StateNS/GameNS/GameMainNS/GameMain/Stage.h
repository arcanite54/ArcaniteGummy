#pragma once
#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class PlayerChild;
class GimmickChild;
class DynamicGimmickChild;

class Stage
{
public:
	Stage(int mapID, int stageID,int stage_max_x,int stage_max_y);
	~Stage();
	void initialize();
	void update(PlayerChild*);
	void draw(const Vector2* player) const;

	enum ChipType
	{
		TYPE_BACK				= 0b000000001, //���蔲������
		TYPE_RIGID				= 0b000000010, //���蔲�����Ȃ�
		TYPE_RIDE				= 0b000000100, //������͂��蔲���A�ォ��͂��蔲�����Ȃ�
		TYPE_DOWN_SLANT_RIGHT	= 0b000001000, //�E��֌������΂߃u���b�N, �オ�u���b�N�Ȃ�
		TYPE_DOWN_SLANT_LEFT	= 0b000010000, //����֌������΂߃u���b�N, �オ�u���b�N�Ȃ�
		TYPE_UP_SLANT_RIGHT		= 0b000100000, //�E��֌������΂߃u���b�N, �����u���b�N�Ȃ�
		TYPE_UP_SLANT_LEFT		= 0b001000000, //����֌������΂߃u���b�N, �����u���b�N�Ȃ�
		TYPE_LADDER				= 0b010000000, //�͂���
		TYPE_LADDER_TOP			= 0b100000000, //�͂����̏�
	};

	bool isRigid_down(ChipType _ct) const { return (_ct & 0b101100110) != 0; }//���ɂ��蔲�����Ȃ��u���b�N�C���ɂȂ�
	bool isRigid_up(ChipType _ct)   const { return (_ct & 0b000011010) != 0; }//��ɂ��蔲�����Ȃ��u���b�N�C�V��ɂȂ�
	bool isSlant(ChipType _ct)		const { return (_ct & 0b001111000) != 0; }//�΂߃u���b�N

	ChipType getChipType(const Vector2&, bool isPlayer) const;
	ChipType getChipType(const Vector2&) const;
	ChipType getChipType(const RawVector2&, bool isPlayer) const;

	int getTopPosition(const Vector2*, const int& dy) const;//�����͍�����n�_�̍��W��vectorRrate������������
	int getBottomPosition(const Vector2*, const int& dy) const;//�����͍�����n�_�̍��W��vectorRrate������������
	std::vector< DynamicGimmickChild* > getDynamicGimmicks() { return mDynamicGimmicks; }

	bool isClear() const;

private:
	int mBackImg;
	int stage_num;
	int stage_max_x;
	int stage_max_y;
	int stage_num_x;
	int stage_num_y;

	//�M�~�b�N�̔z��
	std::vector< GimmickChild* > mGimmicks;
	std::vector< DynamicGimmickChild* > mDynamicGimmicks;

	GimmickChild* clearFlag;


	//�ȉ��}�b�v�֘A

	//mapChip�̉摜(32x32pixcels)
	int mapChip[120];

	//map(y:20 x:30 :: 320chips)
	//mapData[y][x]�ŃA�N�Z�X�ł���
	//mapData[~19][~29]
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> mapData;
	std::array< std::array<int, MAP_WIDTH_NUM>, MAP_HEIGHT_NUM> gimmickData;

	//�O�i�`��
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	void loadMap(int stageID, int mapID);
	void loadGimmick(int x,int y);

	class Chip
	{
	public:
		Chip(ChipType _chipType) : mChipType(_chipType) {};
		~Chip() {};
		ChipType getChipType() const { return mChipType; }
		void setChipType(ChipType _chipType) { mChipType = _chipType; }
	private:
		ChipType mChipType;
	};

	//�}�b�v�`�b�v
	array<Chip, 20> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIDE),
		Chip(ChipType::TYPE_DOWN_SLANT_RIGHT),
		Chip(ChipType::TYPE_DOWN_SLANT_LEFT),
		Chip(ChipType::TYPE_UP_SLANT_RIGHT),
		Chip(ChipType::TYPE_UP_SLANT_LEFT),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_LADDER),
		Chip(ChipType::TYPE_LADDER_TOP),

	};


};




}
}
}