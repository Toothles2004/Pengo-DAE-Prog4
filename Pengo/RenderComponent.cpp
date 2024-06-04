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
    float angle{};
    glm::vec3 scale { 1.f, 1.f, 1.f };
    position = m_pOwner->GetWorldTransform().position;
    angle = m_pOwner->GetWorldTransform().rotation;
    scale = m_pOwner->GetWorldTransform().scale;
    dae::Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y, angle, scale);
}
