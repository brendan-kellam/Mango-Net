#ifndef UPDATEABLE_H
#define UPDATEABLE_H

#include "Platform.h"

class MANGO_API IUpdateable
{
public:
	virtual void Update() = 0;
};

#endif
