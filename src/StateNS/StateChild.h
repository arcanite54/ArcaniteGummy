#pragma once

class Parent;
using GrandParent = Parent ;

namespace StateNS{


class Child {
public:
	virtual ~Child() {};
	//�Ԃ�l�͎��̃V�[�P���X
	virtual Child* update(const GrandParent*) = 0;
	virtual void draw() const = 0;
};



}