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

const char *INPUT_FILE = "jeopardy.csv";
const char *DELIMS = ",";

int
main()
{
	// First we will read the input file.
	ifstream inputFile;
	inputFile.open(INPUT_FILE);

	if (!inputFile) {
		cerr << "Error opening file " << INPUT_FILE << endl;
		exit(1);
	}

	// The first line is the column headings.  We need to clear it.
	string line;

	if (!getline(inputFile, line)) {
		cerr << "Error reading first line of " << INPUT_FILE << endl;
		exit(2);
	}

	cout << "The input file is now being read, this will take a few seconds." << endl;

	// Now we are ready to loop through the input records.
	vector<Question> questions;

	while (getline(inputFile, line)) {
		// getline automatically removes the line feed (\n)
		// character at the end of the line, but a carriage return
		// (\r) may remain.  Remove it before continuing.
		if (line[line.length() - 1] == '\r')
			line = line.substr(0, line.length() - 1);

		string::size_type i;

		// In the CSV file, double quotes are escaped by having two
		// of them.  This makes them a pain to parse, but we will
		// use a trick.  We will replace them with the tilde
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

			// Commas can also appear inside a quoted string, which
			// is a problem.  Replace them with the backtick
			// character, which does not appear in the file.
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

	srand(time(0));

	double randomQ = (rand() % 216930) + 1.00;

	string answerQ;

	cout << endl << "Jeopardy Question of the day" << endl << endl;

	cout << "Show Number: " << questions[randomQ].getShowNumber() << endl;

	cout << "Air Date: " << questions[randomQ].getAirDate() << endl;
	
	cout << "Round: " << questions[randomQ].getRound() << endl;
	
	cout << "Category: " << questions[randomQ].getCategory() << endl;
	
	cout << "Value: " << questions[randomQ].getValue() << endl;
	
	cout << "Question: " << questions[randomQ].getQuestion() << endl;
	
	cout << "Answer: " << questions[randomQ].getAnswer() << endl;

	return 0;
}



/*//ask the user to guess the question
	cout << "Answer the question or you die!" << endl;
	cin.getline(answerQ, 50);

	if (answerQ != questions[randomQ].getAnswer()) {
		cout << "Incorrect! better luck tomorrow" << endl << endl;
	}
	else {
		cout << "Correct!" << endl << endl;
	}

	return 0;
}

/* loop copied
	for (int i = 0; i < questions.size(); i++) {
		cout << "--------\n" << questions[i];
	}
*/
