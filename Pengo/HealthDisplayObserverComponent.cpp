#include "HealthDisplayObserverComponent.h"
#include "TextComponent.h"
#include "HealthSubjectComponent.h"
#include "SoundServiceLocator.h"

HealthDisplayObserverComponent::HealthDisplayObserverComponent(dae::GameObject* owner)
	: BasicComponent(owner)
{
    if (owner->HasComponent<TextComponent>() == false)
    {
        owner->AddComponent<TextComponent>();
    }
    m_pTextComponent = m_pOwner->GetComponent<TextComponent>();
}

void HealthDisplayObserverComponent::OnNotify(std::unordered_map<std::string, std::any>& data, std::string& event)
{
	if (event == "Damaged")
	{
		auto iter = data.find("Health");
		if (iter != data.end()) {
			SetHealthDisplay(std::any_cast<int>(iter->second));
		}
		auto& soundService = daeEngine::SoundServiceLocator::GetSoundService();
		soundService.LoadSound("..\\Data\\sounds\\Miss.mp3", 1);
		soundService.PlaySound(1, 1, 20, 0);
	}
	else if (event == "Died")
	{
		const std::string text = "# Lives: 0  Player died";
		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
		m_pTextComponent->SetText(text, font);
	}
}

void HealthDisplayObserverComponent::SetHealthDisplay(int health) const
{
	const std::string text = "# Lives: " + std::to_string(health);
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	m_pTextComponent->SetText(text, font);
}
