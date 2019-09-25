#include "Station.h"
#include "ItemSet.h"

namespace sict
{
	// Receives a reference to an unmodifiable string and passes that reference to the ItemSet sub-object of the current object
	//
	Station::Station(const std::string& string)
		: m_stationInventory(string)
	{
		m_stationName = { m_stationInventory.getName() };
	}

	// displays data for the ItemSet object on os
	//
	void Station::display(std::ostream& os) const {
		m_stationInventory.display(os);
	}

	// fills the last order in the customer order queue (if there is one), if the queue is empty, the function does nothing
	//
	void Station::fill(std::ostream& os) {
		if (!m_stationCustomerOrders.empty())
			m_stationCustomerOrders.front().fillItem(m_stationInventory, os);	// fills only the last order
	}

	// returns a reference to the name of the ItemSet sub-object
	//
	const std::string& Station::getName() const {
		return m_stationInventory.getName();
	}

	// Returns the release state of the current object
	// Return true if the station has filled item requests for the customer order at the front of the queue or the station has no items left
	//
	bool Station::hasAnOrderToRelease() const {
		bool hasOrder = false;
		if (!m_stationCustomerOrders.empty()) {
			if (!m_stationInventory.getQuantity())
				hasOrder = true;
			else
				hasOrder = m_stationCustomerOrders.front().isItemFilled(m_stationName);
		}
		return hasOrder;
	}
	Station& Station::operator--() {
		--m_stationInventory;
		return *this;
	}


	Station& Station::operator+=(CustomerOrder&& order) {
		m_stationCustomerOrders.push_back(std::move(order));
		return *this;
	}

	bool Station::pop(CustomerOrder& ready) {

		bool filled = false;
		if (!m_stationCustomerOrders.empty())
		{
			filled = m_stationCustomerOrders.front().isItemFilled(m_stationName);
			ready = std::move(m_stationCustomerOrders.front());
			m_stationCustomerOrders.erase(m_stationCustomerOrders.begin());
		}
		return filled;
	}

	// A query that reports the state of the ItemSet object
	// 
	void Station::validate(std::ostream & os) const {
		os << " getName(): " << m_stationInventory.getName() << std::endl;
		os << " getSerialNumber(): " << m_stationInventory.getSerialNumber() << std::endl;
		os << " getQuantity(): " << m_stationInventory.getQuantity() << std::endl;
	}
}