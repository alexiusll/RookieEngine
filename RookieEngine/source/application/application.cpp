#include "stdafx.h"
#include "application.h"

Application* Application::sInstance = nullptr;
Application::GC Application::GC::gc;

Application::Application(const std::string& app_name)
{
	mWindow = std::make_unique<GLWindow>();
	mWindow->init(1600, 900, app_name);
}

void Application::loop()
{
	while (mWindow->is_running())
	{
		mWindow->render();
	}
}