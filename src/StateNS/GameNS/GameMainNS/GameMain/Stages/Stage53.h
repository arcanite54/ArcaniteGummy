#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Kaguya;

class Stage53 : public StageChild
{
public:
	Stage53();
	~Stage53();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	
private:
	void initialize();

	Kaguya* kaguya;

	AllEnemies itoE(int num)
	{
		num = max(0, min(5, num));
		switch (num)
		{
			//�n��
		case(0):return ENE_YACH;
		case(1):return ENE_PIKA;
		case(2):return ENE_BROTH;
		case(3):return ENE_MARI;
		case(4):return ENE_BALL;
		case(5):return ENE_TERESA;
		}
		assert(!"Stage53::itoAE: �G�R�[�h���s���ł�");
		return ENE_NONE;
	}


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
		Chip(ChipType::TYPE_LADDER),
		Chip(ChipType::TYPE_LADDER_TOP),
		Chip(ChipType::TYPE_LESAL),
		Chip(ChipType::TYPE_LESAL),
		Chip(ChipType::TYPE_LESAL),
		Chip(ChipType::TYPE_LESAL),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
		Chip(ChipType::TYPE_RIGID),
	};


};




}
}
}