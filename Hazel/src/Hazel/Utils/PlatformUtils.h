#pragma once

#include <string>

namespace Hazel {

	class Time
	{
	public:
		static float GetTime();
	};

	class FileDialogs
	{
	public:
		// These return empty string is canceled.
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};

}
