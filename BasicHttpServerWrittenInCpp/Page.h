#pragma once

#include <string>
#include <unordered_map>
#include <functional>

using OnRoute = std::string(*)();

class Page
{
public:
	static Page& GetInstance();
	void RegisterPage(std::string route, OnRoute executor);
	std::string FindPage(std::string route);
private:
	Page();
	~Page();
	Page(const Page& copy) = delete;
	Page(Page&& other) = delete;
private:
	std::unordered_map<std::string, OnRoute> mPages;
	std::string mEmptyPage;
};