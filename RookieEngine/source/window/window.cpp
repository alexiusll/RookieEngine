#include "stdafx.h"

#include "window.h"

bool GLWindow::init(int width, int height, const std::string& title)
{
	this->Width = width;
	this->Height = height;
	this->Title = title;

	openGL_Context->init(this);

	return true;
}
void GLWindow::on_resize(int width, int height)
{
	this->Width = width;
	this->Height = height;
}
void GLWindow::on_cursor_pos(double xpos, double ypos)
{

}
void GLWindow::on_scroll(double xoffset, double yoffset)
{

}

void GLWindow::render()
{

}
