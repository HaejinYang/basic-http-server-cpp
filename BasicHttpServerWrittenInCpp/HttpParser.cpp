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
		if (eachLine.size() == 0)
		{
			fullText.ignore();
			if (std::getline(fullText, eachLine, delimeter))
			{
				// body
				mParsedBody = eachLine;
			}

			break;
		}

		mParsedHeader.push_back(eachLine);
		fullText.ignore();
	}
}

size_t HttpParser::GetLinesCount()
{
	return mParsedHeader.size();
}

void HttpParser::PrintAllLines()
{
	for (const auto& e : mParsedHeader)
	{
		std::cout << e << std::endl;;
	}
}

std::string HttpParser::GetPath()
{
	if (mParsedHeader.size() == 0)
	{
		return "";
	}

	std::stringstream firstLine(mParsedHeader[0]);
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

