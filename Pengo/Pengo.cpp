#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "GraphComponent.h"
#include "Minigin.h"
//#include "RotatorComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "InputManager.h"
#include "DamageCommand.h"
#include "HealthDisplayObserverComponent.h"
#include "HealthSubjectComponent.h"
#include "MovementCommand.h"
#include "MovementComponent.h"
#include "ScoreDisplayObserverComponent.h"
#include "ScoreSubjectComponent.h"
#include "IncreaseScoreCommand.h"
#include "PlayerComponent.h"
#include "SoundServiceLocator.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::vector<int>> ReadLevelLayoutFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::vector<std::vector<int>> layout;
	std::string line;

	while (std::getline(file, line))
	{
		// Skip comments and empty lines
		if (!line.empty() && line[0] != '"' && line[0] != ';')
		{
			std::istringstream iss(line);
			std::vector<int> row;

			char valueChar; // Use char to capture non-digit characters
			while (iss >> valueChar)
			{
				if (isdigit(valueChar))
				{
					int value = valueChar - '0'; // Convert char to int
					// Ensure the value is within the valid range
					if (value >= 0 && value <= 5)
					{
						row.push_back(value);
					}
				}
			}

			layout.push_back(row);
		}
	}

	return layout;
}

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Programming 4 assignment");
	int tileSize{ 16 };

	//sound
	int amountOfChannels{ 2 };
	daeEngine::SoundServiceLocator::RegisterSoundService(std::make_unique<daeEngine::SDLSoundService>(amountOfChannels));
	auto& soundService = daeEngine::SoundServiceLocator::GetSoundService();
	soundService.LoadSound("..\\Data\\sounds\\mainBGM.mp3", 0);
	soundService.PlaySound(0, 0, 10, -1);

	std::vector<std::vector<int>> levelLayout = ReadLevelLayoutFromFile("..\\Data\\levels\\level1.txt");

	// Iterate over the layout to create game objects
	for (size_t y{}; y < levelLayout.size(); ++y)
	{
		
		for (size_t x{}; x < levelLayout[y].size(); ++x)
		{
			int objectType = levelLayout[y][x];
			if(objectType == 0)
			{
				continue;
			}
			if(objectType == 1)
			{
				auto iceBlock = scene.CreateGameObject();
				iceBlock->AddComponent<RenderComponent>("textures/blocks.png", glm::vec2{0, 0}, glm::vec2{9, 4});
				iceBlock->SetLocalPosition({ x * tileSize, y * tileSize +200, 0 });
				continue;
			}
			if (objectType == 2)
			{
				auto egg = scene.CreateGameObject();
				egg->AddComponent<RenderComponent>("textures/blocks.png", glm::vec2{ 1, 0 }, glm::vec2{ 9, 4 });
				egg->SetLocalPosition({ x * tileSize, y * tileSize+200, 0 });
				continue;
			}
			if (objectType == 3)
			{
				auto snoBee = scene.CreateGameObject();
				snoBee->AddComponent<RenderComponent>("textures/snoBee1.png");
				snoBee->SetLocalPosition({ x * tileSize, y * tileSize+200, 0 });
				continue;
			}
			if (objectType == 4)
			{
				auto diamond = scene.CreateGameObject();
				diamond->AddComponent<RenderComponent>("textures/blocks.png", glm::vec2{ 0, 2 }, glm::vec2{ 9, 4 });
				diamond->SetLocalPosition({ x * tileSize, y * tileSize+200, 0 });
				continue;
			}
			if (objectType == 5)
			{
				//Penguin
				auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
				/*//First player display
				auto goFirstPlayerDisplay = scene.CreateGameObject();
				goFirstPlayerDisplay->AddComponent<TextComponent>("# Lives: 4", font);
				auto healthObserver = goFirstPlayerDisplay->AddComponent<HealthDisplayObserverComponent>();
				goFirstPlayerDisplay->SetLocalPosition({ 5, 130, 0 });

				//First player score
				auto goFirstPlayerScore = scene.CreateGameObject();
				goFirstPlayerScore->AddComponent<TextComponent>("Score: 0", font);
				auto scoreObserver = goFirstPlayerScore->AddComponent<ScoreDisplayObserverComponent>();
				goFirstPlayerScore->SetLocalPosition({ 5, 145, 0 });

				//First player
				auto goFirstPlayer = scene.CreateGameObject();
				goFirstPlayer->AddComponent<RenderComponent>("textures/penguinDown.png");
				//goPenguin->AddComponent<MovementComponent>(100.f);
				goFirstPlayer->AddComponent<PlayerComponent>();
				goFirstPlayer->AddComponent<HealthSubjectComponent>()->AddObserver(healthObserver);
				goFirstPlayer->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver);
				goFirstPlayer->SetLocalPosition({ 100, 250, 0 });

				//Add input commands
				auto& manager = dae::InputManager::GetInstance();
				daeEngine::ControllerInput* controller = new daeEngine::ControllerInput(0);
				controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadUp, std::make_shared<MovementCommand>(goFirstPlayer, glm::vec3(0, -1, 0)));
				controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadDown, std::make_shared<MovementCommand>(goFirstPlayer, glm::vec3(0, 1, 0)));
				controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadLeft, std::make_shared<MovementCommand>(goFirstPlayer, glm::vec3(-1, 0, 0)));
				controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadRight, std::make_shared<MovementCommand>(goFirstPlayer, glm::vec3(1, 0, 0)));
				controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::x, std::make_shared<DamageCommand>(goFirstPlayer));
				controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::a, std::make_shared<IncreaseScoreCommand>(goFirstPlayer, 10));
				controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::b, std::make_shared<IncreaseScoreCommand>(goFirstPlayer, 100));
				manager.AddController(controller);*/

				//Second player display
				auto goSecondPlayerDisplay = scene.CreateGameObject();
				goSecondPlayerDisplay->AddComponent<TextComponent>("# Lives: 4", font);
				auto healthObserver = goSecondPlayerDisplay->AddComponent<HealthDisplayObserverComponent>();
				goSecondPlayerDisplay->SetLocalPosition({ 5, 160, 0 });

				//Second player score
				auto goSecondPlayerScore = scene.CreateGameObject();
				goSecondPlayerScore->AddComponent<TextComponent>("Score: 0", font);
				auto scoreObserver = goSecondPlayerScore->AddComponent<ScoreDisplayObserverComponent>();
				goSecondPlayerScore->SetLocalPosition({ 5, 175, 0 });

				//Second player
				auto goSecondPlayer = scene.CreateGameObject();
				goSecondPlayer->AddComponent<RenderComponent>("textures/penguinDown.png");
				goSecondPlayer->AddComponent<MovementComponent>(200.f);
				goSecondPlayer->AddComponent<PlayerComponent>();
				goSecondPlayer->AddComponent<HealthSubjectComponent>()->AddObserver(healthObserver);
				goSecondPlayer->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver);
				goSecondPlayer->SetLocalPosition({ x * tileSize, y * tileSize + 200, 0 });

				//Add input commands
				daeEngine::KeyboardInput* keyboard = dae::InputManager::GetInstance().GetKeyboard();
				keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_W, std::make_shared<MovementCommand>(goSecondPlayer, glm::vec3(0, -1, 0)));
				keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_S, std::make_shared<MovementCommand>(goSecondPlayer, glm::vec3(0, 1, 0)));
				keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_A, std::make_shared<MovementCommand>(goSecondPlayer, glm::vec3(-1, 0, 0)));
				keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_D, std::make_shared<MovementCommand>(goSecondPlayer, glm::vec3(1, 0, 0)));
				keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_W, std::make_shared<MovementCommand>(goSecondPlayer, glm::vec3(0, 0, 0)));
				keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_S, std::make_shared<MovementCommand>(goSecondPlayer, glm::vec3(0, 0, 0)));
				keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_A, std::make_shared<MovementCommand>(goSecondPlayer, glm::vec3(0, 0, 0)));
				keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_D, std::make_shared<MovementCommand>(goSecondPlayer, glm::vec3(0, 0, 0)));
				keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_C, std::make_shared<DamageCommand>(goSecondPlayer));
				keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_Z, std::make_shared<IncreaseScoreCommand>(goSecondPlayer, 10));
				keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_X, std::make_shared<IncreaseScoreCommand>(goSecondPlayer, 100));
			}
		}
	}

	//Logo
	auto goLogo = scene.CreateGameObject();
	goLogo->AddComponent<RenderComponent>("logo.tga");
	goLogo->SetLocalPosition({ 216, 180, 0 });

	//Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto goText = scene.CreateGameObject();
	goText->AddComponent<TextComponent>("Programming 4 Assignment", font);
	goText->SetLocalPosition({ 80, 20, 0 });

	//FPS counter
	auto goFPS = scene.CreateGameObject();
	goFPS->AddComponent<FPSComponent>();

	//Set new font for text
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	//Button info
	auto goButtonInfoController = scene.CreateGameObject();
	goButtonInfoController->AddComponent<TextComponent>("Use the D-Pad to move the left Pengo, X to inflict damage, A and B to get points", font);
	goButtonInfoController->SetLocalPosition({ 5, 75, 0 });

	auto goButtonInfoKeyboard = scene.CreateGameObject();
	goButtonInfoKeyboard->AddComponent<TextComponent>("Use the WASD to move the right Pengo, C to inflict damage, Z and X to get points", font);
	goButtonInfoKeyboard->SetLocalPosition({ 5, 90, 0 });

	auto goInfo = scene.CreateGameObject();
	goInfo->AddComponent<TextComponent>("When taking damage a sound plays", font);
	goInfo->SetLocalPosition({ 5, 105, 0 });

	////Render imgui graphs
	//go = std::make_shared<dae::GameObject>();
	//go->AddComponent<GraphComponent>();
	//scene.CreateGameObject(go);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}