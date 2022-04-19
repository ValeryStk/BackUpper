#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <thread>
#include "TimeManager/TimeManager.h"
#include "Configurator/Configurator.h"


class Controller {

public:
	Controller();
	~Controller();
	int getVar()const;
	void setVar(int var);

private:
	int var;
	Configurator m_configurator;
	std::thread m_threadTimes;
	TimeManager m_timeMgr;

};

#endif //CONTROLLER