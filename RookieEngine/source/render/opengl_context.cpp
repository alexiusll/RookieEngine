#include "stdafx.h"

#include "opengl_context.h"

static void on_window_size_callback(GLFWwindow* window, int width, int height)
{
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // 因为返回void*指针，所以需要转换一下
	glViewport(0, 0, width, height); // glViewport() 前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）

	pWindow->on_resize(width, height);
}

static void on_cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // 因为返回void*指针，所以需要转换一下
	pWindow->on_cursor_pos(xpos, ypos);
}

static void on_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // 因为返回void*指针，所以需要转换一下
	pWindow->on_scroll(xoffset, yoffset);
}

static void on_window_close_callback(GLFWwindow* window)
{
	auto pWindow = static_cast<Iwindow*>(glfwGetWindowUserPointer(window)); // 因为返回void*指针，所以需要转换一下
	pWindow->on_close();
}

bool OpenGL_Context::init(Iwindow* mWindow)
{
	this->mWindow = mWindow;

	// glfw: 初始化和配置
	// ------------------------------
	glfwInit(); // 初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // 主版本号(Major)和次版本号(Minor)都设为3。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 明确告诉GLFW我们使用的是核心模式(Core-profile)

	// glfwWindowHint(GLFW_DECORATED, GL_FALSE); // 无边框窗口

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// 创建一个窗口对象，这个窗口对象存放了所有和窗口相关的数据，而且会被GLFW的其他函数频繁地用到。
	// ! 这里只能传入 char* ，记得做一下转换
	GLFWwindow* glfwWindow = glfwCreateWindow(mWindow->Width, mWindow->Height, mWindow->Title.c_str(), nullptr, nullptr);

	// 设置 GlfwWindow*
	mWindow->set_native_window(glfwWindow);

	if (glfwWindow == NULL)
	{
		printf("Open window failed.");
		glfwTerminate();//关闭窗口
		return false;
	}

	glfwSetWindowUserPointer(glfwWindow, mWindow);
	// --- 回调函数的设置 ---
	glfwSetFramebufferSizeCallback(glfwWindow, on_window_size_callback); // 窗口调整大小
	glfwSetCursorPosCallback(glfwWindow, on_cursor_pos_callback); // 鼠标位置
	glfwSetScrollCallback(glfwWindow, on_scroll_callback); // 滑动
	glfwSetWindowCloseCallback(glfwWindow, on_window_close_callback); // 窗口关闭

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR); // tell GLFW to capture our mouse
	glfwMakeContextCurrent(glfwWindow);

	// 初始化 GLAD
	// GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前我们需要初始化GLAD。
	// 我们给GLAD传入了用来加载系统相关的OpenGL函数指针地址的函数。GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数。
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	// 配置全局的 opengl 参数
	// -----------------------------
	glEnable(GL_DEPTH_TEST); // 开启深度缓冲

	// 第一个参数表示我们打算将其应用到所有的三角形的正面和背面，第二个参数告诉我们用线来绘制。
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // 默认

	return false;
}

void OpenGL_Context::pre_render()
{
	// 在每个新的渲染迭代开始的时候我们总是希望清屏,否则我们仍能看见上一次迭代的渲染结果
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f); //状态设置函数: glClearColor来设置清空屏幕所用的颜色
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//状态使用: glClear函数来清空屏幕的颜色缓冲，它接受一个缓冲位(Buffer Bit)来指定要清空的缓冲
}

void OpenGL_Context::post_render()
{
	// 双缓冲(Double Buffer)机制 https://learnopengl-cn.github.io/01%20Getting%20started/03%20Hello%20Window/
	glfwPollEvents();// 函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）。
	glfwSwapBuffers(mWindow->get_native_window()); // 函数会 交换 颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上。
}

void OpenGL_Context::end()
{
	std::cout << "销毁 OpenGL_Context ..." << std::endl;
	glfwDestroyWindow(mWindow->get_native_window()); // 销毁指定的窗口及其上下文。
	glfwTerminate(); // 这个函数销毁所有剩余的窗口和游标，恢复任何修改过的伽马斜坡，并释放任何其他分配的资源。
}
