#pragma once

#include "Router.h"

Router& Router::GetInstance()
{
	static Router router;

	return router;
}

void Router::RegisterPath(std::string path)
{
	mRoutingGroups[path] = "";
}

void Router::RegisterDefaultPath(std::string path)
{
	mDefaultPath = path;
}

bool Router::IsExistRoute(std::string path)
{
	if (mRoutingGroups.find(path) == mRoutingGroups.end())
	{
		if (mDefaultPath != "")
		{
			return true;
		}

		return false;
	}

	return true;
}

Router::Router()
{
	mDefaultPath = "";
}

Router::~Router()
{

}