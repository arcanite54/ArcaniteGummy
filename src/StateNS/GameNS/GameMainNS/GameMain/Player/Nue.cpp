#include "Nue.h"

#include "..\..\..\..\..\Data.h"
#include "..\..\..\..\..\KeyInput.h"

namespace StateNS {
namespace GameNS {
namespace GameMainNS{

Nue::Nue()
{

}

Nue::~Nue()
{

}

PlayerChild* Nue::update()
{
	PlayerChild* next = this;

	return next;
}

void Nue::draw() const
{
	DrawFormatString(0, 40, MyData::WHITE, "Nue");
}



//==============================================
//�����v���C�x�[�g�֐�
//==============================================

//����Ȃ��̂͂Ȃ�



}
}
}