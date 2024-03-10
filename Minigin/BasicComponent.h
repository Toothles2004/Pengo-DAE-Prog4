#pragma once

#include "GameObject.h"
#include "GameTime.h"

class BasicComponent
{
public:
	virtual void Update(){}
	virtual void FixedUpdate(){}
	virtual void LateUpdate(){}
	virtual void Render() const {}
	virtual void RenderImgui() {}

	explicit BasicComponent(dae::GameObject* owner);
	virtual ~BasicComponent() = default;
	BasicComponent(const BasicComponent& other) = delete;
	BasicComponent(BasicComponent&& other) = delete;
	BasicComponent& operator=(const BasicComponent& other) = delete;
	BasicComponent& operator=(BasicComponent&& other) = delete;

protected:
	dae::GameObject* m_pOwner;
};

