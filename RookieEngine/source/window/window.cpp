#include "stdafx.h"

#include "scene/sample_scene.h"

#include "ui/SceneHierarchy.h"

#include "scene/SceneManager.h"

#include "components/camera.h"

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

	// 初始化 scene
	// scene = std::make_unique<Sample_Scene>();
	// SceneHierarchy::Instance().initScene(scene);

	SceneManager::Instance().init();

	textPanel = std::make_unique<TextPanel>();

	ImGui::SetMouseCursor(ImGuiMouseCursor_None);

	return true;
}
void GLWindow::on_resize(int width, int height)
{
	this->Width = width;
	this->Height = height;

	// scene->resize(Width, Height);
	SceneManager::Instance().resize(width, height);
	
	render();
}
void GLWindow::on_cursor_pos(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	SceneManager::Instance().getCamera()-> ProcessMouseMovement(xoffset, yoffset);
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

	// 帧数
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// 清空当前窗口
	openGL_Context->pre_render();
	ui_context->pre_render();

	// scene->render();

	SceneManager::Instance().draw();

	textPanel->render();

	ConsoleLog::Instance().draw();
	SceneHierarchy::Instance().drawComponentsList();
	SceneHierarchy::Instance().drawComponentsProperties();

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

	std::shared_ptr<Camera> camera = SceneManager::Instance().getCamera();

	if (glfwGetMouseButton(glfwWindow, 1) == GLFW_PRESS) {
		// DEBUG_LOG("Mouse Button right");
		// DEBUG_LOG("fps:%f",1/ deltaTime);

		ImGui::SetMouseCursor(ImGuiMouseCursor_None);

		if (glfwGetKey(glfwWindow, GLFW_KEY_W) == GLFW_PRESS)
			camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
		if (glfwGetKey(glfwWindow, GLFW_KEY_S) == GLFW_PRESS)
			camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
		if (glfwGetKey(glfwWindow, GLFW_KEY_A) == GLFW_PRESS)
			camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
		if (glfwGetKey(glfwWindow, GLFW_KEY_D) == GLFW_PRESS)
			camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

		// 处理鼠标移动
		double x, y;
		glfwGetCursorPos(glfwWindow, &x, &y);
		on_cursor_pos(x, y);
	}
	else {
		ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
		firstMouse = true;
		// glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR); 
	}
}
