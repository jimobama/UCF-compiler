#include "TextView.h"
#include"IWindow.h"
using namespace  obaro::windows;

TextView::TextView(IWindow *parent)
{
	this->__parent = parent;
}


void TextView::onPaint()
{
	PAINTSTRUCT ps;
	::BeginPaint(this->__parent->getHWnd(), &ps);
	//start painting of the parent windows



	::EndPaint(this->__parent->getHWnd(),&ps);
}


