#pragma once

#include "..\Character.h"
#include "..\Attack.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "..\..\GameMain.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Stage;
class Attack;

class PlayerChild : public Character
{
public:
	PlayerChild(int x, int y, float maxMoveSpeed ,float jump,int jumpCount, int maxHP);
	virtual ~PlayerChild();
	virtual PlayerChild* update(const Stage*) = 0;
	void draw() const;
	const Vector2* getCamera() const { return camera; }
	vector<Attack*> getAttacks() const { return attacks; }
	GameMain::HowStageMove getStageMove() const { return nextStageMove; };

	virtual int specialAction() = 0;

	const StopType getStopDynamicObject() const { return stopDynamics; }

protected:
	//�ϐ�
	float moveSpeed;
	Vector2* camera;
	int mImage[40];
	int animationTime;
	bool direction;

	int animeNum;
	int animeCount;
	bool canMove;
	bool prePushC;
	StopType stopDynamics;

	//���͊֌W
	bool in_right;
	bool in_left;
	bool in_up;
	bool in_down;
	bool in_jump;


	//�U����vector
	vector<Attack*> attacks;

	//���ʂ̍s��
	bool canChangeCharacter();
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //���@�ȊO��`�悷��
	virtual void loadImage() = 0;
	virtual bool onRigidBlock() const override { return false; }

	void standardAction(const Stage*);
	int animation();

	void actCheck();

	//�e���
	enum ActionState
	{
		ACT_NORMAL, //�ʏ���
		ACT_WALK,//�����Ă���
		ACT_RUN,//�����Ă���
		ACT_AIR, //�󒆂ɂ���
		ACT_ATTACK, //�U��
		ACT_SIT, //���Ⴊ��
		ACT_LADDER, //�͂���

	};
	ActionState actionState;


private:
	//�L�������ƂɈړ����x�Ȃǂ̈Ⴂ���o���Ȃ炱���̕ϐ�����������
	const float maxMoveSpeed;

	//���̕ϐ�
	bool prePush;
	GameMain::HowStageMove nextStageMove;

	//�O�t���[���ł̎��@�̈ʒu
	int post_x;
	int post_y;

	//�L�����N�^�[�؂芷���֘A
	bool isCharaChange;
	void changeCharacter();
	void draw_changingAnimation(int, int) const;

	//������ʒu�֌W
	bool onGround;
	bool onLadder;

	//���̑�
	void initialize();
	void processDamage();
	void hittedAction() override;
	void move(const Stage*);
	void updateCamera();
	bool isOnGround(const Stage*);
	bool isOnLadder(const Stage*) const;



};






}
}
}