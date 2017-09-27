#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


class Reisen : public EnemyChild
{
public:
	Reisen(int x, int y);
	~Reisen();

	void update(const StageChild* _stage, const Vector2* _camera);


private:
	int images;
	bool imgLoad = false;
	int mTime;

	bool nowMoving;

	//�W�����v�ړ��̈ړ���
	const int move_x = 320;
	const int move_y = 200;

	//Character�̊֐�
	void hittedAction();

	//Enemychild�̊֐�
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera)const override;

	//TODO �摜�����ւ�
	void loadImage() { images = LoadGraph("Data/Image/balloon.png"); mImage = images; imgLoad = true; }
	void attack(const StageChild*);

	void initialize();

	class Shot : public Attack
	{
	public:
		Shot(const EnemyChild*, const StageChild*, const Vector2* player, int x, int y);
		~Shot();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int);
		void hittedAction();

	private:
		int time;
		int dx;
		bool nowFast;
		const StageChild* stage;
		const Vector2* player;

		const int fast_speed = 10 * vectorRate;
		const int slow_speed =  3 * vectorRate;

		void initialize();
	};

	vector<Shot*> shots;

};




}
}
}