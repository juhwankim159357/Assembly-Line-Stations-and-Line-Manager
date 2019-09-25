#include <string>
#include <iomanip>
#include "ItemSet.h"
#include "Utilities.h"

namespace sict
{
	// Extracts 4 tokens from the string that is passed and stores tokens in the object
	// 
	ItemSet::ItemSet(const std::string& record) {
		// setting delimiter position
		//
		size_t next_pos = record.find(m_utility.getDelimiter());					// get the position of the first delimiter
		// Getting m_Name from pos to beginning
		//
		m_itemName = record.substr(0, next_pos);

		// Extracting m_SerialNumber from record according to pos
		// record is string so there is need to transfrom string to unsigned int
		// Therefore, I used stoul function which is in C++11's string library
		//
		m_itemSerialNumber = std::stoul(m_utility.extractToken(record, next_pos));	// extract token and convert from string to ulong
		m_itemQuantity = std::stoi(m_utility.extractToken(record, next_pos));
		m_itemDescription = m_utility.extractToken(record, next_pos);

		// Updating the utility fieldWidth(m_FW) with the largest name's length
		//
		if (m_utility.getFieldWidth() < m_itemName.length())
			m_utility.setFieldWidth(m_itemName.length());
	}

	// Move Constructor 
	// It is needed for AssemblyLine module
	//
	ItemSet::ItemSet(ItemSet && other) {
		// Preventing self moving
		//
		if (this != &other) {
			m_itemName = other.m_itemName;
			m_itemDescription = other.m_itemDescription;
			m_itemSerialNumber = other.m_itemSerialNumber;
			m_itemQuantity = other.m_itemQuantity;

			other.m_itemName = { "" };
			other.m_itemDescription = { "" };
			other.m_itemSerialNumber = { 0 };
			other.m_itemQuantity = { 0 };
		}
	}

	// A query that returns a reference to the name of the item 
	//
	const std::string & ItemSet::getName() const {
		return m_itemName;
	}

	// A query that returns a reference to the name of the item 
	//
	const unsigned int ItemSet::getSerialNumber() const {
		return m_itemSerialNumber;
	}

	// A query that returns the remaining number of items in the set
	//
	const unsigned int ItemSet::getQuantity() const {
		return m_itemQuantity;
	}

	// a prefix decrement operator that reduces the number of items in stock by one and increases the serial number by one. This operator returns a reference to the current object
	//
	ItemSet& ItemSet::operator--() {
		m_itemQuantity--;
		m_itemSerialNumber++;

		return *this;
	}

	// A query that receives a reference to an std::ostream object os and a Boolean full and inserts the data for the current object into stream os. 
	//
	void ItemSet::display(std::ostream & os, bool full) const {
		size_t fw = m_utility.getFieldWidth();
		os << std::left << std::setw(fw) << m_itemName << " [" << std::setw(5) << m_itemSerialNumber << "]";
		if (full)
			os << " Quantity " << std::setw(3) << m_itemQuantity << std::right << " Description: " << m_itemDescription << std::endl;
	}
}
