#include "TextDocument.h"
#include <Windows.h>
using namespace obaro::windows;

TextDocument::TextDocument(std::string filename)
{
	if (filename.size() > 0)
	{
		this->init(filename);
	}
}

bool  TextDocument::init(std::string filename)
{
	HANDLE hFile;
	std::wstring filepath(filename.begin(), filename.end());
	hFile = CreateFile(filepath.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	return init(hFile);
}

bool  TextDocument::init(HANDLE hFile)
{
	ULONG numread;
	if ((__size = ::GetFileSize(hFile, 0)) == 0)
		return false;

	__text = new char[__size];
	//read the file into memory
	::ReadFile(hFile, __text, this->__size, &numread, 0);
	//work put where each line of text start
	this->__workLines();
	CloseHandle(hFile);
	return true;
}

bool  TextDocument::__workLines()
{
	ULONG i = 0;
	ULONG linestart = 0;

	// allocate the line-buffer
	if ((this->__lineBuffer = new ULONG[__size]) == 0)
		return false;

	this->__lineCount = 0;

	// loop through every byte in the file
	for (i = 0; i < (ULONG) this->__size;)
	{
		if (this->__text[i++] == '\r')
		{
			// carriage-return / line-feed combination
			if (this->__text[i] == '\n')
				i++;
			// record where the line starts
			this->__lineBuffer[this->__lineCount++] = linestart;
			linestart = i;
		}
	}

	this->__lineBuffer[__lineCount] = __size;
	return true;
	
}


ULONG TextDocument::getline(ULONG lineno, char *buf, size_t len)
{
	char *lineptr;
	ULONG linelen;

	// find the start of the specified line
	lineptr = this->__text + this->__lineBuffer[lineno];

	// work out how long it is, by looking at the next line's starting point
	linelen = this->__lineBuffer[lineno + 1] - this->__lineBuffer[lineno];

	// make sure we don't overflow caller's buffer
	linelen = min(len, linelen);
	//memory compy 
	memcpy(buf, lineptr, linelen);
	return linelen;
}
