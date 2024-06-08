#include "IceCubeIdleState.h"

#include <glm/detail/func_geometric.inl>

#include "IceCubeBreakingState.h"
#include "IceCubeMovingState.h"
#include "RenderComponent.h"

std::unique_ptr<IceCubeState> IceCubeIdleState::HandleInput(glm::vec3 direction)
{
	if (abs(normalize(direction).x) >= 0.01f || abs(normalize(direction).y) >= 0.01f)
	{
		/*if()
		{
			auto state = std::make_unique<IceCubeBreakingState>();
			return state;
		
		}*/
		auto state = std::make_unique<IceCubeMovingState>();
		return state;
	}

	auto state = std::make_unique<IceCubeIdleState>();
	return state;
}
