#pragma once
#include <any>
#include <unordered_map>

namespace daeEngine
{
	class Observer
	{
	public:
		Observer() = default;
		virtual void OnNotify(std::unordered_map<std::string, std::any>& data, std::string& event) = 0;

		virtual ~Observer() = default;
		Observer(const Observer& other) = delete;
		Observer(Observer&& other) = delete;
		Observer& operator=(const Observer& other) = delete;
		Observer& operator=(Observer&& other) = delete;
	};
}


