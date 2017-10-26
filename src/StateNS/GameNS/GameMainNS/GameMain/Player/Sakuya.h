#pragma once

#include "PlayerChild.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Sakuya : public PlayerChild
{
public:
	Sakuya(int, int);
	Sakuya(int, int, int);
	~Sakuya();
	PlayerChild* update(const StageChild*);

private:
	int attackTime;
	const int attackInterval = 15;//�U���̊Ԋu

	bool isStoppingTime;
	int notStoppingTime;
	int stoppingTime;
	const int maxStoppingTime = 120;//�����~�߂Ă����鎞��(�t���[����)

	void initialize();
	virtual void attack() override {}//���z
	void attack(const StageChild*);
	int getAttackDx() const;
	void processAttack(const StageChild*);
	void processStopDynamics();

	void draw_other() const;
	virtual void loadImage() override;
	virtual void animation() override;
	virtual StageChild::ChangeableCharacter getThisCharacter() override
	{
		return StageChild::ChangeableCharacter::CHARA_SAKUYA;
	}

	//�U�����@�̓����N���X
	class Knife : public Attack
	{
	public:
		Knife(const PlayerChild*, const StageChild*, int x, int y, int dx);
		virtual ~Knife() override;
		void update();

		void setStatus(Vector2, int dx);
		void hittedAction();

	private:
		int dx;
		bool up;
		const StageChild* stage = 0;
	};
};




}
}
}