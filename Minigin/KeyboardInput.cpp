#include "KeyboardInput.h"
#include <functional>

KeyboardInput::KeyboardInput()
{
	memset(m_PreviousState, 0, SDL_NUM_SCANCODES * sizeof(Uint8));
	memset(m_CurrentState, 0, SDL_NUM_SCANCODES * sizeof(Uint8));
}

void KeyboardInput::ProcessInput()
{
	memcpy(m_PreviousState, m_CurrentState, SDL_NUM_SCANCODES * sizeof(Uint8));

	const Uint8* state = SDL_GetKeyboardState(nullptr);
	memcpy(m_CurrentState, state, SDL_NUM_SCANCODES * sizeof(Uint8));

	//Key events
	for (const auto& keyBind : m_KeyBinds)
	{
		if ((m_CurrentState[keyBind.button] && keyBind.buttonState == ButtonState::pressed) ||
			(m_CurrentState[keyBind.button] && !m_PreviousState[keyBind.button] && keyBind.buttonState == ButtonState::down) ||
			(!m_CurrentState[keyBind.button] && m_PreviousState[keyBind.button] && keyBind.buttonState == ButtonState::up))
		{
			keyBind.command->Execute();
		}
	}
}

void KeyboardInput::AddKeyBind(const KeyboardKeyBinds& keyBind)
{
	m_KeyBinds.emplace_back(keyBind);
}

void KeyboardInput::AddKeyBind(ButtonState state, SDL_Scancode button, std::shared_ptr<Command> command)
{
	AddKeyBind(KeyboardKeyBinds(state, button, command));
}
