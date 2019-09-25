#ifndef _SICT_ITEMSET_H
#define _SICT_ITEMSET_H

#include <string>
#include "Utilities.h"

namespace sict
{
	class ItemSet
	{
		// Tokens which are came from string
		//
		std::string m_itemName;
		std::string m_itemDescription;
		unsigned long m_itemSerialNumber;
		int m_itemQuantity;

		// Containing Utilities object to use its' function 
		//
		Utilities m_utility;
	public:
		explicit ItemSet(const std::string&);
		ItemSet(ItemSet&&);
		// Disables copy and move assignment operations and copy construction of the list.dis
		//
		ItemSet(const ItemSet&) = delete;
		ItemSet& operator=(const ItemSet&) = delete;
		ItemSet& operator=(ItemSet&&) = delete;

		const std::string& getName() const;
		const unsigned int getSerialNumber() const;
		const unsigned int getQuantity() const;
		ItemSet& operator--();

		void display(std::ostream& os, bool full = true) const;
	};
}

#endif // !_SICT_ITEMSET_H