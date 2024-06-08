#pragma once
#include <string>
#include <vector>

class LevelManager
{
public:
    LevelManager();
    void LoadLevel(const std::string& filename);
    void UnloadCurrentLevel();
    void NextLevel();

    LevelManager(const LevelManager& other) = delete;
    LevelManager(LevelManager&& other) = delete;
    LevelManager& operator=(const LevelManager& other) = delete;
    LevelManager& operator=(LevelManager&& other) = delete;

private:
    std::vector<std::string> m_Levels;
    int m_CurrentLevelIndex{ -1 };
    void LoadLevelLayout(const std::string& filename);
    std::vector<std::vector<int>> ReadLevelLayoutFromFile(const std::string& filename);
};