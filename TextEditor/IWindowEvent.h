#ifndef  __OBARO_IWINDOW_EVENTS_H
#define  __OBARO_IWINDOW_EVENTS_H
#include <Windows.h>
namespace obaro
{
	namespace windows
	{
		class IWindow;
		class IWindowEvent
		{
		  protected:
			  IWindowEvent();
			  void onCreateEvent(IWindow *sender);
			  static LRESULT CALLBACK EventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			  

		};
	}
}

#endif