#include "stdafx.h"

#include "scene/sample_scene.h"
#include "window.h"

GLWindow::~GLWindow()
{
	// 销毁窗口
	std::cout << "销毁 GLWindow..." << std::endl;
	openGL_Context->end();

	std::cout << "销毁 UIContext..." << std::endl;
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
	std::cout << "关闭窗口..." << std::endl;
	IsRunning = false;
}

void GLWindow::render()
{
	// 清空当前窗口
	openGL_Context->pre_render();
	ui_context->pre_render();

	scene->render();

	textPanel->render(scene.get());

	ui_context->post_render();
	// 交换缓冲区
	openGL_Context->post_render();

	// 处理输入
	handle_input();
}

void GLWindow::handle_input()
{
	if (glfwGetKey(glfwWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		std::cout << "输入按键: esc" << std::endl;
	}
}
