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

	/* ��ȡ GLFWwindow* */
	GLFWwindow* get_native_window() override { return glfwWindow; }
	/* ���� GLFWwindow* */
	void set_native_window(GLFWwindow* window) 
	{
		glfwWindow = window;
	}

	/* ��Ⱦ���� */
	void render();

	/* �����û������� */
	void handle_input();

	bool is_running() { return this->IsRunning; }

private:
	GLFWwindow* glfwWindow; // GLFW ��Ķ���

	std::unique_ptr<OpenGL_Context> openGL_Context; // ��Ⱦ������

	std::unique_ptr<UIContext> ui_context;  // UI ������
	std::unique_ptr<TextPanel> textPanel;  // TextPanel

	std::unique_ptr<Sample_Scene> scene; // ����

	bool IsRunning;  // �Ƿ�������
};
