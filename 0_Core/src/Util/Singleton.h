#ifndef SINGLETON_H
#define SINGLETON_H

#include "Platform.h"
#include "Util/Interfaces/NonCopyable.h"

template <typename T>
class MANGO_API CSingleton
{

public:
	static T& Instance()
	{
		static T instance;
		return instance;
	}

protected:
	explicit CSingleton<T>() { }

	// Ensures pointer deconstruction of dynamically allocated child to be 
	// preformed in child (if the deconstructor is explicitly overrided publically)
	// NOTE: this case should NEVER really happen. Singletons should never be dynamically allocated. (bad form)
	virtual ~CSingleton<T>() { }

};


#endif