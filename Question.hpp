#include <iostream>
#include <string>

#include "Date.h"

// Jeopardy Question
class Question {
public:
	// default constructor
	Question(int showNumber = 0, const Date& airDate = Date(),
		const std::string& round = "Jeopardy!",
		const std::string& category = "DEFAULT", double value = 0.0,
		const std::string& question = "", const std::string& answer = "");

	// copy constructor
	Question(const Question&);

	// accessors
	int getShowNumber() const;
	Date getAirDate() const;
	std::string getRound() const;
	std::string getCategory() const;
	double getValue() const;
	std::string getQuestion() const;
	std::string getAnswer() const;

	// mutators
	void setShowNumber(int);
	void setAirDate(const Date&);
	void setRound(const std::string&);
	void setCategory(const std::string&);
	void setValue(double);
	void setQuestion(const std::string&);
	void setAnswer(const std::string&);

private:
	int showNumber;
	Date airDate;
	std::string round;
	std::string category;
	double value;
	std::string question;
	std::string answer;
};

// stream output operator
std::ostream& operator<<(std::ostream&, const Question&);

#endif /* QUESTION_HPP */
