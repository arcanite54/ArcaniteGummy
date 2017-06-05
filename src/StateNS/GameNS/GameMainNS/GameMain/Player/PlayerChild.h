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
	Vector2* p; //static�ł͂Ȃ�����L�����ύX�̂��т�delete���悤

	//���ʂ̈ړ�
	void standardMove(const Stage*);
};




}
}
}