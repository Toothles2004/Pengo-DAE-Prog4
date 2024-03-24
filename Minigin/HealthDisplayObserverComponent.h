#pragma once
#include "BasicComponent.h"
#include "Observer.h"

class TextComponent;
class HealthSubjectComponent;
class HealthDisplayObserverComponent: public daeEngine::Observer, public daeEngine::BasicComponent
{
public:
	explicit HealthDisplayObserverComponent(dae::GameObject* owner);

	void OnNotify(std::unordered_map<std::string, std::any>& data, std::string& event) override;

private:
	void SetHealthDisplay(int health) const;
	TextComponent* m_pTextComponent;
};

