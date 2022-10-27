#pragma once

#include <stdint.h>

class Input
{
public:
	Input() = default;
	~Input() = default;

	void Initialize();

	void KeyDown(uint32_t keycode);
	void KeyUp(uint32_t keycode);

	bool IsKeyDown(uint32_t keycode);

private:
	bool m_Keys[256];
};
