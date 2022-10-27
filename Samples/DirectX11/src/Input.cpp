#include "Input.h"

void Input::Initialize()
{
	for (uint32_t keycode = 0; keycode < 256; ++keycode)
	{
		m_Keys[keycode] = false;
	}
}

void Input::KeyDown(uint32_t keycode)
{
	m_Keys[keycode] = true;
}

void Input::KeyUp(uint32_t keycode)
{
	m_Keys[keycode] = false;
}

bool Input::IsKeyDown(uint32_t keycode)
{
	return m_Keys[keycode];
}

