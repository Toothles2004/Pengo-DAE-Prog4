#include "LevelManager.h"
#include "SceneManager.h"
#include "RenderComponent.h"
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

#include <iostream>
#include <fstream>
#include <sstream>

LevelManager::LevelManager()
{
}

void LevelManager::LoadLevel(const std::string& filename)
{
    UnloadCurrentLevel();
    LoadLevelLayout(filename);
}

void LevelManager::UnloadCurrentLevel()
{
    auto& scene = dae::SceneManager::GetInstance().GetCurrentScene();
    scene.Clear();
}

void LevelManager::NextLevel()
{
    m_CurrentLevelIndex++;
    if (m_CurrentLevelIndex < m_Levels.size())
    {
        LoadLevel(m_Levels[m_CurrentLevelIndex]);
    }
}

void LevelManager::LoadLevelLayout(const std::string& filename)
{
    auto& scene = dae::SceneManager::GetInstance().GetCurrentScene();
    float scale{ 1.5 };
    const int tileSize{ static_cast<int>(16 * scale) };
    const glm::vec2 offset{ tileSize / 2 + 150, tileSize / 2 + 50 };

    std::vector<std::vector<int>> levelLayout = ReadLevelLayoutFromFile(filename);

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
                iceBlock->AddComponent<RenderComponent>("textures/blocks.png", glm::vec2{ 0, 0 }, glm::vec2{ 9, 4 });
                iceBlock->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
                iceBlock->SetLocalScale({ scale, scale, 1.f });
                continue;
            }
            if (objectType == 2)
            {
                auto egg = scene.CreateGameObject();
                egg->AddComponent<RenderComponent>("textures/blocks.png", glm::vec2{ 1, 0 }, glm::vec2{ 9, 4 });
                egg->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
                egg->SetLocalScale({ scale, scale, 1.f });
                continue;
            }
            if (objectType == 3)
            {
                auto snoBee = scene.CreateGameObject();
                snoBee->AddComponent<RenderComponent>("textures/snoBee1.png");
                snoBee->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
                snoBee->SetLocalScale({ scale, scale, 1.f });
                continue;
            }
            if (objectType == 4)
            {
                auto diamond = scene.CreateGameObject();
                diamond->AddComponent<RenderComponent>("textures/blocks.png", glm::vec2{ 0, 2 }, glm::vec2{ 9, 4 });
                diamond->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
                diamond->SetLocalScale({ scale, scale, 1.f });
                continue;
            }
            if (objectType == 5)
            {
                auto goPlayer = scene.CreateGameObject();
                goPlayer->AddComponent<RenderComponent>("textures/penguinDown.png");
                goPlayer->AddComponent<MovementComponent>(200.f);
                goPlayer->AddComponent<PlayerComponent>();
                goPlayer->SetLocalPosition({ x * tileSize + offset.x, y * tileSize + offset.y, 0 });
                goPlayer->SetLocalScale({ scale, scale, 1.f });
            }
        }
    }
}