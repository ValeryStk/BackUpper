#include "Controller.h"
#include "Controller.h"
#include "Controller.h"
#include <iostream>

Controller::Controller()
{
	var = 8;
	m_threadTimes = std::thread(&TimeManager::start, &m_timeMgr);
	
}

Controller::~Controller()
{
	m_timeMgr.stop();
	m_threadTimes.detach();
}

int Controller::getVar() const
{
	return var;
}

void Controller::setVar(int var)
{
	this->var = var;
}
