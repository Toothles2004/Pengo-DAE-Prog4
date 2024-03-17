#define WIN32_LEAN_AND_MEAN
#include "ControllerInput.h"
#include "Command.h"
#include <memory>
#include <windows.h>
#include <Xinput.h>
#include <vector>

class ControllerInput::ControllerInputImpl final
{
public:
	explicit ControllerInputImpl(int controllerIndex)
		: m_ControllerIndex{controllerIndex}
	{
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
	}

	~ControllerInputImpl() = default;

	void ProcessInput()
	{
		//Get the state of the controller
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		DWORD dwResult = XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		//Controller is not connected
		if (dwResult != ERROR_SUCCESS)
		{
			return;
		}

		for (const auto& keyBind : m_KeyBinds)
		{
			switch (keyBind.buttonState)
			{
			case ButtonState::pressed:
				if (static_cast<unsigned int>(keyBind.button) & m_CurrentState.Gamepad.wButtons)
				{
					keyBind.command->Execute();
				}
				break;
			case ButtonState::down:
				if (static_cast<unsigned int>(keyBind.button) & m_ButtonsPressedThisFrame)
				{
					keyBind.command->Execute();
				}
				break;
			case ButtonState::up:
				if (static_cast<unsigned int>(keyBind.button) & m_ButtonsReleasedThisFrame)
				{
					keyBind.command->Execute();
				}
				break;
			}
			
		}
	}

	void AddKeyBind(const ControllerKeyBinds& keyBind)
	{
		m_KeyBinds.emplace_back(keyBind);
	}

	void AddKeyBind(ButtonState state, ControllerButton button, std::shared_ptr<Command> command)
	{
		AddKeyBind(ControllerKeyBinds(state, button, std::move(command)));
	}

private:

	int m_ControllerIndex;

	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	std::vector<ControllerKeyBinds> m_KeyBinds{};
	//int m_GamepadLeftThumbDeadzone = 7849;
	//int m_GamepadRightThumbDeadzone = 8689;
};

ControllerInput::ControllerInput(int controllerIndex)
	: m_pImpl{ std::make_unique<ControllerInputImpl>(controllerIndex) }
{
}

void ControllerInput::ProcessInput()
{
	m_pImpl->ProcessInput();
}

void ControllerInput::AddKeyBind(const ControllerKeyBinds& keyBind)
{
	m_pImpl->AddKeyBind(keyBind);
}

void ControllerInput::AddKeyBind(ButtonState state, ControllerButton button, std::shared_ptr<Command> command)
{
	m_pImpl->AddKeyBind(state, button, std::move(command));
}

ControllerInput::~ControllerInput() = default;
