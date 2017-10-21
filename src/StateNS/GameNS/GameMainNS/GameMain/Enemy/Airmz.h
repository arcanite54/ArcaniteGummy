#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Airmz : public EnemyChild
{
public:
	Airmz(int x, int y);
	~Airmz();

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


	void attack(const StageChild*);
	void draw_other(const Vector2*)const override;

	void initialize();


	//�U�����@�̓����N���X
	class Bomb : public Attack
	{
	public:
		Bomb(const Character*, const StageChild*, int x, int y, int speed);
		~Bomb();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int speed);
		void hittedAction();

	private:
		static bool imgLoad;
		static int image;

		int mTime;
		int dx;
		int dy;
		int sy;//�������W

		const StageChild* stage;
	};

};




}
}
}