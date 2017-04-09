#pragma once

#include "GameChild.h"

namespace StateNS {

class Parent;

namespace GameNS {

namespace GameMainNS {
	class GameMain;
}

//SateNS::GameNS�ł�Parent�̖��
class Play : public Child
{
public:
	enum NextSequence
	{
		SEQ_TITLE,
		SEQ_PAUSE,
		SEQ_CONVERSE,
		SEQ_LOAD,
		SEQ_SAVE,
		SEQ_CLEAR,
		SEQ_OVER,

		SEQ_NONE
	};


	Play();
	~Play();
	void initialize();
	Child* update(Parent*);
	void draw() const;
	void moveTo(NextSequence);

private:
	GameMainNS::GameMain* gameMain;
	NextSequence mNextSeq;
};




}
}

