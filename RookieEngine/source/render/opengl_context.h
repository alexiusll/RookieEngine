#pragma once
#include "window/Iwindow.h"

class OpenGL_Context
{
public:
	/* ��ʼ������ */
	bool init(Iwindow* glWindow);
	/* Ԥ��Ⱦ */
	void pre_render();

	void post_render();

	/* ���ٴ��� */
	void end();

private:
	// GLWindow* glWindow;

	Iwindow* mWindow;
};
