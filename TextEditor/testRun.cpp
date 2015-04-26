#include "TextEditor.h"

using namespace obaro::windows;

int WINAPI wWinMain(HINSTANCE hIn, HINSTANCE hPrevInstance,
	PWSTR pCmdLine, int nCmdShow)
{

	TextEditor *window = new TextEditor(hIn, "Editor 0.2");
	window->__setTitle("Editor 0.2");
	window->__show(nCmdShow);
	window->__center();
	return window->__exec();


}