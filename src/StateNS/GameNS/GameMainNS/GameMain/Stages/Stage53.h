#pragma once
#include "..\..\..\..\..\Data.h"
#include "StageChild.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

class Kaguya;

class Stage53 : public StageChild
{
public:
	Stage53();
	~Stage53();
	void update(GameMain*, PlayerChild*);
	void draw(const Vector2* player) const;
	bool isClear() const;
	void draw_front(const Vector2* _camera) const override;
private:
	void initialize();
	void updateConverse(GameMain*, PlayerChild*);
	bool converseFlag0, converseFlag0fin;
	bool converseFlag1, converseFlag1fin;
	Kaguya* kaguya = 0;

	AllEnemies itoE(int num)
	{
		//�͈͊O�������狭���I�ɔ͈͓��ɕϊ�
		num = max(0, min(7, num));

		switch (num)
		{
			//�n��
		case(0):return ENE_YACH;
		case(1):return ENE_PIKA;
		case(2):return ENE_BROTH;
		case(3):return ENE_MARI;
		case(4):return ENE_USA;
		case(5):return ENE_USA;

			//��
		case(6):return ENE_BALL;
		case(7):return ENE_TERESA;
		}
		assert(!"Stage53::itoE: �G�R�[�h���s���ł�");
		return ENE_NONE;
	}




};




}
}
}