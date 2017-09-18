<<<<<<< HEAD
#pragma once

#include "DynamicGimmickChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Child;

class Torch : public DynamicGimmickChild
{
public:
	Torch(int x, int y);
	~Torch();
	void initialize();
	void update(const StageChild*);
	void draw(const Vector2*) const;
	void apply(Character*);

	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const override;

	bool onActiveArea(const Vector2*) const;
	void checkOnActiveArea(const Vector2* player) { this->onActiveArea(player); }
	StageChild::ChipType getChipType() const;

private:
	bool isBurned;
	int mTime;

	void loadImage();
};




}
}
}
=======
#pragma once

#include "DynamicGimmickChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Child;

class Torch : public DynamicGimmickChild
{
public:
	Torch(int x, int y);
	~Torch();
	void initialize();
	void update(const StageChild*);
	void draw(const Vector2*) const;
	void apply(Character*);

	void hittedAction() override;
	void burnedAction() override;
	bool isOverlap(const Vector2*) const override;

	bool onActiveArea(const Vector2*) const;
	void checkOnActiveArea(const Vector2* player) { this->onActiveArea(player); }
	StageChild::ChipType getChipType() const;

private:
	bool isBurned;
	int mTime;

	void loadImage();
};




}
}
}
>>>>>>> master
