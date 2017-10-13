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

class Attack;

class PlayerChild : public Character
{
public:
	PlayerChild(int x, int y, float maxMoveSpeed ,float jump,int jumpCount, int maxHP);
	virtual ~PlayerChild();
	virtual PlayerChild* update(const StageChild*) = 0;
	virtual void draw() const;
	const Vector2* getCamera() const { return camera; }
	vector<Attack*> getAttacks() const { return attacks; }
	StageChild::HowStageMove getStageMove() const { return nextStageMove; }
	int getFloorCoordinate() override;
	virtual bool hasAdditionalGimmick() const { return false; }
	virtual DynamicGimmickChild* getAdditionalGimmick() const { assert(!"�����ɂ͂��Ȃ�"); return NULL; }


	const StopType getStopDynamicObject() const { return stopDynamics; }
	void moveCamera(int dx, int dy);
	void setCamera(const Vector2& _camera) { *(this->camera) = _camera; };

protected:
	//�ϐ�
	float moveSpeed;
	Vector2* camera;
	int mImage[32];
	bool direction;

	int animationTime;
	virtual StageChild::ChangeableCharacter getThisCharacter() { return StageChild::ChangeableCharacter::CHARA_NONE; };

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

	//������ʒu�֌W
	bool onGround;
	bool onLadder;
	
	//�U����vector
	vector<Attack*> attacks;


	//���ʂ̍s��
	bool canChangeCharacter();
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //���@�ȊO��`�悷��
	void draw_changingAnimation(int, int) const;
	virtual void loadImage() = 0;
	virtual bool onRigidBlock() const override { return false; }
	virtual void animation();

	void standardAction(const StageChild*);
	void actCheck();
	bool runCheck() 
	{
		return 
			actionState == ACT_ATTACK_SIDE_RUN ||
			actionState == ACT_ATTACK_UP_RUN ||
			actionState == ACT_RUN ||
			actionState == ACT_RUNJUMP;
	}
	int ladderTime;

	//�e���
	enum ActionState
	{
		ACT_NORMAL, //�ʏ���
		ACT_WALK,//�����Ă���
		ACT_RUN,//�����Ă���
		ACT_AIR, //�󒆂ɂ���
		ACT_RUNJUMP,//�����ăW�����v���Ă���
		ACT_ATTACK_SIDE, //���U��
		ACT_ATTACK_UP,//��U��
		ACT_ATTACK_SIDE_WALK, //�������U��
		ACT_ATTACK_UP_WALK,//������U��
		ACT_ATTACK_SIDE_RUN, //������U��
		ACT_ATTACK_UP_RUN,//�㑖��U��
		ACT_SIT, //���Ⴊ��
		ACT_LADDER, //�͂���
	};
	ActionState actionState;

	int getTopDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const override { return DynamicObject::getTopDiffer(_stage, dy, _moveLeft, true); }
	int getBottomDiffer(const StageChild* _stage, const int dy, bool _moveLeft) const override { return DynamicObject::getBottomDiffer(_stage, dy, _moveLeft, true); }
	int getHorizontalDiffer(const StageChild* _stage, const int dx, bool _moveUp) const override { return DynamicObject::getHorizontalDiffer(_stage, dx, _moveUp, true); }


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
	void changeCharacter(const StageChild*);

	//���̑�
	void initialize();
	void processDamage();
	void hittedAction() override;
	void move(const StageChild*);
	void updateCamera();
	bool isOnGround(const StageChild*);
	bool isOnLadder(const StageChild*) const;
	bool isOnLesal(const StageChild*);



};






}
}
}