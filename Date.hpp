// ---------------------------------------------------------------------
// Jeopardy Project
// Date Class Declaration, v1.0
//
// CSC 111: Introduction to Programming
// BMCC / Spring 2019 / Professor Yu
// ---------------------------------------------------------------------
#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <string>
#include <ctime>

class Date {
public:
	// default constructor
	Date(std::string date_string = "1970-01-01");

	// copy constructor
	Date(const Date&);

	// public methods
	void read(std::istream&);
	std::string toString() const;

	// comparison operators
	bool operator==(const Date&) const;
	bool operator!=(const Date&) const;
	bool operator< (const Date&) const;
	bool operator> (const Date&) const;
	bool operator<=(const Date&) const;
	bool operator>=(const Date&) const;

	// assignment operator
	Date& operator=(const Date&);

private:
	std::time_t seconds;
};

std::ostream& operator<<(std::ostream&, const Date&);

#endif /* DATE_HPP */
