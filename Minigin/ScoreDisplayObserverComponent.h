#pragma once
#include "BasicComponent.h"
#include "Observer.h"

class TextComponent;
class ScoreDisplayObserverComponent : public daeEngine::Observer, public daeEngine::BasicComponent
{
public:
	explicit ScoreDisplayObserverComponent(dae::GameObject* owner);

	void OnNotify(std::unordered_map<std::string, std::any>& data, std::string& event) override;

private:
	void SetScoreDisplay(int score) const;
	TextComponent* m_pTextComponent;
};

