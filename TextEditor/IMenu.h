#ifndef IMENU_MENU_H
#define  IMENU_MENU_H
#include <windows.h>
#define MENU_SEPERATOR 0x0000
#define MENU_NEW 0x0001
#define MENU_OPEN 0x0002
#define MENU_RECENT_FILES 0x0003
#define MENU_CLOSE_APP 0x0004

namespace obaro
{
	namespace windows
	{
		class IWindow;
		class IMenu
		{
		private:
			HMENU __hMenu;
			HWND __hwnd;
			void __initial();
			void __setMenu();
		public:
			IMenu(IWindow * parent);


		};
	}
}
#endif