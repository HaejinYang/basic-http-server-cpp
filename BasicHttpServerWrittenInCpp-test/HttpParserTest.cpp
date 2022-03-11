#include "pch.h"
#include "../BasicHttpServerWrittenInCpp/HttpParser.h"

// reference : https://github.com/google/googletest/tree/main/googletest/samples
TEST(HasHttpMethod, InvalidStringReturnFalse) 
{
	HttpParser parser;

	std::string input = "Put";
	EXPECT_FALSE(parser.HasHttpMethod(input));

	input = "asd;lqwd";
	EXPECT_FALSE(parser.HasHttpMethod(input));

	input = "1231avd";
	EXPECT_FALSE(parser.HasHttpMethod(input));

	input = "";
	EXPECT_FALSE(parser.HasHttpMethod(input));

	input = " ";
	EXPECT_FALSE(parser.HasHttpMethod(input));
}

TEST(HasHttpMethod, HttpMethodReturnTrue) 
{
	HttpParser parser;

	std::string input = "PUT";
	EXPECT_TRUE(parser.HasHttpMethod(input));

	input = "GET";
	EXPECT_TRUE(parser.HasHttpMethod(input));

	input = "POST";
	EXPECT_TRUE(parser.HasHttpMethod(input));

	input = "DELETE";
	EXPECT_TRUE(parser.HasHttpMethod(input));
}

TEST(GetPath, IfParseSuccessShouldReturnPath)
{
	HttpParser parser;
	//parser.Parse()
}