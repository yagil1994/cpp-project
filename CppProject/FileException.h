#pragma once
#include <exception>
#include <string>
using namespace std;

namespace election
{
	class FileException : public exception
	{
	private:
		string _str;
	public:
		FileException(const string& str) { _str = str; }
		const char* what() const throw()
		{
			return _str.c_str();
		}
	};
}