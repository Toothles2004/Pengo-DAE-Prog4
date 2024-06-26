#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "FPSComponent.h"
#include "GraphComponent.h"
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
#include "GameState.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "CollisionObserverComponent.h"
#include "CollisionSubjectComponent.h"
#include "IceCubeComponent.h"

enum class EnemyColor
{
	green,
	red,
	yellow
};

void LoadLevel(const std::string& levelName, EnemyColor enemyColor, const float scale,  const int tileSize, const glm::vec2 offset)
{
	std::string levelDataPath{ "..\\Data\\levels\\" };
	levelDataPath += levelName + ".txt";
	std::string characterPath{ "textures/character.png" };
	std::string blockPath{ "textures/blocks.png" };
	glm::vec2 characterFrameCount{40, 18};
	glm::vec2 player2FramePos{ 0,0 };
	glm::vec2 blockImageFrameCount{ 9, 4 };
	glm::vec2 iceBlockFramePos{ 0, 0 };
	glm::vec2 backgroundFramePos{ 0, 0 };
	glm::vec2 backgroundFrameCount{ 2, 1 };
	glm::vec2 diamondFramePos{ 0, 1 };
	glm::vec2 eggFramePos{};
	glm::vec2 enemyFramePos{};

	switch (enemyColor)
	{
		case EnemyColor::green:
			eggFramePos = { 1, 0 };
			enemyFramePos = { 0, 9 };
			break;
		case EnemyColor::red:
			eggFramePos = { 2, 0 };
			enemyFramePos = { 8, 9 };
			break;
		case EnemyColor::yellow:
			eggFramePos = { 3, 0 };
			enemyFramePos = { 16, 9 };
			break;
	}

	auto& scene = dae::SceneManager::GetInstance().CreateScene(levelName);
	auto& gameInstance = daeEngine::GameState::GetInstance();

	auto& soundService = daeEngine::SoundServiceLocator::GetSoundService();
	soundService.PlaySound(0, 0, 10, -1);

	//background
	auto goBackground = scene.CreateGameObject();
	goBackground->AddComponent<RenderComponent>("textures/level.png", backgroundFramePos, backgroundFrameCount);
	goBackground->SetLocalPosition({ offset.x - static_cast<float>(tileSize / 2.f), offset.y - static_cast<float>(tileSize / 2.f), 0 });
	goBackground->SetLocalScale({ scale, scale, 1.f });

	auto goCollisionManager = scene.CreateGameObject();
	goCollisionManager->AddComponent<CollisionSubjectComponent>();

	std::vector<std::vector<int>> levelLayout = dae::SceneManager::GetInstance().ReadLevelLayoutFromFile(levelDataPath);

	// Iterate over the layout to create game objects
	for (size_t y{}; y < levelLayout.size(); ++y)
	{
		for (size_t x{}; x < levelLayout[y].size(); ++x)
		{
			int objectType = levelLayout[y][x];
			if (objectType == 0)
			{
				continue;
			}
			if (objectType == 1)
			{
				auto iceBlock = scene.CreateGameObject();
				iceBlock->AddComponent<RenderComponent>(blockPath, iceBlockFramePos, blockImageFrameCount);
				iceBlock->AddComponent<MovementComponent>(250.f, tileSize, offset);
				iceBlock->AddComponent<IceCubeComponent>();
				auto collisionObserver = iceBlock->AddComponent<CollisionObserverComponent>();
				goCollisionManager->GetComponent<CollisionSubjectComponent>()->AddObserver(collisionObserver);
				iceBlock->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
				iceBlock->SetLocalScale({ scale, scale, 1.f });
				continue;
			}
			if (objectType == 2)
			{
				auto egg = scene.CreateGameObject();
				egg->AddComponent<RenderComponent>(blockPath, eggFramePos, blockImageFrameCount);
				auto collisionObserver = egg->AddComponent<CollisionObserverComponent>();
				goCollisionManager->GetComponent<CollisionSubjectComponent>()->AddObserver(collisionObserver);
				egg->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
				egg->SetLocalScale({ scale, scale, 1.f });
				continue;
			}
			if (objectType == 3)
			{
				auto snoBee = scene.CreateGameObject();
				snoBee->AddComponent<RenderComponent>(characterPath, enemyFramePos, characterFrameCount);
				auto collisionObserver = snoBee->AddComponent<CollisionObserverComponent>();
				goCollisionManager->GetComponent<CollisionSubjectComponent>()->AddObserver(collisionObserver);
				snoBee->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
				snoBee->SetLocalScale({ scale, scale, 1.f });
				continue;
			}
			if (objectType == 4)
			{
				auto diamond = scene.CreateGameObject();
				diamond->AddComponent<RenderComponent>(blockPath, diamondFramePos, blockImageFrameCount);
				auto collisionObserver = diamond->AddComponent<CollisionObserverComponent>();
				goCollisionManager->GetComponent<CollisionSubjectComponent>()->AddObserver(collisionObserver);
				diamond->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
				diamond->SetLocalScale({ scale, scale, 1.f });
				continue;
			}
			if (objectType == 5)
			{
				//Player
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
				goFirstPlayer->SetLocalScale({ 2.f, 2.f, 1.f });

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
				std::string healthDisplayText = "# Lives: ";
				healthDisplayText += std::to_string(gameInstance.secondPlayerHealth);
				goSecondPlayerDisplay->AddComponent<TextComponent>(healthDisplayText, font);
				auto healthObserver = goSecondPlayerDisplay->AddComponent<HealthDisplayObserverComponent>();
				goSecondPlayerDisplay->SetLocalPosition({ 5, 160, 0 });

				//Second player score
				auto goSecondPlayerScore = scene.CreateGameObject();
				std::string scoreDisplayText = "Score: ";
				scoreDisplayText += std::to_string(gameInstance.secondPlayerScore);
				goSecondPlayerScore->AddComponent<TextComponent>(scoreDisplayText, font);
				auto scoreObserver = goSecondPlayerScore->AddComponent<ScoreDisplayObserverComponent>();
				goSecondPlayerScore->SetLocalPosition({ 5, 175, 0 });

				//Second player
				auto goSecondPlayer = scene.CreateGameObject();
				goSecondPlayer->AddComponent<RenderComponent>(characterPath, player2FramePos, characterFrameCount);
				goSecondPlayer->AddComponent<MovementComponent>(200.f, tileSize, offset);
				goSecondPlayer->AddComponent<PlayerComponent>();
				goSecondPlayer->AddComponent<HealthSubjectComponent>(gameInstance.secondPlayerHealth)->AddObserver(healthObserver);
				goSecondPlayer->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver);
				auto collisionObserver = goSecondPlayer->AddComponent<CollisionObserverComponent>();
				goCollisionManager->GetComponent<CollisionSubjectComponent>()->AddObserver(collisionObserver);
				goSecondPlayer->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
				goSecondPlayer->SetLocalScale({ scale, scale, 1.f });

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
}

void load()
{
	/*auto& scene = dae::SceneManager::GetInstance().CreateScene("menu");
	dae::SceneManager::GetInstance().SetActiveScene("menu");*/
	auto& gameInstance = daeEngine::GameState::GetInstance();

	float scale{ 1.5 };
	const int tileSize{ static_cast<int>(16*scale) };
	const glm::vec2 offset{ tileSize / 2 + 150, tileSize / 2 + 50 };
	gameInstance.firstPlayerHealth = 4;
	gameInstance.secondPlayerHealth = 4;
	gameInstance.firstPlayerScore = 0;
	gameInstance.secondPlayerScore = 0;

	//load levels
	LoadLevel("level1", EnemyColor::green, scale, tileSize, offset);
	/*LoadLevel("level2", EnemyColor::red, scale, tileSize, offset);
	LoadLevel("level3", EnemyColor::yellow, scale, tileSize, offset);*/

	//sound
	int amountOfChannels{ 2 };
	daeEngine::SoundServiceLocator::RegisterSoundService(std::make_unique<daeEngine::SDLSoundService>(amountOfChannels));
	auto& soundService = daeEngine::SoundServiceLocator::GetSoundService();
	soundService.LoadSound("..\\Data\\sounds\\mainBGM.mp3", 0);
	soundService.LoadSound("..\\Data\\sounds\\miss.mp3", 1);
	soundService.PlaySound(0, 0, 10, -1);

	dae::SceneManager::GetInstance().SetActiveScene("level1");

	/*//Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto goText = scene.CreateGameObject();
	goText->AddComponent<TextComponent>("Programming 4 Assignment", font);
	goText->SetLocalPosition({ 80, 20, 0 });

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
	goInfo->SetLocalPosition({ 5, 105, 0 });*/

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