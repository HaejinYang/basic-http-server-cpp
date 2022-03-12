#pragma once

#include <string>
#include <unordered_map>

class Router
{
public:
	static Router& GetInstance();
	void RegisterPath(std::string path);
	void RegisterDefaultPath(std::string path);
	bool IsExistRoute(std::string path);
private:
	Router();
	~Router();
	Router(const Router& copy) = delete;
	Router(Router&& other) = delete;
private:
	std::string mDefaultPath;
	std::unordered_map<std::string, std::string> mRoutingGroups;
};