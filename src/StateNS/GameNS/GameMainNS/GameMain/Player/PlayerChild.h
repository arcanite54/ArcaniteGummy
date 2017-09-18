#pragma once

#include "..\Character.h"
#include "..\Attack.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"
#include "..\..\GameMain.h"
#include "..\Stages\StageChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class StageChild;
class Attack;

class PlayerChild : public Character
{
public:
	PlayerChild(int x, int y, float maxMoveSpeed ,float jump,int jumpCount, int maxHP);
	virtual ~PlayerChild();
	virtual PlayerChild* update(const StageChild*) = 0;
	void draw() const;
	const Vector2* getCamera() const { return camera; }
	vector<Attack*> getAttacks() const { return attacks; }
	StageChild::HowStageMove getStageMove() const { return nextStageMove; };

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

	void standardAction(const StageChild*);
	int animation();

	void actCheck();

	//�e���
	enum ActionState
	{
		ACT_NORMAL, //�ʏ���
		ACT_WALK,//�����Ă���
		ACT_RUN,//�����Ă���
		ACT_AIR, //�󒆂ɂ���
		ACT_RUNJUMP,//�����ăW�����v���Ă���
		ACT_ATTACK, //�U��
		ACT_SIT, //���Ⴊ��
		ACT_LADDER, //�͂���
		ACT_LADDER_STOP,//�͂����Ŏ~�܂��Ă���
	};
	ActionState actionState;


private:
	//�L�������ƂɈړ����x�Ȃǂ̈Ⴂ���o���Ȃ炱���̕ϐ�����������
	const float maxMoveSpeed;

	//���̕ϐ�
	bool prePush;
	StageChild::HowStageMove nextStageMove;

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
	void move(const StageChild*);
	void updateCamera();
	bool isOnGround(const StageChild*);
	bool isOnLadder(const StageChild*) const;



};






}
}
}