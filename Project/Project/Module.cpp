#include "module.h"
#include <iostream>

using namespace std;

Module::Module(const char* name, short tasks, int units, long size)
{
	moduleName = name;
	tasksCount = tasks;
	unitsCount = units;
	moduleSize = size;
}

Module::Module(const char* name, short tasks, int units)
{
	moduleName = name;
	tasksCount = tasks;
	unitsCount = units;
}

Module::Module(const char* name, short tasks)
{
	moduleName = name;
	tasksCount = tasks;
}