#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Poppy : public EnemyChild
{
public:
	Poppy(int x, int y);
	~Poppy();

	void update(const StageChild* _stage, const Vector2* _camera);


private:
	int mTime;

	static bool imgLoad;
	static int images[8];
	void loadImage();

	//Character�̊֐�
	void hittedAction();

	//Enemychild�̊֐�
	void move(const StageChild*, int& dx, int& dy);


	void initialize();
};


}
}
}