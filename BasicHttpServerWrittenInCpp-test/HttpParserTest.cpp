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

TEST(GetPath, IfParseSuccessReturnNonEmptyPath)
{
	char* httpMsg = "GET /abcd HTTP/1.1\r\n\
		Host: 127.0.0.1 : 50001\r\n\
		Connection : keep - alive\r\n\
		Cache - Control : max - age = 0\r\n\
		sec - ch - ua : \" Not A;Brand\"; v = \"99\", \"Chromium\"; v = \"99\", \"Google Chrome\"; v = \"99\"\r\n\
		sec - ch - ua - mobile: ? 0\r\n\
		sec - ch - ua - platform : \"Windows\"\r\n\
		Upgrade - Insecure - Requests : 1\r\n\
		User - Agent : Mozilla / 5.0 (Windows NT 10.0; Win64; x64) AppleWebKit / 537.36 (KHTML, like Gecko) Chrome / 99.0.4844.51 Safari / 537.36\r\n\
		Sec-Fetch-Site: none\r\n\
		Sec-Fetch-Mode: navigate\r\n\
		Sec-Fetch-User: ?1\r\n\
		Sec-Fetch-Dest: document\r\n\
		Accept-Encoding: gzip, deflate, br\r\n\
		Accept-Language: ko,ko-KR;q=0.9,en-US;q=0.8,en;q=0.7";

	HttpParser parser;
	parser.Parse(httpMsg, strlen(httpMsg));
	
	EXPECT_TRUE(parser.GetPath() == "/abcd");
}