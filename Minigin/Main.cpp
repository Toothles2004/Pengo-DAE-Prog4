#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "Minigin.h"
#include "RotatorComponent.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"

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

	//Empty object (center of orbit)
	auto goEmpty = std::make_shared<dae::GameObject>();
	goEmpty->SetLocalPosition({ 100, 250, 0 });
	scene.Add(goEmpty);

	//penguin
	auto goPenguin = std::make_shared<dae::GameObject>();
	goPenguin->SetParent(goEmpty.get(), false);
	goPenguin->AddComponent<RenderComponent>("textures/penguin.png");
	goPenguin->AddComponent<RotatorComponent>(20.f, -10.f);
	scene.Add(goPenguin);

	//enemy
	go = std::make_shared<dae::GameObject>();
	go->SetParent(goPenguin.get(), false);
	go->AddComponent<RenderComponent>("textures/enemy.png");
	go->AddComponent<RotatorComponent>(30.f, 7.f);
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}