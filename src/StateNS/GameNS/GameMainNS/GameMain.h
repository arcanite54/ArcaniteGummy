#pragma once

#include "GameMainChild.h"


namespace StateNS {
namespace GameNS {

class Play;
using GameParent = Play;

namespace GameMainNS{

class StageChild;
class PlayerChild;
class System;
class EnemyController;

enum StopType { TYPE_SAKUYA, TYPE_CHANGE, TYPE_NONE };

class GameMain : public Child
{
public:
	GameMain(int stageID,int width,int height);
	~GameMain();
	void initialize();
	Child* update(GameParent*);
	void draw() const;

private:
	StageChild* mStage;
	PlayerChild* mPlayer;
	System* mSystem;
	EnemyController* mEController;
	int stageID;
	int xNum, yNum;

	int nowStageNum;

	//時止めやキャラ変更の時に、動いているものを止める
	StopType stopDynamicObject;

	void updateDynamics(StageChild* stage);
	void processCollision(StageChild* stage);
};




}
}
}