#include "Nue.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Nue::Nue() : PlayerChild(5.0f, 15.0f, 1, 200)
{

}

Nue::~Nue()
{

}

PlayerChild* Nue::update(const Stage* _stage)
{
	PlayerChild* next = this;

	return next;
}




//==============================================
//�����v���C�x�[�g�֐�
//==============================================
void Nue::initialize(){}

void Nue::attack(){}

void Nue::draw_other() const {};

void Nue::loadImage() {} 

//����Ȃ��̂͂Ȃ�



}
}
}