#include <vector>
#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "ItemSet.h"
#include "Utilities.h"

namespace sict {

	size_t CustomerOrder::m_fieldWidth = 0;

	// Default Constructor that sets the object to a safe empty state
	//
	CustomerOrder::CustomerOrder() : m_itemsOrdered{ nullptr },
		m_customerName{ "" },
		m_productName{ "" },
		m_numItems{ 0 } {}

	// One argument constructor that receives a string that contains at least 3 tokens:
	//
	CustomerOrder::CustomerOrder(const std::string& record)
		: CustomerOrder() {
		Utilities utility;

		size_t delimiter_pos = record.find(utility.getDelimiter());
		m_customerName = record.substr(0, delimiter_pos);

		if (m_fieldWidth < utility.getFieldWidth())
			m_fieldWidth = utility.getFieldWidth();

		m_productName = utility.extractToken(record, delimiter_pos);

		m_numItems = std::count(record.begin(), record.end(), utility.getDelimiter()) - 1;
		m_itemsOrdered = new ItemInfo[m_numItems];

		if (m_numItems >= 1) {
			for (size_t i = 0; i < m_numItems; i++)
				m_itemsOrdered[i].s_name = utility.extractToken(record, delimiter_pos);
		}
		else {
			throw "***No items are found***";
		}
	}

	// Move Constructor
	//
	CustomerOrder::CustomerOrder(CustomerOrder&& other) {
		*this = std::move(other);
	}

	// Move assign operator
	//
	CustomerOrder & CustomerOrder::operator=(CustomerOrder&& other) {
		if (this != &other)
		{
			m_customerName = other.m_customerName;
			m_productName = other.m_productName;
			m_numItems = other.m_numItems;
			m_itemsOrdered = other.m_itemsOrdered;

			other.m_itemsOrdered = { nullptr };
		}
		return *this;
	}

	// Destructor 
	// dellocate memories
	//
	CustomerOrder::~CustomerOrder()
	{
		delete[] m_itemsOrdered;
		m_itemsOrdered = { nullptr };
	}

	/*
	 Modifier that receives a reference to an ItemSet object and an std::ostream object.
	 This function checks each item request, fills it if the requested item is available and the request has not been filled, reports the filling
	 in the format shown below and decrements the item stock by one:
		Filled CUSTOMER [PRODUCT][ITEM][SERIAL NUMBER]
	 If the item request has already been filled or if the item is out of stock, this function displays the corresponding message:
		Unable to fill CUSTOMER [PRODUCT][ITEM][SERIAL NUMBER] already filled
		Unable to fill CUSTOMER [PRODUCT][ITEM][SERIAL NUMBER] out of stock
	*/
	void CustomerOrder::fillItem(ItemSet& item, std::ostream& os)
	{
		for (size_t i = 0; i < m_numItems; ++i)
		{
			if (item.getName() == m_itemsOrdered[i].s_name)
			{
				if (item.getQuantity() == 0)
					os << " Unable to fill " << m_customerName << " [" << m_productName << "][" << m_itemsOrdered[i].s_name << "][" << m_itemsOrdered[i].s_serialNumer << "] out of stock" << std::endl;
				else
				{
					if (m_itemsOrdered[i].s_filled)
						os << " Unable to fill " << m_customerName << " [" << m_productName << "][" << m_itemsOrdered[i].s_name << "][" << m_itemsOrdered[i].s_serialNumer << "] already filled" << std::endl;
					else
					{
						m_itemsOrdered[i].s_serialNumer = item.getSerialNumber();
						m_itemsOrdered[i].s_filled = true;
						--item;
						os << " Filled " << m_customerName << " [" << m_productName << "][" << m_itemsOrdered[i].s_name << "][" << m_itemsOrdered[i].s_serialNumer << "]" << std::endl;
					}
				}
			}
		}
	}

	// query that searches the list of items requested and returns true if all have been filled; false otherwise
	//
	bool CustomerOrder::isFilled() const
	{
		for (size_t i = 0; i < m_numItems; ++i)
			if (!m_itemsOrdered[i].s_filled)
				return false;
		return true;
	}

	// a query that receives the name of an item, search the item request list for that item and returns true if all
	//	requests for that item have been filled; false, otherwise.If the item is not in the request list, this function returns true.
	//
	bool CustomerOrder::isItemFilled(const std::string& itemName) const
	{
		for (size_t i = 0; i < m_numItems; ++i)
		{
			if (m_itemsOrdered[i].s_name == itemName)
			{
				if (!m_itemsOrdered[i].s_filled)
					return false;
			}
		}
		return true;
	}

	// query that returns the name of the customer and their product in the following format
	// CUSTOMER [PRODUCT]
	//
	std::string CustomerOrder::getNameProduct() const
	{
		return std::string(m_customerName) + "[" + std::string(m_productName) + "]";
	}

	/*
	 a query that receives a reference to an std::ostream object os and a Boolean showDetail and inserts
	 the data for the current object into stream os. If the Boolean is false the data consists of
	 the name of the customer, the product being assembled, and the list of items on the order.
	*/
	void CustomerOrder::display(std::ostream & os, bool showDetail) const
	{
		os << std::left << std::setw(m_fieldWidth) << m_customerName << " [" << m_productName << "]" << std::endl;
		if (!showDetail) {
			for (size_t i = 0; i < m_numItems; ++i) {
				os << std::setfill(' ') << std::setw(m_fieldWidth + 1) << "    " << std::right << m_itemsOrdered[i].s_name << std::endl;
			}
		}
		else
		{
			for (size_t i = 0; i < m_numItems; ++i) {
				if (m_itemsOrdered[i].s_filled)
					os << std::setfill(' ') << std::setw(m_fieldWidth + 1) << "    " << "[" << m_itemsOrdered[i].s_serialNumer << "] " << std::right << m_itemsOrdered[i].s_name << " - FILLED" << std::endl;
				else
					os << std::setfill(' ') << std::setw(m_fieldWidth + 1) << "    " << "[" << m_itemsOrdered[i].s_serialNumer << "] " << std::right << m_itemsOrdered[i].s_name << " - MISSING" << std::endl;
			}
		}
	}
}