#pragma once

#include "..\..\..\..\..\Data.h"


namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class EnemyChild;
class Stage;
class PlayerChild;

class EnemyController
{
public:
	EnemyController();
	~EnemyController();

	void update(const Stage*);
	void draw(const Vector2*) const;

	vector<EnemyChild*>& getEnemies() { return enemies; }

	//���@�ƓG�̍U���Ƃ̓����蔻��
	void processCollision(PlayerChild*);

	void createEnemy();
	void deleteEnemy(int ID);
	void setPlayerPos(const Vector2* player);

private:
	vector<EnemyChild*> enemies;


};





}
}
}