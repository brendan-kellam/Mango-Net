#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Platform.h"
#include "Util/Interfaces/Manager.h"
#include "Util/Singleton.h"

#define DEFAULT_FILE_NAME "log.log"

class MANGO_API CLogManager final
	: public IManager, public CSingleton<CLogManager>
{
public:
	CLogManager();
	~CLogManager() override;

	void StartUp() override;
	void ShutDown() override;

	void WriteLine(std::string& msg, bool newline = true);

private:

	std::ofstream m_file;


};


#endif