#include "tools.h"

void saveNameInFile(ostream& out,const string& name)
{
	int stringLen = name.size();
	out.write(rcastcc(&stringLen), sizeof(int));
	out.write(name.c_str(), stringLen);
	if (!out.good())
		throw FileException("The file did not saved properly.");
}

void loadNameFromFile(istream& in, string* name)
{
	int stringLen;
	in.read(rcastc(&stringLen), sizeof(stringLen));  
	char* temp = new char[sizeof(char)*(stringLen + 1)];
	in.read(temp,sizeof(char)*stringLen);
	temp[stringLen] = '\0';
	*name = temp;
	delete[] temp;
	if (!in.good())
		throw FileException("The file did not loaded properly.");
}
