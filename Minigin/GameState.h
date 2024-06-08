#pragma once
#include "Singleton.h"

namespace daeEngine
{
    class GameState final : public dae::Singleton<GameState>
    {
    public:
        static GameState& GetInstance()
        {
            static GameState instance;
            return instance;
        }

        static int firstPlayerHealth;
        static int secondPlayerHealth;

        static int firstPlayerScore;
        static int secondPlayerScore;

        static int highScore;
    };
}
