#pragma once

#include "..\..\..\..\..\Data.h"
#include "..\Character.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild : public Character
{
public:
	EnemyChild(int hp, int x, int y, int w, int h, float jump, int jumpCount);
	virtual ~EnemyChild();
	virtual void update(const StageChild*,const Vector2*) = 0;
	void draw(const Vector2* camera) const;
	virtual void draw_other(const Vector2* camera)const {}
	bool isAlive() const { return mIsAlive; }
	void setPlayer(const Vector2* _player) { this->player = _player; }
	vector<Attack*> getAttacks() const { return attacks; }

protected:
	int mImage;
	bool mDirection;
	const Vector2* player;

	//dx �� dy �Ɉړ��ʂ�����
	virtual void move(const StageChild*, int& dx, int& dy) = 0;
	virtual void loadImage() = 0;

	void standardAction(const StageChild* _stage);
	//�U����vector
	vector<Attack*> attacks;
private:
	bool mIsAlive;


	void initialize();
	void standardMove(const StageChild* stage);
	void checkIsAlive(const StageChild* stage);
	void processDamage();



};



}
}
}