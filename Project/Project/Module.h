#pragma once

class Module
{
public:
	Module(const char* name, short tasks, int units, long size);   //Остальные члены класса
	Module(const char* name, short tasks, int units);
	Module(const char* name, short tasks);
private:
	const char* moduleName;
	short tasksCount;
	int unitsCount;
	long moduleSize;
};

