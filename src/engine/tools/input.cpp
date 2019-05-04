#include "Input.h"

namespace le {

double Input::MousePosX = 0.0f;
double Input::MousePosY = 0.0f;
double Input::ScrollOffset = 0.0f;
bool Input::mouseButtons[MAX_BUTTONS];
bool Input::keys[MAX_KEYS];

void Input::Initialize()
{
	for (int i = 0; i < MAX_KEYS; i++)
	{
		Input::keys[i] = false;
	}

	for (int i = 0; i < MAX_BUTTONS; i++)
	{
		Input::mouseButtons[i] = false;
	}
}

bool Input::IsKeyPressed(unsigned int keycode)
{
	if (keycode >= MAX_KEYS)
		return false;
	return keys[keycode];
}


bool Input::IsMouseButtonPressed(unsigned int button)
{
	if (button >= MAX_BUTTONS)
		return false;
	return mouseButtons[button];
}

}