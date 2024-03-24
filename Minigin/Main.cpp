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
#include "MovementCommand.h"
#include "MovementComponent.h"

void load()
{

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Programming 4 assignment");

	//Background
	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>("background.tga");
	scene.Add(go);

	//Logo
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<RenderComponent>("logo.tga");
	go->SetLocalPosition({ 216, 180, 0 });
	scene.Add(go);

	//Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	go->SetLocalPosition({ 80, 20, 0 });
	scene.Add(go);

	//FPS counter
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<FPSComponent>();
	scene.Add(go);

	//Controller + keyboard movement
	//penguin
	auto goPenguin = std::make_shared<dae::GameObject>();
	goPenguin->AddComponent<RenderComponent>("textures/penguin.png");
	goPenguin->AddComponent<MovementComponent>(100.f);
	goPenguin->SetLocalPosition({ 100, 250, 0 });
	scene.Add(goPenguin);

	//enemy
	auto goEnemy = std::make_shared<dae::GameObject>();
	goEnemy->AddComponent<RenderComponent>("textures/enemy.png");
	goEnemy->AddComponent<MovementComponent>(200.f);
	goEnemy->SetLocalPosition({ 130, 250, 0 });
	scene.Add(goEnemy);

	//Add input commands
	auto& manager = dae::InputManager::GetInstance();
	daeEngine::ControllerInput* controller = new daeEngine::ControllerInput(0);
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadUp, std::make_shared<MovementCommand>(goPenguin.get(), glm::vec3(0, -1, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadDown, std::make_shared<MovementCommand>(goPenguin.get(), glm::vec3(0, 1, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadLeft, std::make_shared<MovementCommand>(goPenguin.get(), glm::vec3(-1, 0, 0)));
	controller->AddKeyBind(daeEngine::ButtonState::pressed, daeEngine::ControllerButton::dPadRight, std::make_shared<MovementCommand>(goPenguin.get(), glm::vec3(1, 0, 0)));
	manager.AddController(controller);

	daeEngine::KeyboardInput* keyboard = manager.GetKeyboard();
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_W, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, -1, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_S, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, 1, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_A, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(-1, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_D, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(1, 0, 0)));

	////Render imgui graphs
	//go = std::make_shared<dae::GameObject>();
	//go->AddComponent<GraphComponent>();
	//scene.Add(go);

	////Characters orbiting
	////Empty object (center of orbit)
	//auto goEmpty = std::make_shared<dae::GameObject>();
	//goEmpty->SetLocalPosition({ 100, 250, 0 });
	//scene.Add(goEmpty);

	////penguin
	//auto goPenguin = std::make_shared<dae::GameObject>();
	//goPenguin->SetParent(goEmpty.get(), false);
	//goPenguin->AddComponent<RenderComponent>("textures/penguin.png");
	//goPenguin->AddComponent<RotatorComponent>(20.f, -10.f);
	//scene.Add(goPenguin);

	////enemy
	//go = std::make_shared<dae::GameObject>();
	//go->SetParent(goPenguin.get(), false);
	//go->AddComponent<RenderComponent>("textures/enemy.png");
	//go->AddComponent<RotatorComponent>(30.f, 7.f);
	//scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}