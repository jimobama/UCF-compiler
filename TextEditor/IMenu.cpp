#include "IMenu.h"
#include "IWindow.h"

using namespace obaro::windows;

IMenu::IMenu(IWindow *window)
{
	this->__hwnd = window->getHWnd();
	this->__hMenu = CreateMenu();
	this->__initial();
	
}
void IMenu::__initial()
{
	
	HMENU file_m = CreateMenu();
	AppendMenuW(file_m, MF_STRING, MENU_NEW, L"N&ew");
	AppendMenuW(file_m, MF_STRING, MENU_OPEN, L"O&pen");
	AppendMenuW(file_m, MF_SEPARATOR, MENU_SEPERATOR, NULL);
	AppendMenuW(file_m, MF_STRING, MENU_RECENT_FILES, L"Recent files...");
	AppendMenuW(this->__hMenu, MF_POPUP, (UINT_PTR)file_m, L"&File");
	this->__setMenu();
}
void IMenu::__setMenu()
{
	SetMenu(this->__hwnd, this->__hMenu);
}