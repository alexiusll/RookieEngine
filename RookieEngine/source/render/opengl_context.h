#pragma once
#include "window/Iwindow.h"

class OpenGL_Context
{
public:
	bool init(Iwindow* glWindow);
private:
	// GLWindow* glWindow;

	/* ‘§‰÷»æ */
	void pre_render();

	Iwindow* glWindow;
};
