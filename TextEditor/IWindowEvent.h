#ifndef  __OBARO_IWINDOW_EVENTS_H
#define  __OBARO_IWINDOW_EVENTS_H
#include <Windows.h>
#include <gl/gl.h>

namespace obaro
{
	namespace windows
	{
		class IWindow;
		class IWindowEvent
		{
		private :
			static HGLRC __hglrc;
			static HDC __hdc;
			//helper methods
			void setPixelFormat(HDC _hdc);
		  protected:
			  IWindowEvent();
			  //Event Direct Window Objects
			 virtual   void  onCreateEvent(IWindow *sender);
			 virtual   void  onPaintEvent(IWindow * sender);
			 virtual   void  onDestroyEvent(IWindow * sender);
			 virtual   void  onUpdateWindow(IWindow *sender);
			 virtual   void  onSizeEvent(IWindow *sender, WORD __lower, WORD __higher);
			 //The window event handler
			 static    LRESULT CALLBACK EventHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			  

		};
	}
}

#endif