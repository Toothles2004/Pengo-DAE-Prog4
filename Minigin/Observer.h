#pragma once
#include <any>

#include "GameObject.h"

namespace daeEngine
{
	class Observer
	{
	public:

		template <typename TEvent>
		void OnNotify(std::vector<std::any> data, TEvent event)
		{
			static_assert(std::is_enum<TEvent>::value, "TEvent must be an enum");
		}

		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	};
}


