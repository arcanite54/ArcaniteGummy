#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Balloon : public EnemyChild
{
public:
	Balloon(int x, int y);
	~Balloon();

	void update(const Stage* _stage);

private:
	int images;
	bool imgLoad = false;
	int mTime;

	//Character�̊֐�
	void hittedAction();

	//Enemychild�̊֐�
	void move(const Stage*, int& dx, int& dy);
	void loadImage() { images = LoadGraph("Data/Image/balloon.png"); mImage = images; imgLoad = true; }


	void initialize();

};




}
}
}