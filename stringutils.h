#pragma once

#include <string>
#include <deque>

void splitString(std::string toSplit, std::string delim, std::deque<std::string*>& data, int& count) {
	size_t pos = 0;
	std::string* token;
	std::deque<std::string*> *vector = new std::deque<std::string*>;

	while ((pos = toSplit.find(delim)) != std::string::npos) {
		token = new std::string(toSplit.substr(0, pos));
		vector->push_back(token);
		toSplit.erase(0, pos + delim.length());
	}

	vector->push_back(new std::string(toSplit));

	data = *vector;
	count = vector->size();
}