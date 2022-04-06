#pragma once
#include "window/Iwindow.h"

class OpenGL_Context
{
public:
	/* 初始化窗口 */
	bool init(Iwindow* glWindow);
	/* 预渲染 */
	void pre_render();

	void post_render();

	/* 销毁窗口 */
	void end();

private:
	// GLWindow* glWindow;

	Iwindow* mWindow;
};
