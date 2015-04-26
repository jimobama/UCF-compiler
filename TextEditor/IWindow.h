#ifndef _OB_IWINDOW_H
#define _OB_IWINDOW_H
#include <windows.h>
#include <string>
#include <stdint.h>
#include "IWindowEvent.h"



namespace obaro
{
	namespace windows
	{
		class IMenu;
		class IWindow :protected IWindowEvent
		{
		private://fields
			MSG  msg;
			HWND hwnd;
			WNDCLASSW wc;
			IMenu * __menubar;
			HINSTANCE __hInstance;
			std::wstring __title;
			int32_t __cmdShow;
			int32_t __xPosition,__yPosition, __width,__height;

			//fields controll


		private:
			virtual void __initial();
		protected:
			void __register();
			void __createWindow();
		public:
			IWindow(HINSTANCE hInstance=NULL,std::string title="");	
			LRESULT CALLBACK windowEvents(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
			
			void __setTitle(std::string title);			
			void __show(int32_t cmd = 1);
			void __center();
			HWND &getHWnd();
			int32_t __exec();

		};

	}
}

#endif