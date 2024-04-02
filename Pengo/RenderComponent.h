#pragma once
#include <string>

#include "GameObject.h"
#include "ResourceManager.h"
#include "BasicComponent.h"

class RenderComponent : public daeEngine::BasicComponent
{
public:
    explicit RenderComponent(dae::GameObject* owner);
    explicit RenderComponent(dae::GameObject* owner, const std::shared_ptr<dae::Texture2D>& texture);
    explicit RenderComponent(dae::GameObject* owner, const std::string& texture);

    void Render() const override;

    void SetTexture(const std::shared_ptr<dae::Texture2D>& texture) { m_pTexture = texture; }
    void SetTexture(const std::string& filename) { m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filename); }

private:
    std::shared_ptr<dae::Texture2D> m_pTexture;
};

