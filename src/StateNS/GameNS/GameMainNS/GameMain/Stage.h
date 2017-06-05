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
	bool canPass(const Vector2) const;

	enum ChipType
	{
		TYPE_BACK,				//���蔲������
		TYPE_RIGID,				//���蔲�����Ȃ�
		TYPE_RIDE,				//������͂��蔲���A�ォ��͂��蔲�����Ȃ�
		TYPE_SLANT_RIGHT,		//�E��֌������΂߃u���b�N, �����炷�蔲������
		TYPE_SLANT_LEFT,		//����֌������΂߃u���b�N, �����炷�蔲������
	};

private:
	int mBackImg;


	//�M�~�b�N�̔z��
	std::vector<GimmickChild*> mGimmicks;

	//mapChip�̉摜(32x32pixcels)
	int mapChip[3];

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
	array<Chip, 3> chip
	{
		Chip(ChipType::TYPE_BACK),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_SLANT_RIGHT),
	};


};




}
}
}