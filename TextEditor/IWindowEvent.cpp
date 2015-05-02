/*The class required the opengl library and the linked to point towards it*/

#include "IWindowEvent.h"
#include "IWindow.h"
#include<gl\GLU.h>


using namespace obaro::windows;
IWindowEvent::IWindowEvent()
{

}

void IWindowEvent::onCreateEvent(IWindow *sender){
//get the device context
IWindowEvent::__hdc = ::GetDC(sender->getHWnd());
//set the pixer format
this->setPixelFormat(IWindowEvent::__hdc);

IWindowEvent::__hglrc = ::wglCreateContext(IWindowEvent::__hdc);
::wglMakeCurrent(IWindowEvent::__hdc, IWindowEvent::__hglrc);

::SetTimer(sender->getHWnd(), 101, 1, 0);

}
void IWindowEvent::onPaintEvent(IWindow * sender)
{
	
}
void IWindowEvent::onDestroyEvent(IWindow * sender)
{
	::wglMakeCurrent(IWindowEvent::__hdc, NULL);
	::wglDeleteContext(IWindowEvent::__hglrc);
	//kill the time created ealier on create methods
	::KillTimer(sender->getHWnd(), 101);
	//close the window
	::PostQuitMessage(WM_QUIT);	

}

void IWindowEvent::onSizeEvent(IWindow *sender, WORD __width , WORD __height)
{
	glViewport(0, 0, __width, __height);

	/*      Set current Matrix to projection*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); //reset projection matrix

	/*      Time to calculate aspect ratio of
	our window.
	*/
	gluPerspective(54.0f, (GLfloat)__width / (GLfloat)__height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW); //set modelview matrix
	glLoadIdentity(); //reset modelview matrix

}

void IWindowEvent::onUpdateWindow(IWindow *sender)
{
	// update called the onPaintEvent
	this->onPaintEvent(sender);
}

/*This methods can not be over */
HDC IWindowEvent::__hdc = NULL;
HGLRC IWindowEvent::__hglrc = NULL;

//The methjod set the pix format of the window device context
void IWindowEvent::setPixelFormat(HDC _hdc_)
{
	int __pixelFormat;
	static PIXELFORMATDESCRIPTOR _pfd_ =
	{
		sizeof(PIXELFORMATDESCRIPTOR),//the size of the pdf
		1, //version of the pdf
		PFD_DRAW_TO_WINDOW | //allow it to darw to window not bitmap
		PFD_SUPPORT_OPENGL | //allow it to support opengl
		PFD_DOUBLEBUFFER  | //support buffer drawing 
		PFD_TYPE_RGBA ,//allow for support for rgba drawing
		32, //allow 24bit pixel coloring
		0, 
		0,
		0,
		0, 
		0, 
		0,
		0,
		0,
		0,
		0,
		0, 
		0,
		0,
		16, //size of the depth buffer
		0,
		0,
		PFD_MAIN_PLANE, //draw in a main plain
		0,
		0,
		0,
		0	
	};

	//choose the pixel format
	__pixelFormat = ChoosePixelFormat(_hdc_,&_pfd_);
	//set the pixel format
	::SetPixelFormat(_hdc_, __pixelFormat, &_pfd_);
}
//The main window procedure
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