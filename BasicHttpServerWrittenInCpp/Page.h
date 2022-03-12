#pragma once

#include <string>
#include <unordered_map>

class Page
{
public:
	static Page& GetInstance();
	void RegisterPage(std::string route, std::string page);
	std::string& FindPage(std::string route);
private:
	Page();
	~Page();
	Page(const Page& copy) = delete;
	Page(Page&& other) = delete;
private:
	std::unordered_map<std::string, std::string> mPages;
	std::string mEmptyPage;
};