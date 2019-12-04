#include "pch.h"
#include "Question.hpp"

#include <iomanip>
#include <sstream>

using namespace std;

Question::Question(int newShowNumber, const Date& newAirDate,
	const string& newRound, const string& newCategory,
	double newValue,
	const string& newQuestion, const string& newAnswer)
{
	showNumber = newShowNumber;
	airDate = newAirDate;
	round = newRound;
	category = newCategory;
	value = newValue;
	question = newQuestion;
	answer = newAnswer;
}

Question::Question(const Question& q)
{
	showNumber = q.showNumber;
	airDate = q.airDate;
	round = q.round;
	category = q.category;
	value = q.value;
	question = q.question;
	answer = q.answer;
}

int
Question::getShowNumber() const
{
	return showNumber;
}

Date
Question::getAirDate() const
{
	return airDate;
}

string
Question::getRound() const
{
	return round;
}

string
Question::getCategory() const
{
	return category;
}

double
Question::getValue() const
{
	return value;
}

string
Question::getQuestion() const
{
	return question;
}

string
Question::getAnswer() const
{
	return answer;
}

void
Question::setShowNumber(int n)
{
	showNumber = n;
}

void
Question::setAirDate(const Date& d)
{
	airDate = d;
}

void
Question::setRound(const string& r)
{
	round = r;
}

void
Question::setCategory(const string& c)
{
	category = c;
}

void
Question::setValue(double v)
{
	value = v;
}

void
Question::setQuestion(const string& q)
{
	question = q;
}

void
Question::setAnswer(const string& a)
{
	answer = a;
}

ostream&
operator<<(ostream& out, const Question& q)
{
	out << "Show Number: " << q.getShowNumber() << endl
		<< "Air Date   : " << q.getAirDate() << endl
		<< "Round      : " << q.getRound() << endl
		<< "Category   : " << q.getCategory() << endl
		<< "Value      : " << "$" << fixed << setprecision(2) << q.getValue() << endl
		<< "Question   : " << q.getQuestion() << endl
		<< "Answer     : " << q.getAnswer() << endl;
	return out;
}
