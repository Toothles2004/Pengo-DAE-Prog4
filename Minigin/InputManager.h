#pragma once
#include <memory>
#include <vector>
#include "ControllerInput.h"
#include "KeyboardInput.h"
#include "Singleton.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddController(ControllerInput* pController);
		KeyboardInput* GetKeyboard();

	private:
		std::vector<std::unique_ptr<ControllerInput>> m_pControllers;
		inline static std::unique_ptr<KeyboardInput> m_pKeyboard = std::make_unique<KeyboardInput>();
	};

}
