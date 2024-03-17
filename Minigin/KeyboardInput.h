#pragma once
#include "ButtonInput.h"

class KeyboardInput final
{
public:
	KeyboardInput();

	void ProcessInput();
	void AddKeyBind(const KeyboardKeyBinds& keyBind);
	void AddKeyBind(ButtonState state, SDL_Scancode button, std::shared_ptr<Command> command);

	~KeyboardInput() = default;
	KeyboardInput(const KeyboardInput& other) = delete;
	KeyboardInput(KeyboardInput&& other) = delete;
	KeyboardInput& operator=(const KeyboardInput& other) = delete;
	KeyboardInput& operator=(KeyboardInput&& other) = delete;

private:
	Uint8 m_PreviousState[SDL_NUM_SCANCODES]{};
	Uint8 m_CurrentState[SDL_NUM_SCANCODES]{};

	std::vector<KeyboardKeyBinds> m_KeyBinds{};
};

