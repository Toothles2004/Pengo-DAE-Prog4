#pragma once
#include <SDL.h>
#include "Command.h"

namespace daeEngine
{
	enum class ControllerButton
	{
		dPadUp = 0x0001,
		dPadDown = 0x0002,
		dPadLeft = 0x0004,
		dPadRight = 0x0008,
		start = 0x0010,
		back = 0x0020,
		leftThumb = 0x0040,
		rightThumb = 0x0080,
		leftShoulder = 0x0100,
		rightShoulder = 0x0200,
		a = 0x1000,
		b = 0x2000,
		x = 0x4000,
		y = 0x8000
	};

	enum class ButtonState
	{
		up,
		down,
		pressed
	};

	struct ControllerKeyBinds
	{
		ButtonState buttonState;
		ControllerButton button;
		//Shared pointer allows the binding of multiple buttons to the same command
		std::shared_ptr<daeEngine::Command> command;
	};

	struct KeyboardKeyBinds
	{
		ButtonState buttonState;
		SDL_Scancode button;
		//Shared pointer allows the binding of multiple buttons to the same command
		std::shared_ptr<daeEngine::Command> command;
	};
}