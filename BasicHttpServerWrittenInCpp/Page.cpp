#include "Page.h"

Page& Page::GetInstance()
{
	static Page page;

	return page;
}

void Page::RegisterPage(std::string route, OnRoute executor)
{
	mPages[route] = executor;
}

std::string Page::FindPage(std::string route)
{
	if (mPages.find(route) == mPages.end())
	{
		return mEmptyPage;
	}

	return mPages[route]();
}

Page::Page()
{
	mEmptyPage = "";
}

Page::~Page()
{
}