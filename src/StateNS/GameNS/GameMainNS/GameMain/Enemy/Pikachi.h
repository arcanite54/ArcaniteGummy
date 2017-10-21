#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Pikachi : public EnemyChild
{
public:
	Pikachi(int x, int y);
	~Pikachi();

	void update(const StageChild* _stage,const Vector2* _camera);

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


	int moveSpeed;
	bool preOnGround;
	void attack(const StageChild*);
	void draw_other(const Vector2*)const override;

	//�U�����@�̓����N���X
	class Thunder : public Attack
	{
	public:
		Thunder(const Character*, const StageChild*, int x, int y, int speed);
		~Thunder();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int speed);
		void hittedAction();

	private:
		static bool imgLoad_thun;
		static int image;
		int mTime;
		int dx;
		int dy;
		const StageChild* stage;
	};

};


}
}
}