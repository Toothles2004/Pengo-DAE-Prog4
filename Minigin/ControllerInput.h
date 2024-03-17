#pragma once
#include <memory>
#include "ButtonInput.h"

class ControllerInput final
{
public:
	explicit ControllerInput(int controllerIndex);

	void ProcessInput();
	void AddKeyBind(const ControllerKeyBinds& keyBind);
	void AddKeyBind(ButtonState state, ControllerButton button, std::shared_ptr<Command> command);

	~ControllerInput();
	ControllerInput(const ControllerInput& other) = delete;
	ControllerInput(ControllerInput&& other) = delete;
	ControllerInput& operator=(const ControllerInput& other) = delete;
	ControllerInput& operator=(ControllerInput&& other) = delete;

private:
	class ControllerInputImpl;
	std::unique_ptr<ControllerInputImpl> m_pImpl;
};

