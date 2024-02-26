#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "FPSComponent.h"
#include "Minigin.h"
#include "RenderComponent.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
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
	auto transform = go->AddComponent<TransformComponent>();
	go->AddComponent<RenderComponent>("logo.tga");
	transform->SetPosition({ 216, 180, 0 });
	scene.Add(go);

	//Text
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<dae::GameObject>();
	transform = go->AddComponent<TransformComponent>();
	go->AddComponent<TextComponent>("Programming 4 Assignment", font);
	transform->SetPosition({ 80, 20, 0 });
	scene.Add(go);

	//FPS counter
	go = std::make_shared<dae::GameObject>();
	transform = go->AddComponent<TransformComponent>();
	go->AddComponent<FPSComponent>();
	scene.Add(go);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}