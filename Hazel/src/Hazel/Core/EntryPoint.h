#pragma once

#include "Application.h"
#include "Log.h"

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Hazel Initialized!");
	HZ_INFO("Hello World!");

	auto app = Hazel::CreateApplication();
	app->Run();

	return 0;
}

#endif // HZ_PLATFORM_WINDOWS

