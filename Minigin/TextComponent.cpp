#include "TextComponent.h"

TextComponent::TextComponent(dae::GameObject* owner)
	: BasicComponent(owner)
{
	m_Font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	if(owner->HasComponent<RenderComponent>() == false)
	{
		owner->AddComponent<RenderComponent>();
	}

	m_pRenderComponent = owner->GetComponent<RenderComponent>();
}

TextComponent::TextComponent(dae::GameObject* owner, const std::string& text)
	: TextComponent(owner)
{
	SetText(text);
}

TextComponent::TextComponent(dae::GameObject* owner, const std::string& text, const std::shared_ptr<dae::Font>& font)
	: TextComponent(owner)
{
	SetText(text, font);
}

void TextComponent::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_TextTexture = std::make_shared<dae::Texture2D>(texture);

		if (m_pOwner != nullptr)
		{
			m_pRenderComponent->SetTexture(m_TextTexture);
			m_NeedsUpdate = false;
		}
	}
}

void TextComponent::SetText(const std::string& text)
{
	const auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	SetText(text, font);
}

void TextComponent::SetText(const std::string& text, const std::shared_ptr<dae::Font>& font)
{
	m_Text = text;
	m_Font = font;
	m_NeedsUpdate = true;
	if (m_pOwner != nullptr)
	{
		if (m_pOwner->HasComponent<RenderComponent>() == false)
		{
			m_pOwner->AddComponent<RenderComponent>();
		}
	}
}
