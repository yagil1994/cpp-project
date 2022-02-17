#pragma once
#include "citizen.h"
#include "DynamicArray.h"
namespace election
{
	class citizensArr
	{
	private:
		DynamicArray<citizen*> _citizenArr;
	public:
		citizensArr();
		citizensArr(istream& in, normalRound& n, bool isLoadFromBook = false);

		int getAmountOfTotalCitizens()const { return _citizenArr.size();}
		citizen* const getCitizen(int ind)const;
		citizen*const lookForCitizen(int IDToLookFor)const;//return nullptr if does not exist

		citizen* const operator[](int ind)const;
		citizen* operator[](int ind);
		const citizensArr& operator=(const citizensArr&);//	return !(*this == other);

		void addCitizen(citizen*const newCitiz);

		void save(ostream&,bool isSavedFromBook=false)const;
		void keepHolesAfterSave(ostream&, bool isSavedFromBook = false)const;
		
		void load(istream& in, normalRound& n, bool isLoadFromBook = false);
		void setHolesAfterLoad(istream& in, normalRound& n);
	};
}