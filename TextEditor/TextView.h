#ifndef TEXT_VIEW_EDITOR_H
#define TEXT_VIEW_EDITOR_H
#include<Windows.h>
//Defined a constructs
#define TEXT_VIEW    "TextView_win32";
#define TXM_BASE         (WM_USER)

#define TXM_OPENFILE    (TXM_BASE + 0)
#define TextView_OpenFile(hwndTV, szFile) \   SendMessage((hwndTV), TXM_OPENFILE, 0, (LPARAM)(szFile))
namespace obaro
{
	namespace windows
	{
		class TextView
		{

		};
	}
}
#endif