#include "IWindow.h"
//#include "IMenu.h"
using namespace obaro::windows;
//A default color


IWindow::IWindow(HINSTANCE hInstance, std::string title )
{
	this->__hInstance = hInstance;
	//if the value is not set then 
	if (this->__hInstance ==NULL)
		__hInstance = GetModuleHandle(NULL);
	this->__xPosition = 10;
	this->__yPosition = 0;
	this->__width = 600;
	this->__height = 400;	
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
	wc.hbrBackground = DEFAULT_BRG_COLOR;
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
	this->hwnd = CreateWindowW(//| WS_CLIPSIBLING 
								this->__title.c_str(),
								this-> __title.c_str(),
								WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS ,//| WS_HSCROLL | WS_VSCROLL,
								this->__xPosition,
								this->__yPosition, 
								this->__width, 
								this->__height,
								NULL,
								NULL,
								__hInstance,
								this//pass the object class to the procedure 
								);
}
int32_t IWindow::__exec()
{

	__register();
	__createWindow();
	::SetWindowText(this->getHWnd(), this->__title.c_str());
	//__menubar = new IMenu(this);
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


void IWindow::onUpdateWindow(IWindow *sender){
	

}
LRESULT CALLBACK  IWindow::windowEvents(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{


	switch (msg)
	{
	case WM_CREATE:
  
		this->onCreateEvent(this);
		return TRUE;		
	case WM_PAINT:		
		this->onPaintEvent(this);
		//swap the buffers 
		SwapBuffers(::GetDC(this->getHWnd()));
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		this->onDestroyEvent(this);
		break;
	case WM_SIZE:
		//get the size of the  of the window and its locations
		this->onSizeEvent(this, LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_TIMER:
		//call base on the timer time sets previously
		this->onUpdateWindow(this);
		break;
	default:
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return wParam;

}