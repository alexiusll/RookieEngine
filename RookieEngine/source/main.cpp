#include "stdafx.h"
#include "application/application.h"

int main() {
	// std::unique_ptr<Application> app = std::make_unique<Application>("JMeshBox");
	// app->loop();

	Application::Instance().loop();

	return 0;
}