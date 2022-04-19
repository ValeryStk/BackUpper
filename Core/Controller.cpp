#include "Controller.h"
#include "Controller.h"
#include "Controller.h"
#include <iostream>

Controller::Controller()
{
	var = 8;
	m_timeMgr.start();
	
}

Controller::~Controller()
{
	
}

int Controller::getVar() const
{
	return var;
}

void Controller::setVar(int var)
{
	this->var = var;
}
