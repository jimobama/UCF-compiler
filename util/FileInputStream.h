#ifndef FILE_INPUT_STREAM_OBARO_H
#define FILE_INPUT_STREAM_OBARO_H


#include <stdio.h>  /* defines FILENAME_MAX */


#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif



#include <iostream>
#include <fstream>
#include <string>

#ifdef UTIL_EXPORTS
#define  FILE_INPUT_STREAM_API __declspec(dllexport)
#else
#define FILE_INPUT_STREAM_API __declspec(dllexport)
#endif

namespace obaro
{

	namespace io
	{

		class  FileInputStream : private std::ifstream
		{
		private:
			std::string _filepath;
			char *getDirectory();
		public:
			FILE_INPUT_STREAM_API   FileInputStream(std::string filename);

			FILE_INPUT_STREAM_API  virtual std::string GetContext();


		};
	}

}



#endif