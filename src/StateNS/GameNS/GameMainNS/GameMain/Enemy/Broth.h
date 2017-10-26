#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"
#include "..\Attack.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Broth : public EnemyChild
{
public:
	Broth(int x, int y);
	~Broth();

	void update(const StageChild* _stage,const Vector2* _camera);

private:
	int mTime;

	static bool imgLoad;
	static int images[8];
	void loadImage();
	void attack(const StageChild*);
	void draw_other(const Vector2*) const override;

	//Character�̊֐�
	void hittedAction();

	//Enemychild�̊֐�
	void move(const StageChild*, int& dx, int& dy);

	void initialize();


	int moveSpeed;
	bool preOnGround;

	//�U�����@�̓����N���X
	class Hammer : public Attack
	{
	public:
		Hammer(const Character*, int direction);
		virtual ~Hammer() override;
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int direction);
		void hittedAction();

	private:
		static bool imgLoad_hamm;
		static int image;

		int mTime;
		int dx;
		int dy;
		int sy;//�������W

		//const StageChild* stage;
	};

};

}
}
}