#ifndef MANAGERINTERFACE_H
#define MANAGERINTERFACE_H

#include "Platform.h"

class MANGO_API IManager
{
public:
	virtual void StartUp() = 0;
	virtual void ShutDown() = 0;
};

#endif