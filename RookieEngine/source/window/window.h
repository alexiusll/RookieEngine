#pragma once

#include "render/opengl_context.h"

#include "Iwindow.h"

class GLWindow : public Iwindow {

public:
	GLWindow() :mWindow(nullptr) {
		openGL_Context = std::make_unique<OpenGL_Context>();
	}
	~GLWindow() {}

	bool init(int width, int height, const std::string& title);

	void on_resize(int width, int height) override;

	void on_cursor_pos(double xpos, double ypos) override;

	void on_scroll(double xoffset, double yoffset) override;

	/* ��Ⱦ���� */
	void render();

	bool is_running() { return this->IsRunning; }

private:
	GLFWwindow* mWindow; // GLFW ��Ķ���

	// ��Ⱦ������
	std::unique_ptr<OpenGL_Context> openGL_Context;

	bool IsRunning; // �Ƿ�������
};
