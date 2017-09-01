#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\DynamicObject.h"
#include "..\Stage.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;
class Character;

class DynamicGimmickChild : public DynamicObject
{
public:
	DynamicGimmickChild(int x, int y, int w, int h) : DynamicObject(x, y, w, h, 0, 0) {};
	virtual ~DynamicGimmickChild() {};
	virtual void update(PlayerChild*) = 0;
	virtual void draw(const Vector2* camera) const = 0;
	virtual void apply(Character*) = 0;
	virtual void hittedAction() override = 0;

	//��ʏ�ŏd�Ȃ��Ă��邩�C�����蔻��p
	//�����̓}�b�v���Z�̒l
	virtual bool isOverlap(int sub_x, int sub_y) const = 0;

	//�Ώۂ��M�~�b�N�̌��ʔ͈͓��ɂ��邩
	//�����̓}�b�v���Z�̒l
	virtual bool onActiveArea(const Vector2*) const = 0;

	virtual Stage::ChipType getChipType() const = 0;

	//��ʏ�ɕ\�����āA�X�V���邩�ǂ�����public�ϐ�
	bool isActive;

protected:
	int mImage;
	bool mDirection;

	virtual void loadImage() = 0;
};




}
}
}