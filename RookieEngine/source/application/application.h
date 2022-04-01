#pragma once

#include "window/window.h"

class Application // 单例模式
{
public:
	static Application& Instance() { 
		if (sInstance == nullptr) {
			new Application("114514");
		}
		return *sInstance; 
	}
	void loop();

	class GC { // 回收
		~GC() {
			std::cout << "GC 析构" << std::endl;
			if (Application::sInstance) {
				delete Application::sInstance;
				Application::sInstance = nullptr;
			}
		};
		static GC gc;
	};

	~Application() {
		std::cout << "Application 析构" << std::endl;
	}
private:
	Application(const std::string& app_name);
	static Application* sInstance; // 应用实例
	std::unique_ptr<GLWindow> mWindow; // 自己定义的窗口
};