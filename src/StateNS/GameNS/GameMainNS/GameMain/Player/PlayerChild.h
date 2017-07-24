#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "..\Character.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Stage;

class PlayerChild : public Character
{
public:
	PlayerChild(float maxMoveSpeed , float maxJumpPower, int maxJumpCount, int maxHP);
	virtual ~PlayerChild() { SAFE_DELETE(p); };
	virtual PlayerChild* update(const Stage*) = 0;
	void draw() const;
	const Vector2* getVector2() const { return p; }
	const Vector2* getCamera() const { return camera; }

protected:
	//�L�������ƂɈړ����x�Ȃǂ̈Ⴂ���o���Ȃ炱���̕ϐ�����������
	const float maxMoveSpeed;
	const float maxJumpPower;
	const int maxJumpCount;

	//���̕ϐ�
	Vector2* p; //static�ł͂Ȃ�����L�����ύX�̂��т�delete���悤
	Vector2* camera;
	float moveSpeed;
	float jumpPower;
	int nowJumpCount;
	bool prePush;

	int img;

	//���ʂ̍s��
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //���@�ȊO��`�悷��
	virtual void loadImage() = 0;

	//Character�̊֐�
	//virtual void damagedAction() = 0;

	void standardMove(const Stage*);

private:
	void move(const Stage*);

	int jump();
	int gravity();

	int getVerticalDiffer(const Stage*, const int) const;
	int getHorizontalDiffer(const Stage*, const int) const;

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