#pragma once
#include "..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class GimmickChild;

class Stage
{
public:
	Stage(int stageID);
	~Stage();
	void initialize();
	void update();
	void draw(const Vector2* player) const;

	enum ChipType
	{
		TYPE_RIGID				= 0b0000001, //���蔲�����Ȃ�
		TYPE_RIGID_SLANT_RIGHT	= 0b0000010, //�E��֌������΂߃u���b�N, �����炷�蔲�����Ȃ�
		TYPE_RIGID_SLANT_LEFT	= 0b0000100, //����֌������΂߃u���b�N, �����炷�蔲�����Ȃ�
		TYPE_BACK				= 0b0001000, //���蔲������
		TYPE_RIDE				= 0b0010000, //������͂��蔲���A�ォ��͂��蔲�����Ȃ�
		TYPE_SLANT_RIGHT		= 0b0100000, //�E��֌������΂߃u���b�N, �����炷�蔲������
		TYPE_SLANT_LEFT			= 0b1000000, //����֌������΂߃u���b�N, �����炷�蔲������
	};
	ChipType getChipType(const Vector2) const;
	bool isRigid(ChipType _ct) const { return (_ct & 0b0000111) != 0; }
	bool isSlant(ChipType _ct) const { return (_ct & 0b1100110) != 0; }
	bool  isRide(ChipType _ct) const { return (_ct & 0b1110111) != 0; }

private:
	int mBackImg;

	//�M�~�b�N�̔z��
	std::vector< GimmickChild* > mGimmicks;

	//mapChip�̉摜(32x32pixcels)
	int mapChip[4];

	//map(y:15 x:20 :: 320chips)
	//mapData[y][x]�ŃA�N�Z�X�ł���
	//mapData[~14][~19]
	std::array< std::array<int, 30>, 30> mapData;

	//�}�b�v�`��

	//�O�i�`��
	template<typename Arr>
	void drawMap(Arr, const Vector2*) const;

	void loadMap(int stageID);

	class Chip
	{
	public:
		Chip(ChipType _chipType) : chipType(_chipType) {};
		~Chip() {};
		ChipType getChipType() const { return chipType; }
		void setChipType(ChipType _chipType) { chipType = _chipType; }
	private:
		ChipType chipType;
	};

	//�}�b�v�`�b�v
	array<Chip, 4> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_SLANT_RIGHT),
		Chip(ChipType::TYPE_SLANT_LEFT),
	};


};




}
}
}