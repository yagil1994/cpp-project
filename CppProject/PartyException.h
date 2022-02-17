#pragma once
#include <exception>
#include <string>
using namespace std;

namespace election
{
	class PartyException : public exception
	{
	private:
		string _str;
	public:
		PartyException(const string& str) { _str = str; }
		const char* what() const throw()
		{
			return _str.c_str();
		}
	};
}