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
	PlayerChild(int x, int y, float maxMoveSpeed , float maxJumpPower, int maxJumpCount, int maxHP);
	virtual ~PlayerChild();
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
	bool direction;

	//�U����vector
	vector<Attack*> attacks;

	//���ʂ̍s��
	bool canChangeCharacter();
	virtual void attack() = 0;
	virtual void draw_other() const = 0; //���@�ȊO��`�悷��
	virtual void loadImage() = 0;
	
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

	//���̑�
	void initialize();
	void processDamage();
	void hittedAction() override;
	void move(const Stage*);
	void updateCamera();
	bool isOnGround(const Stage*);

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