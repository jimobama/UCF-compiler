#include "IWindowEvent.h"
#include "IWindow.h"
#include "IMenu.h"
using namespace obaro::windows;

IWindowEvent::IWindowEvent()
{

}

void IWindowEvent::onCreateEvent(IWindow *sender)
{
	
}

LRESULT CALLBACK IWindowEvent::EventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	IWindow* window = NULL;

	switch (msg)
	{
		
		case WM_NCCREATE:
		{
			CREATESTRUCT * pcs = (CREATESTRUCT*)lParam;
			window = (IWindow*)pcs->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);		   		
			return TRUE;
		}			
		default:
			//get the window object
			window = (IWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			return  window->windowEvents(hwnd,msg,wParam,lParam);
		
	}
	


	return wParam;
}