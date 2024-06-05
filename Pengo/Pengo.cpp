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
	soundService.LoadSound("..\\Data\\sounds\\MainBGM.mp3", 0);
	soundService.PlaySound(0, 0, 10, -1);

	//Background
	auto go = std::make_unique<dae::GameObject>();
	go->AddComponent<RenderComponent>("background.tga");
	scene.Add(std::move(go));

	//Logo
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<RenderComponent>("logo.tga");
	go->SetLocalPosition({ 216, 180, 0 });
	scene.Add(std::move(go));

	//Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	go->SetLocalPosition({ 80, 20, 0 });
	scene.Add(std::move(go));

	//FPS counter
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<FPSComponent>();
	scene.Add(std::move(go));

	//Set new font for text
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	//Button info
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextComponent>("Use the D-Pad to move the left Pengo, X to inflict damage, A and B to get points", font);
	go->SetLocalPosition({ 5, 75, 0 });
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextComponent>("Use the WASD to move the right Pengo, C to inflict damage, Z and X to get points", font);
	go->SetLocalPosition({ 5, 90, 0 });
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextComponent>("When taking damage a sound plays", font);
	go->SetLocalPosition({ 5, 105, 0 });
	scene.Add(std::move(go));

	//Penguin display
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextComponent>("# Lives: 4", font);
	auto healthObserver = go->AddComponent<HealthDisplayObserverComponent>();
	go->SetLocalPosition({ 5, 130, 0 });
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextComponent>("Score: 0", font);
	auto scoreObserver = go->AddComponent<ScoreDisplayObserverComponent>();
	go->SetLocalPosition({ 5, 145, 0 });
	scene.Add(std::move(go));

	//Enemy display
	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextComponent>("# Lives: 4", font);
	healthObserver = go->AddComponent<HealthDisplayObserverComponent>();
	go->SetLocalPosition({ 5, 160, 0 });
	scene.Add(std::move(go));

	go = std::make_unique<dae::GameObject>();
	go->AddComponent<TextComponent>("Score: 0", font);
	scoreObserver = go->AddComponent<ScoreDisplayObserverComponent>();
	go->SetLocalPosition({ 5, 175, 0 });
	scene.Add(std::move(go));

	//Penguin
	auto goPenguin = std::make_unique<dae::GameObject>();
	goPenguin->AddComponent<RenderComponent>("textures/penguinDown.png");
	//goPenguin->AddComponent<MovementComponent>(100.f);
	goPenguin->AddComponent<PlayerComponent>();
	goPenguin->AddComponent<HealthSubjectComponent>()->AddObserver(healthObserver.get());
	goPenguin->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver.get());
	goPenguin->SetLocalPosition({ 100, 250, 0 });

	//Add input commands
	auto& manager = dae::InputManager::GetInstance();
	daeEngine::ControllerInput* controller = new daeEngine::ControllerInput(0);
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadUp, std::make_shared<MovementCommand>(goPenguin.get(), glm::vec3(0, -1, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadDown, std::make_shared<MovementCommand>(goPenguin.get(), glm::vec3(0, 1, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadLeft, std::make_shared<MovementCommand>(goPenguin.get(), glm::vec3(-1, 0, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadRight, std::make_shared<MovementCommand>(goPenguin.get(), glm::vec3(1, 0, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::x, std::make_shared<DamageCommand>(goPenguin.get()));
	controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::a, std::make_shared<IncreaseScoreCommand>(goPenguin.get(), 10));
	controller->AddKeyBind(daeEngine::ButtonState::down, daeEngine::ControllerButton::b, std::make_shared<IncreaseScoreCommand>(goPenguin.get(), 100));
	manager.AddController(controller);
	scene.Add(std::move(goPenguin));

	//Enemy
	auto goEnemy = std::make_unique<dae::GameObject>();
	goEnemy->AddComponent<RenderComponent>("textures/penguinDown.png");
	goEnemy->AddComponent<MovementComponent>(200.f);
	goEnemy->AddComponent<PlayerComponent>();
	goEnemy->AddComponent<HealthSubjectComponent>()->AddObserver(healthObserver.get());
	goEnemy->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver.get());
	goEnemy->SetLocalPosition({ 130, 250, 0 });

	//Add input commands
	daeEngine::KeyboardInput* keyboard = manager.GetKeyboard();
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_W, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, -1, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_S, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, 1, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_A, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(-1, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_D, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(1, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_W, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_S, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_A, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::up, SDL_SCANCODE_D, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_C, std::make_shared<DamageCommand>(goEnemy.get()));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_Z, std::make_shared<IncreaseScoreCommand>(goEnemy.get(), 10));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_X, std::make_shared<IncreaseScoreCommand>(goEnemy.get(), 100));
	scene.Add(std::move(goEnemy));

	////Render imgui graphs
	//go = std::make_shared<dae::GameObject>();
	//go->AddComponent<GraphComponent>();
	//scene.Add(go);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}