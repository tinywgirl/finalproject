// ---------------------------------------------------------------------
// Jeopardy Project
// Date Class Implementation, v1.0
//
// CSC 111: Introduction to Programming
// BMCC / Spring 2019 / Professor Yu
// ---------------------------------------------------------------------
#include "pch.h"
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Date.hpp"

using namespace std;

Date::Date(string date_string)
{
	tm when = {};
	istringstream iss(date_string);
	iss >> get_time(&when, "%Y-%m-%d");

	if (iss.fail()) {
		cerr << "Date::Date(string): get_time failed!\n";
		seconds = 18000; // Unix epoch: 1970-01-01
		return;
	}

	seconds = mktime(&when);
}

Date::Date(const Date& d)
{
	seconds = d.seconds;
}

void
Date::read(istream& in)
{
	tm when = {};

	in >> get_time(&when, "%Y-%m-%d");

	while (in.fail()) {
		cout << "Date format is [YYYY-MM-DD]. Try again.\n";
		in.clear();
		in.ignore();
		in >> get_time(&when, "%Y-%m-%d");
	}

	seconds = mktime(&when);

}

string
Date::toString() const
{
	struct tm* timeinfo = gmtime(&seconds);

	if (timeinfo == NULL) {
		cerr << "Date::toString(): gmtime failed!\n";
		return string("1970-01-01");
	}

	ostringstream oss;
	oss << put_time(timeinfo, "%Y-%m-%d");
	return oss.str();
}


bool
Date::operator==(const Date& d) const
{
	return (seconds == d.seconds);
}

bool
Date::operator!=(const Date& d) const
{
	return (seconds != d.seconds);
}

bool
Date::operator<(const Date& d) const
{
	return (seconds < d.seconds);
}

bool
Date::operator>(const Date& d) const
{
	return (seconds > d.seconds);
}

bool
Date::operator<=(const Date& d) const
{
	return (seconds <= d.seconds);
}

bool
Date::operator>=(const Date& d) const
{
	return (seconds >= d.seconds);
}

Date&
Date::operator=(const Date& d)
{
	seconds = d.seconds;
	return *this;
}

ostream&
operator<<(ostream& out, const Date& d)
{
	out << d.toString();
	return out;
}