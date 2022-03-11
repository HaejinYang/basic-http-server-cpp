#pragma once

#include <vector>
#include <string>

class HttpParser
{
public:
	void Parse(char* buf, size_t length);
	size_t GetLinesCount();
	void PrintAllLines();
	std::string GetPath();
	bool HasHttpMethod(std::string& s);
private:
private:
	std::vector<std::string> mParsedHeader;
	std::string mParsedBody;
};