#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS{

class Child;

class MovingFloor : public DynamicGimmickChild
{
public:
	MovingFloor(int start_x, int start_y, int term_x, int term_y, float movingSpeed);
	~MovingFloor();
	void initialize();
	void update(const Stage*);
	void draw(const Vector2* camera) const;
	Stage::ChipType getChipType() const { return Stage::ChipType::TYPE_RIGID; };

	void apply(Character*);
	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const;
	bool onActiveArea(const Vector2*) const;


private:
	//�J�n�_
	int start_x;
	int start_y;

	//�I���_
	int term_x;
	int term_y;

	float movingSpeed;
	
	int motion_dx;
	int motion_dy;

	void loadImage();
};



}
}
}