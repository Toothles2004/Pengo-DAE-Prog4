#include "RenderComponent.h"

RenderComponent::RenderComponent(dae::GameObject* owner)
    : BasicComponent(owner)
{
    m_TransformComponent = owner->GetComponent<TransformComponent>();
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
    if (auto sharedPtr = m_TransformComponent.lock()) //Lock converts weak_ptr into shared_ptr
    {
        position = sharedPtr->GetPosition(); //Call through shared_ptr
    }
    dae::Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y);
}
