#include "stdafx.h"

#include "opengl_context.h"

static void on_window_size_callback(GLFWwindow* window, int width, int height)
{
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // ��Ϊ����void*ָ�룬������Ҫת��һ��
	glViewport(0, 0, width, height); // glViewport() ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ�

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

static void on_window_close_callback(GLFWwindow* window)
{
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // ��Ϊ����void*ָ�룬������Ҫת��һ��
	pWindow->on_close();
}

bool OpenGL_Context::init(Iwindow* mWindow)
{
	this->mWindow = mWindow;

	// glfw: ��ʼ��������
	// ------------------------------
	glfwInit(); // ��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // ���汾��(Major)�ʹΰ汾��(Minor)����Ϊ3��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ��ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)

	// glfwWindowHint(GLFW_DECORATED, GL_FALSE); // �ޱ߿򴰿�

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// ����һ�����ڶ���������ڶ����������кʹ�����ص����ݣ����һᱻGLFW����������Ƶ�����õ���
	// ! ����ֻ�ܴ��� char* ���ǵ���һ��ת��
	GLFWwindow* glfwWindow = glfwCreateWindow(mWindow->Width, mWindow->Height, mWindow->Title.c_str(), nullptr, nullptr);

	// ���� GlfwWindow*
	mWindow->set_native_window(glfwWindow);

	if (glfwWindow == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();//�رմ���
		return false;
	}

	glfwSetWindowUserPointer(glfwWindow, mWindow);
	// --- �ص����������� ---
	glfwSetFramebufferSizeCallback(glfwWindow, on_window_size_callback); // ���ڵ�����С
	glfwSetCursorPosCallback(glfwWindow, on_cursor_pos_callback); // ���λ��
	glfwSetScrollCallback(glfwWindow, on_scroll_callback); // ����
	glfwSetWindowCloseCallback(glfwWindow, on_window_close_callback); // ���ڹر�

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR); // tell GLFW to capture our mouse
	glfwMakeContextCurrent(glfwWindow);

	// ��ʼ�� GLAD
	// GLAD����������OpenGL�ĺ���ָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ������Ҫ��ʼ��GLAD��
	// ���Ǹ�GLAD��������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ�����GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ�����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// ����ȫ�ֵ� opengl ����
	// -----------------------------
	glEnable(GL_DEPTH_TEST); // ������Ȼ���

	// ��һ��������ʾ���Ǵ��㽫��Ӧ�õ����е������ε�����ͱ��棬�ڶ������������������������ơ�
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Ĭ��

	return false;
}

void OpenGL_Context::pre_render()
{
	// ��ÿ���µ���Ⱦ������ʼ��ʱ����������ϣ������,�����������ܿ�����һ�ε�������Ⱦ���
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //״̬���ú���: glClearColor�����������Ļ���õ���ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//״̬ʹ��: glClear�����������Ļ����ɫ���壬������һ������λ(Buffer Bit)��ָ��Ҫ��յĻ���
}

void OpenGL_Context::post_render()
{
	// ˫����(Double Buffer)���� https://learnopengl-cn.github.io/01%20Getting%20started/03%20Hello%20Window/
	glfwPollEvents();// ���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã���
	glfwSwapBuffers(mWindow->get_native_window()); // ������ ���� ��ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ�ϡ�
}

void OpenGL_Context::end()
{
	std::cout << "���� OpenGL_Context ..." << std::endl;
	glfwDestroyWindow(mWindow->get_native_window()); // ����ָ���Ĵ��ڼ��������ġ�
	glfwTerminate(); // ���������������ʣ��Ĵ��ں��α꣬�ָ��κ��޸Ĺ���٤��б�£����ͷ��κ������������Դ��
}
