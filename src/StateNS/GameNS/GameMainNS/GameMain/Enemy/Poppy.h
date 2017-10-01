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

	bool imgLoad = false;
	int mTime;

	//Character�̊֐�
	void hittedAction();

	//Enemychild�̊֐�
	void move(const StageChild*, int& dx, int& dy);
	int images[8];
	void loadImage()
	{
		if (!imgLoad)LoadDivGraph("Data/Image/Poppy.png", 8, 8, 1, 32, 32, images);
		for (int i = 0; i < 8; i++)mImage[i] = images[i];
		imgLoad = true;
	}


	void initialize();
};




}
}
}