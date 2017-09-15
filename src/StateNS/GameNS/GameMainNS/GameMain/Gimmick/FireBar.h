#pragma once

#include "DynamicGimmickChild.h"



namespace StateNS {
namespace GameNS {


namespace GameMainNS {

class Child;

class FireBar : public DynamicGimmickChild
{
public:
	FireBar(int x, int y);
	~FireBar();
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
	int img_bar;
	int img_fire;
	float radian;

	const int r_1 = 48 * vectorRate;
	const int r_2 = 80 * vectorRate;

	int x_1, y_1;
	int x_2, y_2;

	void loadImage();
	void move();
};




}
}
}
