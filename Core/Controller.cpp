#include "Controller.h"
#include <iostream>


Controller::Controller()
{
    isTimeManagerStarted = false;
}

Controller::~Controller()
{
	m_timeMgr.stop();
    m_threadTimes.detach();
}

void Controller::startTimeManager()
{
    if(!isTimeManagerStarted) m_threadTimes = std::thread(&TimeManager::start, &m_timeMgr);
}

void Controller::stopTimeManager()
{
   m_timeMgr.stop();
   isTimeManagerStarted = false;
}

