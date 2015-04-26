#ifndef WINDOW_EDIT_TEXT_H
#define WINDOW_EDIT_TEXT_H
#include <Windows.h>
#include "ITextEditorListener.h"
#include <string>


namespace obaro
{
	namespace editor
	{

		class TextEditor :protected ITextEditorListener <TextEditor>
		{

		private:
			//Initial fields
			WNDCLASSEX *wndClassEx;
			MSG *msg;
			HINSTANCE *__instance;

			//private methods 
			void initial();
			ITextEditorListener  *listener;
			void __register();
			void __createWindow();

		public:
			TextEditor(std::string title = "Editor 1.0");

		};

	}
}

#endif