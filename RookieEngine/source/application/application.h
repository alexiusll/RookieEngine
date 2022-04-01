#pragma once

#include "window/window.h"

class Application // ����ģʽ
{
public:
	static Application& Instance() { 
		if (sInstance == nullptr) {
			new Application("114514");
		}
		return *sInstance; 
	}
	void loop();

	class GC { // ����
		~GC() {
			std::cout << "GC ����" << std::endl;
			if (Application::sInstance) {
				delete Application::sInstance;
				Application::sInstance = nullptr;
			}
		};
		static GC gc;
	};

	~Application() {
		std::cout << "Application ����" << std::endl;
	}
private:
	Application(const std::string& app_name);
	static Application* sInstance; // Ӧ��ʵ��
	std::unique_ptr<GLWindow> mWindow; // �Լ�����Ĵ���
};