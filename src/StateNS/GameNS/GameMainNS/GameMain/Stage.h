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

private:
	int mBackImg;


	//�M�~�b�N�̔z��
	std::vector<GimmickChild*> mGimmicks;

	//mapChip(32x32pixcels)
	int mapChip[2];

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
		Chip(bool _canPass, bool _canRide) : canPass(_canPass), canRide(_canRide) {};
		~Chip() {};
		const bool canPass;//�ʂ邱�Ƃ��ł��邩
		const bool canRide;//��ɏ��邩�ǂ���
	};

	array<Chip, 2> chip
	{
		Chip(false, false),
		Chip(true, false),
	};


};




}
}
}