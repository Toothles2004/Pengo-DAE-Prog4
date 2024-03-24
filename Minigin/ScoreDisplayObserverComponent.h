#pragma once
#include "BasicComponent.h"
#include "CSteamAchievements.h"
#include "Observer.h"

class TextComponent;
class ScoreDisplayObserverComponent : public daeEngine::Observer, public daeEngine::BasicComponent
{
public:
	explicit ScoreDisplayObserverComponent(dae::GameObject* owner);

	void OnNotify(std::unordered_map<std::string, std::any>& data, std::string& event) override;
	void SetSteamAchievements(CSteamAchievements* steamAchievements)
	{
		m_pSteamAchievement = steamAchievements;
	}

private:
	void SetScoreDisplay(int score) const;
	TextComponent* m_pTextComponent;
	CSteamAchievements* m_pSteamAchievement{nullptr};
};

