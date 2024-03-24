#pragma once
#include <string>

#include "Observer.h"

namespace daeEngine
{
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

		template <typename TEvent>
		void Notify(TEvent event)
		{
			static_assert(std::is_enum<TEvent>::value, "TEvent must be an enum");
			for (Observer* observer : m_pObservers)
			{
				observer->OnNotify(event, m_pData);
			}
		}

		Subject() = default;
		virtual ~Subject() = default;
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

	protected:
		std::unordered_map<std::string, std::any> m_pData{};

	private:
		std::vector<Observer*> m_pObservers{};
	};
}
