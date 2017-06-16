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
	PlayerChild(float maxMoveSpeed , float maxJumpPower);
	virtual ~PlayerChild() { SAFE_DELETE(p); };
	virtual PlayerChild* update(const Stage*) = 0;
	virtual void draw() const = 0;
	const Vector2* getVector2() const { return p; }

protected:
	//�`�b�v�̃T�C�Y
	const int width = 32;
	const int height = 64;

	//�L�������ƂɈړ����x�ȂǂɈႢ���o���Ȃ炱���̕ϐ�����������
	const float maxMoveSpeed;
	const float maxJumpPower;

	//���̕ϐ�
	Vector2* p; //static�ł͂Ȃ�����L�����ύX�̂��т�delete���悤
	float moveSpeed;
	float jumpPower;
	bool now_jumping;

	//���ʂ̍s��
	virtual void attack() = 0;

	void standardMove(const Stage*);
	void move(const Stage*);

	void avoidSinking(const Stage*);
	int jump();
	int gravity();

	//�e���
	enum ActionState
	{
		ACT_NORMAL, //�ʏ���
		ACT_AIR, //�󒆂ɂ���
		ACT_ATTACK, //�U��
		ACT_SIT, //���Ⴊ��
	};

};






}
}
}