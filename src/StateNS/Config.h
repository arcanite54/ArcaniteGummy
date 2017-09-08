#pragma once

#include "StateChild.h"


namespace StateNS {


class Config : public Child{
public:
	Config();
	~Config();
	void initialize();
	Child* update(const GrandParent*);
	void draw() const;

private:
	int mBackImg;

};




}