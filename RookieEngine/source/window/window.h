#pragma once

#include "render/opengl_context.h"

#include "scene/sample_scene.h"

#include "Iwindow.h"
#include "ui/ui_context.h"
#include "ui/textPanel.h"

class GLWindow : public Iwindow {

public:
	GLWindow() : IsRunning(true), glfwWindow(nullptr) {
		openGL_Context = std::make_unique<OpenGL_Context>();
		ui_context = std::make_unique<UIContext>();
	}
	~GLWindow();

	bool init(int width, int height, const std::string& title);

	void on_resize(int width, int height) override;

	void on_cursor_pos(double xpos, double ypos) override;

	void on_scroll(double xoffset, double yoffset) override;

	void on_close() override;

	/* 获取 GLFWwindow* */
	GLFWwindow* get_native_window() override { return glfwWindow; }
	/* 设置 GLFWwindow* */
	void set_native_window(GLFWwindow* window) 
	{
		glfwWindow = window;
	}

	/* 渲染函数 */
	void render();

	/* 处理用户的输入 */
	void handle_input();

	bool is_running() { return this->IsRunning; }

private:
	GLFWwindow* glfwWindow; // GLFW 库的对象

	std::unique_ptr<OpenGL_Context> openGL_Context; // 渲染上下文

	std::unique_ptr<UIContext> ui_context;  // UI 上下文
	std::unique_ptr<TextPanel> textPanel;  // TextPanel

	std::unique_ptr<Sample_Scene> scene; // 场景

	bool IsRunning;  // 是否在运行
};
