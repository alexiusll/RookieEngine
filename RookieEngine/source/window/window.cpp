#include "stdafx.h"

#include "scene/sample_scene.h"
#include "window.h"

GLWindow::~GLWindow()
{
	// ���ٴ���
	std::cout << "���� GLWindow..." << std::endl;
	openGL_Context->end();

	std::cout << "���� UIContext..." << std::endl;
	ui_context->end();
}

bool GLWindow::init(int width, int height, const std::string& title)
{
	this->Width = width;
	this->Height = height;
	this->Title = title;

	openGL_Context->init(this);

	ui_context->init(this);

	scene = std::make_unique<Sample_Scene>();

	textPanel = std::make_unique<TextPanel>();

	return true;
}
void GLWindow::on_resize(int width, int height)
{
	this->Width = width;
	this->Height = height;

	scene->resize(Width, Height);
	render();
}
void GLWindow::on_cursor_pos(double xpos, double ypos)
{

}
void GLWindow::on_scroll(double xoffset, double yoffset)
{

}

void GLWindow::on_close()
{
	std::cout << "�رմ���..." << std::endl;
	IsRunning = false;
}

void GLWindow::render()
{
	// ��յ�ǰ����
	openGL_Context->pre_render();
	ui_context->pre_render();

	scene->render();

	textPanel->render(scene.get());

	ui_context->post_render();
	// ����������
	openGL_Context->post_render();

	// ��������
	handle_input();
}

void GLWindow::handle_input()
{
	if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "���밴��: esc" << std::endl;
	}
}
