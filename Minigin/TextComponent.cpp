#include "TextComponent.h"

TextComponent::TextComponent(dae::GameObject* owner)
	: BasicComponent(owner)
{
	m_font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
}

TextComponent::TextComponent(dae::GameObject* owner, const std::string& text)
	: BasicComponent(owner)
{
	SetText(text);
}

TextComponent::TextComponent(dae::GameObject* owner, const std::string& text, const std::shared_ptr<dae::Font>& font)
	: BasicComponent(owner)
{
	SetText(text, font);
}

void TextComponent::Update()
{
	if (m_needsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
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
		m_textTexture = std::make_shared<dae::Texture2D>(texture);

		if (m_pOwner != nullptr)
		{

			if (const auto sharedPtr = m_pOwner->GetComponent<RenderComponent>().lock()) {
				sharedPtr->SetTexture(m_textTexture);
			}
			m_needsUpdate = false;
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
	m_text = text;
	m_font = font;
	m_needsUpdate = true;
	if (m_pOwner != nullptr)
	{
		if (m_pOwner->HasComponent<RenderComponent>() == false)
		{
			m_pOwner->AddComponent<RenderComponent>();
		}
	}
}
