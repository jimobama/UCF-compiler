#include "stdafx.h"
#include <iostream>
#include "Console.h"
#include <fstream>
using namespace obaro::io;




//implementation of the console class

Console::Console()
{

}

std::string Console::prompt(std::string msg)
{
	//print the message to the console
	Console::write(msg);
	std::string input;
	std::getline(std::cin, input);
	//clear and resert std input
	//	std::cin.clear();
	//std::cin.ignore(INT_MAX, '\n');
	return input;

}
void Console::writeln(std::string out)
{
	Console::write(out + "\n");
}
void Console::write(std::string out)
{
	std::cout << out;
}
bool Console::isExists(std::string filename)
{
	std::ifstream ifile(filename);
	if (ifile)
	{
		return true;
	}
	return false;
}

void Console::clear()
{
	system("cls");
}


//implement inner path class 
Console::Path::Path()
{
	//do nothing
}
bool Console::Path::isExtensionEqual(const std::string filename, const std::string __ext)
{

	std::string ext__ = Path::__getFileExtension(filename);
	if (ext__.compare(__ext) == 0)
	{
		return true;
	}
	return false;
}

std::string Console::Path::__getFileExtension(const std::string FileName)
{
	if (FileName.find_last_of(".") != std::string::npos)
		return FileName.substr(FileName.find_last_of(".") + 1);
	return NULL;
}