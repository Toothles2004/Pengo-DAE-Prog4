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

		void Notify(std::string& event)
		{
			for (Observer* observer : m_pObservers)
			{
				observer->OnNotify(m_pData, event);
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
