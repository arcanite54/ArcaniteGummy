#include "Sakuya.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Sakuya::Sakuya() : PlayerChild(5.0f, 15.0f, 1, 150)
{

}

Sakuya::~Sakuya()
{

}

PlayerChild* Sakuya::update(const Stage* _stage)
{
	PlayerChild* next = this;

	return next;
}




//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Sakuya::initialize(){}

void Sakuya::attack(){}

void Sakuya::draw_other() const{}

void Sakuya::loadImage(){}


//����Ȃ��̂͂Ȃ�



}
}
}