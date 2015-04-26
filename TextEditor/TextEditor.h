#ifndef WINDOW_EDIT_TEXT_H
#define WINDOW_EDIT_TEXT_H
#include <Windows.h>
#include "IWindow.h"
#include <string>
#include <stdint.h>

namespace obaro
{
	namespace windows
	{

		class TextEditor :public IWindow
		{

		public:
			TextEditor(HINSTANCE , std::string title = "");
			

		};

	}
}

#endif