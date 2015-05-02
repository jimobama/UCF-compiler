#ifndef TEXT_VIEW_EDITOR_H
#define TEXT_VIEW_EDITOR_H
#include<windows.h>
#include <stdint.h>
//Defined a constructs


namespace obaro
{
	namespace windows
	{
		class IWindow;
		class TextView 
		{
		 private:
			int __length;
			IWindow *__parent;			
		public:
			TextView(IWindow *parant);
			void TextView::onPaint();			
		};
	}
}
#endif