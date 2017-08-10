#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "..\Character.h"
#include "..\..\GameMain.h"

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
	const Vector2* getCamera() const { return camera; }
	GameMain::HowStageMove getStageMove() const { return nextStageMove; };

protected:
	//�ϐ�
	float moveSpeed;
	Vector2* camera;
	int mImage;
	int animationTime;

	//���ʂ̍s��
	bool canChangeCharacter();
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //���@�ȊO��`�悷��
	virtual void loadImage() = 0;

	//Character�̊֐�
	//virtual void damagedAction() = 0;

	void standardAction(const Stage*);

private:
	//�L�������ƂɈړ����x�Ȃǂ̈Ⴂ���o���Ȃ炱���̕ϐ�����������
	const float maxMoveSpeed;
	const float maxJumpPower;
	const int maxJumpCount;

	//���̕ϐ�
	float jumpPower;
	int nowJumpCount;
	bool prePush;
	GameMain::HowStageMove nextStageMove;

	//�O�t���[���ł̎��@�̈ʒu
	int post_x;
	int post_y;

	//�L�����N�^�[�؂芷���֘A
	bool isCharaChange;
	void changeCharacter();
	void draw_changingAnimation(int, int) const;

	void initialize();
	void move(const Stage*);
	bool isOnGround(const Stage*);

	int getVerticalDiffer(const Stage*, const int) const;
	int getHorizontalDiffer(const Stage*, const int) const;

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