#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "TimeManager/TimeManager.h"

class Controller {

public:
	Controller();
	~Controller();
	int getVar()const;
	void setVar(int var);

private:
	int var;
	TimeManager m_timeMgr;

};

#endif //CONTROLLER