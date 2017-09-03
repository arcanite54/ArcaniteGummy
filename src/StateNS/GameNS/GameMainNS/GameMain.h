#pragma once

#include "GameMainChild.h"

//#include <string>
#include <vector>



namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{

class Stage;
class PlayerChild;
class System;
class EnemyController;

class GameMain : public Child
{
public:
	GameMain();
	~GameMain();
	void initialize();
	Child* update(GameParent*);
	void draw() const;

	enum HowStageMove
	{
		MOVE_NONE,

		MOVE_UP,
		MOVE_RIGHT,
		MOVE_LEFT,
		MOVE_DOWN,
	};



private:
	std::vector<Stage*> mStages;
	PlayerChild* mPlayer;
	System* mSystem;
	EnemyController* mEController;

	//�L������ς�����1�t���[�������\�������������Ȃ邩�炻�̑΍�
	bool changed;
	
	int nowStageNum;

	void processCollision(Stage* stage);
};




}
}
}