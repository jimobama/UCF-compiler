#include<Windows.h>
#include<tchar.h>


int  WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,	PWSTR szCmdLine, int CmdShow)
{
	PDWORD cChars = NULL;
	HANDLE std = GetStdHandle(STD_OUTPUT_HANDLE);

	if (std == INVALID_HANDLE_VALUE) {
		_tprintf(L"Cannot retrieve standard output handle\n (%d)",
			GetLastError());
	}

	WriteConsole(std, szCmdLine, _tcslen(szCmdLine), cChars, NULL);

	return EXIT_SUCCESS;
	
}