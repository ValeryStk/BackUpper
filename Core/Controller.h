#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <thread>
#include "TimeManager/TimeManager.h"
#include "Configurator/Configurator.h"


class Controller {

public:
	Controller();
	~Controller();
    void startTimeManager();
    void stopTimeManager();

private:
    bool isTimeManagerStarted;
	Configurator m_configurator;
	std::thread m_threadTimes;
	TimeManager m_timeMgr;

};

#endif //CONTROLLER
