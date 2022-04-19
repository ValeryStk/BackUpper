#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {

public:
	Controller();
	~Controller();
	int getVar()const;
	void setVar(int var);

private:
	int var;

};

#endif //CONTROLLER