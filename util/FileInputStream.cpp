
#include <windows.h>
#include "FileInputStream.h"
#include <exception>
using namespace obaro::io;

using namespace std;

// The directory path returned by native GetCurrentDirectory() no end backslash





FileInputStream::FileInputStream(std::string filepath)
{
	this->_filepath = filepath;
}

char * FileInputStream::getDirectory()
{
	char cCurrentPath[FILENAME_MAX];

	if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
	{
		return "Cant get current director";
	}

	return cCurrentPath;
}


std::string FileInputStream::GetContext()
{
	std::string content = "";
	try
	{
		//open the file
		this->open(this->_filepath);
		//check if the file is open incase there is an error
		if (this->is_open())
		{
			//	std::cout << "Open file \n";
			// while the bit is good read the file character by character	
			while (this->good())
			{
				char data;
				this->get(data);
				content.push_back((char)data);
				//std::cout << (char)data;
			}

			this->clear();
			this->close();
			
		}
		else{
			content =  this->_filepath + " does not exist in the current working directory\n";
			throw std::exception(content.c_str());
		}
	}
	catch (std::exception & err)
	{
		std::cerr << err.what();
	}

	return content;
	
}

