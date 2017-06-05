#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Stage;

class PlayerChild
{
public:
	virtual ~PlayerChild() {};
	virtual PlayerChild* update(const Stage*) = 0;
	virtual void draw() const = 0;
	const Vector2* getVector2() const { return p; }

protected:
	float speed;
	Vector2* p; //staticではないからキャラ変更のたびにdeleteしよう

	//共通の移動
	void standardMove(const Stage*);
};




}
}
}