#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
#include <cstring>
#include <typeinfo>
#include <iostream>
#include "FileException.h"

using namespace std;
using namespace election;

void saveNameInFile(ostream& out, const string& name);
void loadNameFromFile(istream& in, string* name);