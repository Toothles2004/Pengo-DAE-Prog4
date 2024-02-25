#pragma once
#include <SDL_ttf.h>
#include <stdexcept>

#include "BasicComponent.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Font.h"
#include "Texture2D.h"

class TextComponent : public BasicComponent
{
public:
	explicit TextComponent(dae::GameObject* owner);
	explicit TextComponent(dae::GameObject* owner, const std::string& text);
	explicit TextComponent(dae::GameObject* owner, const std::string& text, const std::shared_ptr<dae::Font>& font);


	void Update() override;

	void SetText(const std::string& text);
	void SetText(const std::string& text, const std::shared_ptr<dae::Font>& font);

	void SetColor(SDL_Color newColor) { m_Color = newColor; m_needsUpdate = true; }

private:
	bool m_needsUpdate{ true };
	std::string m_text;
	std::shared_ptr<dae::Font> m_font;
	std::shared_ptr<dae::Texture2D> m_textTexture;
	SDL_Color m_Color = { 255,255,255 };

};

