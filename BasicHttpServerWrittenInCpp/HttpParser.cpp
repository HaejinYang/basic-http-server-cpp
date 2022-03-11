#include <sstream>
#include <iostream>
#include "HttpParser.h"

void HttpParser::Parse(char* buf, size_t length)
{
	std::stringstream fullText(buf);
	std::string eachLine;
	char delimeter = '\r';

	while (std::getline(fullText, eachLine, delimeter))
	{
		mLineByLineParsedResult.push_back(eachLine);
	}
}

size_t HttpParser::GetLinesCount()
{
	return mLineByLineParsedResult.size();
}

void HttpParser::PrintAllLines()
{
	for (const auto& e : mLineByLineParsedResult)
	{
		std::cout << e << std::endl;
	}
}

std::string HttpParser::GetPath()
{
	if (mLineByLineParsedResult.size() == 0)
	{
		return "";
	}

	std::stringstream firstLine(mLineByLineParsedResult[0]);
	std::string text;
	char delimeter = ' ';

	while (std::getline(firstLine, text, delimeter))
	{
		if (HasHttpMethod(text))
		{
			continue;
		}

		if (text[0] == '/')
		{
			break;
		}
	}

	return text;
}

bool HttpParser::HasHttpMethod(std::string& s)
{
	// reference : https://developer.mozilla.org/ko/docs/Web/HTTP/Methods
	return (s == "POST" || s == "GET" || s == "PUT" || s == "DELETE" || s == "HEAD" || s == "TRACE" || s == "PATCH" || s == "CONNECT" || s == "OPTIONS");
} 

