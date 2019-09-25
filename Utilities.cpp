#include <string>
#include <iostream>
#include "Utilities.h"

namespace sict
{
	// Setting Safe Empty State
	//
	char Utilities::m_delimiter = '\0';
	size_t Utilities::m_fieldWidth = { 0 };

	// A default constructor that places the object in a safe empty state and initializes its field width to a size that is less than the possible size of any token. 
	// However, I used static m_Delimiter and m_FW so safe empty state is defined outside of default constructor 
	//
	Utilities::Utilities() {}

	// Extracts the next token in the string starting at the position next_pos
	// 
	const std::string Utilities::extractToken(const std::string & str, size_t & next_pos) {
		std::string token;
		size_t word_length = 0;
		size_t starting_pos = 0;
		// Finding the next delimiter from 1 character after the previous character
		//
		size_t next_delimiter_pos = str.find(m_delimiter, next_pos + 1);
		if (next_pos == 0) {
			word_length = next_delimiter_pos;
			starting_pos = next_pos;
		}
		else {
			// Getting next words' length
			//
			word_length = (next_delimiter_pos - next_pos) - 1;
			starting_pos = next_pos + 1;
		}

		// Extracting the token string by using length
		//
		token = str.substr(starting_pos, word_length);

		// Setting next_delimiter_pos as next_pos
		//
		next_pos = next_delimiter_pos;
		return token;
	}

	// A query that returns the delimiter character
	//
	const char Utilities::getDelimiter() const {
		return m_delimiter;
	}

	// A query that returns the field width for the current object
	//
	size_t Utilities::getFieldWidth() const {
		return m_fieldWidth;
	}

	// A modifier that set the delimiter character for all object of this class
	//
	void Utilities::setDelimiter(const char d) {
		m_delimiter = { d };
	}

	// A modifier that set the field width for the current object 
	//
	void Utilities::setFieldWidth(size_t fw) {
		m_fieldWidth = { fw };
	}
}