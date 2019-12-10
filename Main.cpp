
#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Question.hpp"
#include "Date.hpp"

using namespace std;

const char* INPUT_FILE = "jeopardy.csv";
const char* DELIMS = ",";

void Quiz(); // function for the quiz

int main() {
	// First we will read the input file.
	ifstream inputFile;
	inputFile.open(INPUT_FILE);

	if (!inputFile) {
		cerr << "Error opening file " << INPUT_FILE << endl;
		exit(1);
	}

	// The first line is the column headings
	string line;

	if (!getline(inputFile, line)) {
		cerr << "Error reading first line of " << INPUT_FILE << endl;
		exit(2);
	}

	cout << "The file is being read, please wait a moment. . ." << endl;

	// loop through the input records.
	vector<Question> questions;

	while (getline(inputFile, line)) {
		// getline automatically removes the line feed (\n)
		// character at the end of the line, but a carriage return
		// (\r) may remain.  Remove it before continuing.
		if (line[line.length() - 1] == '\r')
			line = line.substr(0, line.length() - 1);

		string::size_type i;

		// In the Excel file, double quotes are escaped by having two
		// of them.  This makes them a pain to parse, we will replace them with the tilde
		// character (~), which does not appear in the file
		// otherwise.
		bool in_string = false;
		for (i = 0; i < line.size(); ++i) {
			if (!in_string && line[i] == '\"') {
				in_string = true;

			}
			else if (in_string && line[i] == '\"') {
				if (i + 1 != string::npos && line[i + 1] == '\"') {
					line[i] = line[i + 1] = '~';
				}
				else {
					in_string = false;
				}
			}

			// Commas can also appear inside a quoted string, which can be a problem, we replace them with back ticks
			if (in_string && line[i] == ',') {
				line[i] = '`';
			}
		}

		// Now we can tokenize on the comma.
		vector<string>tokens;

		string::size_type begin = line.find_first_not_of(DELIMS);
		string::size_type end = line.find_first_of(DELIMS, begin);

		while (begin != end) {
			string token;

			if (begin != string::npos && end != string::npos) {
				token = line.substr(begin, end - begin);
				begin = line.find_first_not_of(DELIMS, end);
				end = line.find_first_of(DELIMS, begin);
			}
			else if (begin != string::npos && end == string::npos) {
				token = line.substr(begin, line.length() - begin);
				begin = line.find_first_not_of(DELIMS, end);
			}

			// Strip outer double quotes.
			if (token[0] == '\"' && token[token.length() - 1] == '\"') {
				token = token.substr(1, token.length() - 2);
			}

			// Put back commas.
			for (string::size_type i = 0; i < token.size(); i++)
				if (token[i] == '`') token[i] = ',';

			// Put back double quotes.
			string::size_type found = token.find("~~");
			while (found != string::npos) {
				token.replace(found, 2, "\"");
				found = token.find("~~", found + 2);
			}

			tokens.push_back(token);
		}

		int showNumber = stoi(tokens[0]);
		Date airDate = Date(tokens[1]);
		string round = tokens[2];
		string category = tokens[3];

		double value = 0.0;

		if (tokens[4] != "None") {
			value = stod(tokens[4].substr(1, tokens[4].length() - 1));
		}

		string question = tokens[5];
		string answer = tokens[6];

		Question q(showNumber, airDate, round, category, value,
			question, answer);

		questions.push_back(q);
	}

	// Once we have read in the file, we can immediately close the
	// file stream.  We won't need to use it again.
	inputFile.close();

	srand(time(0)); // seed random
	double assignedQuestionIndex = (rand() % 216930) + 1.00;
	string answerQuestion;

	cout << endl << "Jeopardy Question of the day" << endl << endl;
	cout << "Question: " << questions[assignedQuestionIndex].getQuestion() << endl;

	cout << "Show Number: " << questions[assignedQuestionIndex].getShowNumber() << endl;
	cout << "Air Date: " << questions[assignedQuestionIndex].getAirDate() << endl;
	cout << "Round: " << questions[assignedQuestionIndex].getRound() << endl;
	cout << "Category: " << questions[assignedQuestionIndex].getCategory() << endl;
	cout << "Price: " << questions[assignedQuestionIndex].getValue() << endl << endl;

	cout << "Pleaser provide an answer: " << endl;
	getline(cin, answerQuestion);

	if (answerQuestion != questions[assignedQuestionIndex].getAnswer()) {
		cout << "Incorrect! better luck tomorrow" << endl << endl;
	}
	else {
		cout << "Correct!" << endl << endl;
	}	
	
	//ask the user if they want to answer another question
	int responseMore;
	cout << "Do you want to answer one more question?"<< endl <<"Press 1 for yes, 2 for no." << endl;
	cin >> responseMore;

	while (responseMore == 1) {
		double assignedQuestion = (rand() % 216930) + 1.00;
		string answer2;

		cout << endl << "New question: " << endl << endl;

		cout << "Question: " << questions[assignedQuestion].getQuestion() << endl;
		cout << "Show Number: " << questions[assignedQuestion].getShowNumber() << endl;
		cout << "Air Date: " << questions[assignedQuestion].getAirDate() << endl;
		cout << "Round: " << questions[assignedQuestion].getRound() << endl;
		cout << "Category: " << questions[assignedQuestion].getCategory() << endl;
		cout << "Price: " << questions[assignedQuestion].getValue() << endl << endl;

		cout << "Please provide an answer: " << endl;

		cin.ignore(); // clears the buffer

		getline(cin, answer2);
		
		if (answer2 != questions[assignedQuestion].getAnswer()) {
			cout << "Incorrect! better luck tomorrow" << endl << endl;
		}
		else {
			cout << "Correct!" << endl << endl;
		}

		cout << "Do you want to answer my questions? Press 1 for yes, 2 for no." << endl;
		cin >> responseMore;		
	}
	
	return 0;
}
