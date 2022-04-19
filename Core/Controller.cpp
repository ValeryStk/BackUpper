#include "Controller.h"
#include "Controller.h"
#include "Controller.h"
#include <iostream>

Controller::Controller()
{
	var = 8;
	std::cout << "************ Controller constructor *********************";
}

Controller::~Controller()
{
	std::cout << "************ Controller destructor *********************";
}

int Controller::getVar() const
{
	return var;
}

void Controller::setVar(int var)
{
	this->var = var;
}
