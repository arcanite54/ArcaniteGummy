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
	Stage(int mapID, int stageID);
	~Stage();
	void initialize();
	void update(PlayerChild*);
	void draw(const Vector2* player) const;
	void setStageSize(int _x, int _y)
	{
		stage_max_x = _x;
		stage_max_y = _y;
	}

	enum ChipType
	{
		TYPE_BACK				= 0b0000001, //���蔲������
		TYPE_RIGID				= 0b0000010, //���蔲�����Ȃ�
		TYPE_RIDE				= 0b0000100, //������͂��蔲���A�ォ��͂��蔲�����Ȃ�
		TYPE_DOWN_SLANT_RIGHT	= 0b0001000, //�E��֌������΂߃u���b�N, �オ�u���b�N�Ȃ�
		TYPE_DOWN_SLANT_LEFT	= 0b0010000, //����֌������΂߃u���b�N, �オ�u���b�N�Ȃ�
		TYPE_UP_SLANT_RIGHT		= 0b0100000, //�E��֌������΂߃u���b�N, �����u���b�N�Ȃ�
		TYPE_UP_SLANT_LEFT		= 0b1000000, //����֌������΂߃u���b�N, �����u���b�N�Ȃ�
	};
	ChipType getChipType(const Vector2&) const;
	ChipType getChipType(const RawVector2&) const;

	bool isRigid_down(ChipType _ct) const { return (_ct & 0b1100110) != 0; }//���ɂ��蔲�����Ȃ��u���b�N�C���ɂȂ�
	bool isRigid_up(ChipType _ct)   const { return (_ct & 0b0011010) != 0; }//��ɂ��蔲�����Ȃ��u���b�N�C�V��ɂȂ�
	bool isSlant(ChipType _ct)		const { return (_ct & 0b1111000) != 0; }//�΂߃u���b�N
	
private:
	int mBackImg;
	int stage_max_x;
	int stage_max_y;

	//�M�~�b�N�̔z��
	std::vector< GimmickChild* > mGimmicks;
	std::vector< DynamicGimmickChild* > mDynamicGimmicks;


	//�ȉ��}�b�v�֘A

	//mapChip�̉摜(32x32pixcels)
	int mapChip[7];

	//map(y:20 x:30 :: 320chips)
	//mapData[y][x]�ŃA�N�Z�X�ł���
	//mapData[~19][~29]
	std::array< std::array<int, 30>, 20> mapData;

	//�O�i�`��
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	void loadMap(int stageID, int mapID);
	//void loadGimmick();

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
	array<Chip, 7> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIDE),
		Chip(ChipType::TYPE_DOWN_SLANT_RIGHT),
		Chip(ChipType::TYPE_DOWN_SLANT_LEFT),
		Chip(ChipType::TYPE_UP_SLANT_RIGHT),
		Chip(ChipType::TYPE_UP_SLANT_LEFT)
	};


};




}
}
}