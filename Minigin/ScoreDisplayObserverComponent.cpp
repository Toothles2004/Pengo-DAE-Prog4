#include "ScoreDisplayObserverComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"

ScoreDisplayObserverComponent::ScoreDisplayObserverComponent(dae::GameObject* owner)
	: BasicComponent(owner)
{
    if (owner->HasComponent<TextComponent>() == false)
    {
        owner->AddComponent<TextComponent>();
    }
    m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
}

void ScoreDisplayObserverComponent::OnNotify(std::unordered_map<std::string, std::any>& data, std::string& event)
{
    if (event == "GainPoints")
    {
        auto iter = data.find("Score");
        if (iter != data.end()) {
            SetScoreDisplay(std::any_cast<int>(iter->second));
        }
    }
}

void ScoreDisplayObserverComponent::SetScoreDisplay(int score) const
{
    const std::string text = "Score: " + std::to_string(score);
    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
    m_pTextComponent->SetText(text, font);
}
