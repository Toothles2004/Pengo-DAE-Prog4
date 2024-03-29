#include "RenderComponent.h"
#include "Renderer.h"

RenderComponent::RenderComponent(dae::GameObject* owner)
    : BasicComponent(owner)
{
}

RenderComponent::RenderComponent(dae::GameObject* owner, const std::shared_ptr<dae::Texture2D>& texture)
    : RenderComponent(owner)
{
    SetTexture(texture);
}

RenderComponent::RenderComponent(dae::GameObject* owner, const std::string& texture)
    : RenderComponent(owner)
{
    SetTexture(texture);
}

void RenderComponent::Render() const
{
    glm::vec3 position{ 0,0,0 };
    position = m_pOwner->GetWorldPosition();
    dae::Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y);
}
