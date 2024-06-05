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
//#include "Command.h"
#include <iostream>

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

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Programming 4 assignment");

	int amountOfChannels{ 2 };
	daeEngine::SoundServiceLocator::RegisterSoundService(std::make_unique<daeEngine::SDLSoundService>(amountOfChannels));
	auto& soundService = daeEngine::SoundServiceLocator::GetSoundService();
	soundService.LoadSound("..\\Data\\sounds\\mainBGM.mp3", 0);
	soundService.PlaySound(0, 0, 10, -1);

	//Background
	auto goBackground = scene.CreateGameObject();
	goBackground->AddComponent<RenderComponent>("background.tga");

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

	//Penguin display
	auto goPenguinDisplay = scene.CreateGameObject();
	goPenguinDisplay->AddComponent<TextComponent>("# Lives: 4", font);
	auto healthObserver = goPenguinDisplay->AddComponent<HealthDisplayObserverComponent>();
	goPenguinDisplay->SetLocalPosition({ 5, 130, 0 });

	auto goPenguinScore = scene.CreateGameObject();
	goPenguinScore->AddComponent<TextComponent>("Score: 0", font);
	auto scoreObserver = goPenguinScore->AddComponent<ScoreDisplayObserverComponent>();
	goPenguinScore->SetLocalPosition({ 5, 145, 0 });

	//Enemy display
	auto goEnemyDisplay = scene.CreateGameObject();
	goEnemyDisplay->AddComponent<TextComponent>("# Lives: 4", font);
	healthObserver = goEnemyDisplay->AddComponent<HealthDisplayObserverComponent>();
	goEnemyDisplay->SetLocalPosition({ 5, 160, 0 });

	auto goEnemyScore = scene.CreateGameObject();
	goEnemyScore->AddComponent<TextComponent>("Score: 0", font);
	scoreObserver = goEnemyScore->AddComponent<ScoreDisplayObserverComponent>();
	goEnemyScore->SetLocalPosition({ 5, 175, 0 });

	//Penguin
	auto goPenguin = scene.CreateGameObject();
	goPenguin->AddComponent<RenderComponent>("textures/penguinDown.png");
	//goPenguin->AddComponent<MovementComponent>(100.f);
	goPenguin->AddComponent<PlayerComponent>();
	goPenguin->AddComponent<HealthSubjectComponent>()->AddObserver(healthObserver);
	goPenguin->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver);
	goPenguin->SetLocalPosition({ 100, 250, 0 });

	//Add input commands
	auto& manager = dae::InputManager::GetInstance();
	daeEngine::ControllerInput* controller = new daeEngine::ControllerInput(0);
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadUp, std::make_shared<MovementCommand>(goPenguin, glm::vec3(0, -1, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadDown, std::make_shared<MovementCommand>(goPenguin, glm::vec3(0, 1, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadLeft, std::make_shared<MovementCommand>(goPenguin, glm::vec3(-1, 0, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadRight, std::make_shared<MovementCommand>(goPenguin, glm::vec3(1, 0, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::x, std::make_shared<DamageCommand>(goPenguin));
	controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::a, std::make_shared<IncreaseScoreCommand>(goPenguin, 10));
	controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::b, std::make_shared<IncreaseScoreCommand>(goPenguin, 100));
	manager.AddController(controller);

	//Enemy
	auto goEnemy = scene.CreateGameObject();
	goEnemy->AddComponent<RenderComponent>("textures/penguinDown.png");
	goEnemy->AddComponent<MovementComponent>(200.f);
	goEnemy->AddComponent<PlayerComponent>();
	goEnemy->AddComponent<HealthSubjectComponent>()->AddObserver(healthObserver);
	goEnemy->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver);
	goEnemy->SetLocalPosition({ 130, 250, 0 });

	//Add input commands
	daeEngine::KeyboardInput* keyboard = manager.GetKeyboard();
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_W, std::make_shared<MovementCommand>(goEnemy, glm::vec3(0, -1, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_S, std::make_shared<MovementCommand>(goEnemy, glm::vec3(0, 1, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_A, std::make_shared<MovementCommand>(goEnemy, glm::vec3(-1, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_D, std::make_shared<MovementCommand>(goEnemy, glm::vec3(1, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_W, std::make_shared<MovementCommand>(goEnemy, glm::vec3(0, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_S, std::make_shared<MovementCommand>(goEnemy, glm::vec3(0, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_A, std::make_shared<MovementCommand>(goEnemy, glm::vec3(0, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_D, std::make_shared<MovementCommand>(goEnemy, glm::vec3(0, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_C, std::make_shared<DamageCommand>(goEnemy));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_Z, std::make_shared<IncreaseScoreCommand>(goEnemy, 10));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_X, std::make_shared<IncreaseScoreCommand>(goEnemy, 100));

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