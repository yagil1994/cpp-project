#include "normalRound.h"
namespace election
{
	partyArr::partyArr():_arr(DynamicArray<party*>()){}
	void partyArr::addPartyToPartiesArr( party* const newParty)
	{
		_arr.push_back(newParty);
	}

	party*const partyArr::getPartyByName(const string& partyNameToFind)const
	{
		int amountOfParties = _arr.size();
		for (int i = 0; i < amountOfParties; ++i)
		{
			if (strcmp((_arr[i])->getPartyName().c_str(), partyNameToFind.c_str()) == 0)
				return _arr[i];
		}
		return nullptr;
	}
	party* const partyArr::getPartyBySerialnum(int partySerialNum)const//if the party name has not found returns nullptr
	{
		int amountOfParties = _arr.size();
		for (int i = 0; i < amountOfParties; ++i)
		{
			if (_arr[i]->getPartySerial() == partySerialNum)
				return _arr[i];
		}
		return nullptr;
	}
	void partyArr::addRepresentativeToParty(int partyId, int districtId, citizen* const newRep)
	{
		party* const tmp = getPartyBySerialnum(partyId);
		if (tmp)
			tmp->addNewRepresentativeToParty(newRep, districtId);
	}
	void partyArr::resizeRepresentativesArrs(int amountOfDistrictsToUpdate)
	{
		int amountOfParties = _arr.size();
		for (int i = 0; i < amountOfParties; ++i)
			_arr[i]->updateRepsArrSize(amountOfDistrictsToUpdate);
	}

	void partyArr::save(ostream& out)const
	{
		int _logs = _arr.size();
		out.write(rcastcc(&_logs), sizeof(_logs));
		for (int i = 0; i < _logs; i++)
			_arr[i]->save(out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}

	void partyArr::load(istream& in, normalRound& n)
	{
		int _logs;
		in.read(rcastc(&_logs), sizeof(_logs));
		if (in.good())
		{
			int amountOfDists = n.getAmountOfDistricts();
			for (int i = 0; i < _logs; i++)
			{
				party* tmpParty = nullptr;
				try {
					 tmpParty = new party( in, n, amountOfDists);
				}
				catch (exception& ex) {
					cout << "Error: " << ex.what() << endl;
					exit(1);
				}
				if (!in.good())
					throw FileException("The file did not loaded properly.");
				addPartyToPartiesArr(tmpParty);
			}
		}
		if (!in.good())
			throw FileException("The file did not loaded properly.");;
	}

	partyArr::partyArr(istream& in, normalRound& n) : _arr(DynamicArray<party*>())
	{
		load(in,n);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}
	const party* partyArr::operator[](int ind) const
	{ 
		if (ind < 0 || ind >= _arr.size())
			throw out_of_range("invalid array index");
		return _arr[ind];
	}
	party* partyArr::operator[](int ind)
	{ 
		if (ind < 0 || ind >= _arr.size())
			throw out_of_range("invalid array index");
		return _arr[ind];
	}
}