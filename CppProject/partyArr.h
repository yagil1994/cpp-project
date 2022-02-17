#pragma once
#include "party.h"
namespace election
{
	class partyArr
	{
	private:
		DynamicArray<party*> _arr;
	public:
		partyArr();
		partyArr(istream& in, normalRound& n);

		void addPartyToPartiesArr( party* const newParty);
		void addRepresentativeToParty(int partyId, int districtId, citizen* const newRep);

		void resizeRepresentativesArrs(int amountOfDistrictsToUpdate);

		const party* operator[](int ind) const;
		party* operator[](int ind);
		party*const getPartyByName(const string& partyNameToFind)const;//if the party name has not found returns nullptr
		party* const getPartyBySerialnum(int partySerialNum)const;//if the party name has not found returns nullptr
		int getAmountOfParties()const { return _arr.size();}

		void save(ostream&)const;
		void load(istream& in, normalRound& n);
	};
}