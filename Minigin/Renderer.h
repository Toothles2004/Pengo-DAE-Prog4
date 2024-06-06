#pragma once
#include <SDL.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_Renderer{};
		SDL_Window* m_Window{};
		SDL_Color m_ClearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, const float x, const float y) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const float angle, glm::vec3 scale) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const float angle, const glm::vec3 scale, const glm::vec2 positionInImage, const glm::vec2 framesInImage) const;
		void RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, const float angle, glm::vec3 scale) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }
	};
}

