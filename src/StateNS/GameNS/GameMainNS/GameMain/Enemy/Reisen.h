#pragma once

#include "..\..\..\..\..\Data.h"
#include "EnemyChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{


//�W�����v�ړ��̊Ԋu(�t���[��)
//�傫������ƈړ��ɂ����鎞�Ԃ������Ȃ�
//�傫������ƈړ��̋������傫���Ȃ�
constexpr int jump_interval = 60;
static_assert(jump_interval > 5, "A constance \'jump_interval\' is Too small");

class Reisen : public EnemyChild
{
public:
	Reisen(int x, int y);
	Reisen(int x, int y, bool isOriginal);
	~Reisen();

	void update(const StageChild* _stage, const Vector2* _camera);
	virtual void setPlayer(const Vector2* _player) override { this->player = _player; if (isOriginal)replica->setPlayer(_player); }
	virtual vector<Attack*> getAttacks() const override;
	virtual vector<EnemyChild*> getChilds() override { vector<EnemyChild*> ret{ replica }; return ret; }

private:
	int images;
	bool imgLoad = false;
	int mTime;

	bool nowMoving;
	const bool isOriginal;
	bool makeReplica;
	Reisen* replica;

	//Character�̊֐�
	void hittedAction();

	//Enemychild�̊֐�
	void move(const StageChild*, int& dx, int& dy);
	virtual void draw_other(const Vector2* camera)const override;

	//TODO �摜�����ւ�
	void loadImage() { images = LoadGraph("Data/Image/balloon.png"); mImage = images; imgLoad = true; }
	void attack();

	void initialize();

	class Shot : public Attack
	{
	public:
		Shot(const EnemyChild*, const Vector2* player, int x, int y);
		~Shot();
		void update();
		virtual void draw(const Vector2*) const override;
		void setStatus(Vector2, int);
		void hittedAction();

	private:
		int time;
		int dx;
		bool nowFast;
		const Vector2* player;

		const int fast_speed = 10 * vectorRate;
		const int slow_speed =  2 * vectorRate;

		void initialize();
	};


};




}
}
}