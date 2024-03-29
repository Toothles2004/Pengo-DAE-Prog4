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

#define USING_STEAM
#ifdef USING_STEAM

#pragma warning (push)
#pragma warning (disable: 4996)
#include "steam_api.h"
#pragma warning (pop)

#pragma warning(push)
#pragma warning (disable: 4389)
#pragma warning (disable: 26495)
#pragma warning (disable: 6053)
#include "CSteamAchievements.h"
#pragma warning (pop)

CSteamAchievements* g_SteamAchievements = nullptr;

#endif // USING_STEAM

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

	//Set new font for text
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	//button info
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("Use the D-Pad to move Pengo, X to inflict damage, A and B to get points", font);
	go->SetLocalPosition({ 5, 75, 0 });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("Use the WASD to move the ice bear, C to inflict damage, Z and X to get points", font);
	go->SetLocalPosition({ 5, 90, 0 });
	scene.Add(go);

	//Penguin display
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("# Lives: 3", font);
	auto healthObserver = go->AddComponent<HealthDisplayObserverComponent>();
	go->SetLocalPosition({ 5, 130, 0 });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("Score: 0", font);
	auto scoreObserver = go->AddComponent<ScoreDisplayObserverComponent>();
#ifdef USING_STEAM
	scoreObserver->SetSteamAchievements(g_SteamAchievements);
#endif
	go->SetLocalPosition({ 5, 145, 0 });
	scene.Add(go);

	//penguin
	auto goPenguin = std::make_shared<dae::GameObject>();
	goPenguin->AddComponent<RenderComponent>("textures/penguin.png");
	goPenguin->AddComponent<MovementComponent>(100.f);
	goPenguin->AddComponent<HealthSubjectComponent>()->AddObserver(healthObserver.get());
	goPenguin->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver.get());
	goPenguin->SetLocalPosition({ 100, 250, 0 });
	scene.Add(goPenguin);

	//Enemy display
	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("# Lives: 3", font);
	healthObserver = go->AddComponent<HealthDisplayObserverComponent>();
	go->SetLocalPosition({ 5, 160, 0 });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<TextComponent>("Score: 0", font);
	scoreObserver = go->AddComponent<ScoreDisplayObserverComponent>();
#ifdef USING_STEAM
	scoreObserver->SetSteamAchievements(g_SteamAchievements);
#endif
	go->SetLocalPosition({ 5, 175, 0 });
	scene.Add(go);

	//enemy
	auto goEnemy = std::make_shared<dae::GameObject>();
	goEnemy->AddComponent<RenderComponent>("textures/enemy.png");
	goEnemy->AddComponent<MovementComponent>(200.f);
	goEnemy->AddComponent<HealthSubjectComponent>()->AddObserver(healthObserver.get());
	goEnemy->AddComponent<ScoreSubjectComponent>()->AddObserver(scoreObserver.get());
	goEnemy->SetLocalPosition({ 130, 250, 0 });
	scene.Add(goEnemy);

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

	daeEngine::KeyboardInput* keyboard = manager.GetKeyboard();
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_W, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, -1, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_S, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(0, 1, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_A, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(-1, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::pressed, SDL_SCANCODE_D, std::make_shared<MovementCommand>(goEnemy.get(), glm::vec3(1, 0, 0)));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_C, std::make_shared<DamageCommand>(goEnemy.get()));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_Z, std::make_shared<IncreaseScoreCommand>(goEnemy.get(), 10));
	keyboard->AddKeyBind(daeEngine::ButtonState::down, SDL_SCANCODE_X, std::make_shared<IncreaseScoreCommand>(goEnemy.get(), 100));

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

#ifdef USING_STEAM
// Achievement array which will hold data about the achievements and their state
Achievement_t g_Achievements[] =
{
	_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
	_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
	_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
	_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
};
#endif // USING_STEAM

int main(int, char*[]) {

#ifdef USING_STEAM
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Successfully initialized steam." << std::endl;
		g_SteamAchievements = new CSteamAchievements(g_Achievements, 4);
	}
#endif

	dae::Minigin engine("../Data/");
	engine.Run(load);

#ifdef USING_STEAM
	SteamAPI_Shutdown();

	if (g_SteamAchievements)
	{
		delete g_SteamAchievements;
	}
#endif

    return 0;
}