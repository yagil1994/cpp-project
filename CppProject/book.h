#pragma once
#include "citizensArr.h"
using namespace std;
namespace election
{//**********************************************************************//
	//keeps all the citizens in the country
//**********************************************************************//
	class book
	{
	private:
		citizensArr _theVotersBook;//the voters book
	public:
		book() = default;
		book(istream& in, normalRound& n);
		book(const book&) = delete;
		~book();//distractor
		const citizensArr& getVotersBook()const{ return _theVotersBook;}
		void addCitizenToBook(citizen* const newCitizen) { _theVotersBook.addCitizen(newCitizen);}
		int getAmountOfTotalCitizens()const { return _theVotersBook.getAmountOfTotalCitizens();}
		citizen* const getCitizenByInd(int ind)const {return _theVotersBook.getCitizen(ind);}//returns nullptr if does not exist
		citizen* const findCitizen(int IDToLookFor)const { return _theVotersBook.lookForCitizen(IDToLookFor);}//returns nullptr if does not exist

		void save(ostream&)const;
		void keepHolesAfterSave(ostream&)const;
		void setHolesAfterLoad(istream& in, normalRound& n);
	};
}