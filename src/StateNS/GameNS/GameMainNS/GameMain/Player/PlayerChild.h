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
	PlayerChild();
	virtual ~PlayerChild() { SAFE_DELETE(p); };
	virtual PlayerChild* update(const Stage*) = 0;
	virtual void draw() const = 0;
	const Vector2* getVector2() const { return p; }

protected:
	//�L�������ƂɈړ����x�ȂǂɈႢ���o���Ȃ炱���̕ϐ�����������
	float moveSpeed;
	float maxJumpPower;

	//���̕ϐ�
	Vector2* p; //static�ł͂Ȃ�����L�����ύX�̂��т�delete���悤
	float jumpPower;


	//���ʂ̍s��
	void standardMove(const Stage*);
	int jump();
	int gravity();
};




}
}
}