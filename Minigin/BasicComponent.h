#pragma once

namespace dae
{
	class GameObject;
}

class BasicComponent
{
public:
	virtual void Update(){}
	virtual void FixedUpdate(){}
	virtual void LateUpdate(){}
	virtual void Render() const {}

	explicit BasicComponent(dae::GameObject* owner);
	virtual ~BasicComponent() = default;
	BasicComponent(const BasicComponent& other) = delete;
	BasicComponent(BasicComponent&& other) = delete;
	BasicComponent& operator=(const BasicComponent& other) = delete;
	BasicComponent& operator=(BasicComponent&& other) = delete;

private:
	dae::GameObject* m_pOwner;
};

