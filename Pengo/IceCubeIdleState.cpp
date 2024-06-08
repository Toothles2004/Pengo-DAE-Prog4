#include "IceCubeIdleState.h"

#include <glm/detail/func_geometric.inl>

#include "BasicComponent.h"
#include "BasicComponent.h"
#include "IceCubeBreakingState.h"
#include "IceCubeMovingState.h"
#include "RenderComponent.h"

::IceCubeState* IceCubeIdleState::HandleInput(glm::vec3 direction)
{
	if (abs(normalize(direction).x) >= 0.01f || abs(normalize(direction).y) >= 0.01f)
	{
		/*if()
		{
			auto state = std::make_unique<IceCubeBreakingState>();
			return state;
		
		}*/
		IceCubeMovingState* state = new IceCubeMovingState();
		return state;
	}

	const auto state = this;
	return state;
}
