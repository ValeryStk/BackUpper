#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H
#include "json.hpp"

class Configurator {
public:
	Configurator();
	void parseConfigFile(const char* filename);

};

#endif // !CONFIGURATOR_H

