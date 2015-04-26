#include "IWindow.h"
#include "IMenu.h"
using namespace obaro::windows;

IWindow::IWindow(HINSTANCE hInstance, std::string title )
{
	this->__hInstance = hInstance;

	this->__xPosition = 10;
	this->__yPosition = 0;
	this->__width = 500;
	this->__height = 500;	
	this->__setTitle(title);
}
HWND &IWindow::getHWnd()
{
	return this->hwnd;
}
void IWindow::__setTitle(std::string title)
{
	std::wstring titleName(title.begin(), title.end());
	this->__title = titleName;
}
void IWindow::__show(int32_t cmd)
{
	this->__cmdShow = cmd;	


}

void IWindow::__initial()
{
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(IWindow);
	wc.lpszClassName = this->__title.c_str();
	wc.hInstance = __hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpszMenuName = NULL;
	wc.lpfnWndProc = &IWindow::EventHandler;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
}


void IWindow::__register()
{
	__initial();
	RegisterClassW(&wc);
}
void IWindow::__createWindow()
{	
	this->hwnd = CreateWindowW(this->__title.c_str(),this-> __title.c_str(),
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		this->__xPosition, this->__yPosition, this->__width, this->__height, NULL,NULL, __hInstance,this);
}
int32_t IWindow::__exec()
{

	__register();
	__createWindow();
	__menubar = new IMenu(this);
	ShowWindow(hwnd, this->__cmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		::TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

void IWindow::__center()
{
	
		RECT rc;

		if (this->hwnd != NULL){
			GetWindowRect(this->hwnd, &rc);
			//set the position of the window
			this->__xPosition = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
			this->__yPosition = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
			//update the window position
			SetWindowPos(hwnd, NULL, __xPosition, __yPosition, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		}
		else
		{
			this->__xPosition = (GetSystemMetrics(SM_CXSCREEN) - this->__width) / 2;
			this->__yPosition = (GetSystemMetrics(SM_CYSCREEN) - this->__height) / 2;
		}
}
LRESULT CALLBACK  IWindow::windowEvents(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	case WM_CREATE:
		this->onCreateEvent(this);
		break;
	case WM_PAINT:
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		::PostQuitMessage(WM_QUIT);
		break;
	default:
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return wParam;

}