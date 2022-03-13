#include "pch.h"
#include "../BasicHttpServerWrittenInCpp/Page.h"

// reference : https://github.com/google/googletest/tree/main/googletest/samples
TEST(FindPageMethod, IfRegisteredFindSuccess)
{
	Page::GetInstance().RegisterPage("/a", []()->std::string {
		
		return "/a";
		});
	
	EXPECT_EQ(Page::GetInstance().Response("/a"), "/a");
}

TEST(FindPageMethod, IfNotRegisteredFindFail)
{
	Page::GetInstance().RegisterPage("/a", []()->std::string {

		return "/a";
		});

	EXPECT_EQ(Page::GetInstance().Response("/b"), "");
}