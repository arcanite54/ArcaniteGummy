#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Stages\StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class PlayerChild;
class Character;

class GimmickChild
{
public:
	GimmickChild(Vector2);
	virtual ~GimmickChild() {};
	virtual void update() = 0;
	virtual void draw(const Vector2*) const = 0;
	virtual void draw_front(const Vector2*) const {}
	virtual void apply(Character*) = 0;

	//��ʏ�ŏd�Ȃ��Ă��邩�C�����蔻��p
	//�����̓}�b�v���Z�̒l
	//virtual bool isOverlap(int sub_x, int sub_y) const = 0;
	bool isOverlap(const Vector2*) const;

	//�Ώۂ��M�~�b�N�̌��ʔ͈͓��ɂ��邩
	//�����̓}�b�v���Z�̒l
	virtual bool onActiveArea(const Vector2*) const = 0;

	virtual StageChild::ChipType getChipType() const = 0;


	//��ʏ�ɕ\�����āA�X�V���邩�ǂ�����public�ϐ�
	bool isActive;

	//�����~�܂��Ă���Ƃ��ł��L�����ǂ���
	bool activeWhenStopping;

protected:
	Vector2 pos;
	int mImage;
	bool mDirection;
	
	void standardDraw(const Vector2* _camera) const;
	virtual void loadImage() = 0;
};




}
}
}