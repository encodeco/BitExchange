#pragma once

#include <string>
#include <vector>

int parse(std::string &delimiter, std::string &&line, std::vector <std::string> &parsed)
{
	size_t pos = 0;
	std::string token;
	while ((pos = line.find(delimiter)) != std::string::npos) {
		token = line.substr(0, pos);
		parsed.push_back(token);
		line.erase(0, pos + delimiter.length());
	}
	token = line.substr(0, pos);
	parsed.push_back(token);

	return parsed.size();
}