#pragma once
#include <exception>
#include <string>
using namespace std;

namespace election
{
	class CalculateException : public exception
	{
	private:
		string _str;
	public:
		CalculateException(const string& str) { _str = str; }
		const char* what() const throw()
		{
			return _str.c_str();
		}
	};
}