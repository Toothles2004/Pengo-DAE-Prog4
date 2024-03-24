#include "Subject.h"

namespace daeEngine
{
	void Subject::AddObserver(Observer* observer)
	{
		m_pObservers.emplace_back(observer);
	}

	void Subject::RemoveObserver(Observer* observer)
	{
		m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer));
	}
}