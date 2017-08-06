#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;
class Character;

class GimmickChild
{
public:
	virtual ~GimmickChild() {};
	virtual void update() = 0;
	virtual void draw(const Vector2*) const = 0;
	virtual void apply(Character*) = 0;

	//��ʏ�ŏd�Ȃ��Ă��邩�C�����蔻��p
	virtual bool isOverlap(const Vector2*) const = 0;

	//�Ώۂ��M�~�b�N�̌��ʔ͈͓��ɂ��邩
	virtual bool onActiveArea(const Vector2*) const = 0;

	virtual Stage::ChipType getChipType() const = 0;

	//��ʏ�ɕ\�����āA�X�V���邩�ǂ�����public�ϐ�
	bool isActive;
};




}
}
}