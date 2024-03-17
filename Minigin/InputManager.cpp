#include <SDL.h>
#include "InputManager.h"
#include "backends/imgui_impl_sdl2.h"


bool dae::InputManager::ProcessInput()
{
	for(const auto& controller : m_pControllers)
	{
		controller->ProcessInput();
	}

	m_pKeyboard->ProcessInput();

	//Get the state of the keyboard
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		//Process event for IMGUI
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

void dae::InputManager::AddController(ControllerInput* pController)
{
	m_pControllers.emplace_back(std::unique_ptr<ControllerInput>(pController));
}

KeyboardInput* dae::InputManager::GetKeyboard()
{
	return m_pKeyboard.get();
}
