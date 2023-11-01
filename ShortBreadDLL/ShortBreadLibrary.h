#pragma once

#ifdef SHORTBREADLIB_EXPORTS
#define SHORTBREADLIB_API __declspec(dllexport)
#else
#define SHORTBREADLIB_API __declspec(dllimport)
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <cstring>
#include <algorithm>
#include <regex>


extern "C" SHORTBREADLIB_API bool GetFileContent(std::string Path, int WordLength);
extern "C" SHORTBREADLIB_API bool PrepareGraph();
extern "C" SHORTBREADLIB_API bool getShortestDistance(std::string source, std::string dest);
