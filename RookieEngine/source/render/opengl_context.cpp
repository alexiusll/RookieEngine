#include "stdafx.h"

#include "opengl_context.h"

static void on_window_size_callback(GLFWwindow* window, int width, int height)
{
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // ��Ϊ����void*ָ�룬������Ҫת��һ��
	pWindow->on_resize(width, height);
}

static void on_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // ��Ϊ����void*ָ�룬������Ҫת��һ��
	pWindow->on_cursor_pos(xpos, ypos);
}

static void on_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // ��Ϊ����void*ָ�룬������Ҫת��һ��
	pWindow->on_scroll(xoffset, yoffset);
}

bool OpenGL_Context::init(Iwindow* glWindow)
{
	// ��ʼ��
	this->glWindow = glWindow;

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

// ���� GLFW �Ĵ���, ����ֻ�ܴ��� char* ���ǵ���һ��ת��
	GLFWwindow* glfwWindow = glfwCreateWindow(glWindow->Width, glWindow->Width, glWindow->Title.c_str(), nullptr, nullptr);
	if (glfwWindow == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();//�رմ���
		return false;
	}

	glfwSetWindowUserPointer(glfwWindow, glWindow);
	glfwSetFramebufferSizeCallback(glfwWindow, on_window_size_callback);
	glfwSetCursorPosCallback(glfwWindow, on_cursor_pos_callback);
	glfwSetScrollCallback(glfwWindow, on_scroll_callback);
	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // tell GLFW to capture our mouse
	glfwMakeContextCurrent(glfwWindow);

	//��ʼ�� GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST); // ������Ȼ���

	return false;
}

void OpenGL_Context::pre_render()
{
	glViewport(0, 0, glWindow->Width, glWindow->Height);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
