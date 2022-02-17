#include "normalRound.h"
namespace election
{
	citizen::citizen(const string& name, int id , int yearOfbirth , abstractDist* const dist, party* const partyChoise)//ctor
		: _name(name), _id(id), _yearOfBirth(yearOfbirth), _district(dist), _partyChoise(partyChoise),
		 _isVote(false), _isRep(false), _isMainCandidate(false)
	{
		if(name != "" && id != -1 && yearOfbirth != -1 && dist != nullptr && partyChoise==nullptr)//only if its not the empty ctor
		{
			//check if ID 9 digits
			int howManyDig = 0;
			while (id > 0)
			{
				id = id / 10;
				howManyDig++;
			}
			if (howManyDig != 9)
				throw invalid_argument("Invalid ID");

			if (!(yearOfbirth >= 1900 && yearOfbirth <= 2021))//check year time line
				throw out_of_range("Your year of birth is not valid!, how old are you son?");
		}
	}
	
	
	ostream& operator<<(ostream& os, const citizen& citiz)//operator <<
	{
		os << "Name: " << citiz._name <<" ;ID: " << citiz._id<< " ;Born in: " << citiz._yearOfBirth <<" ;Origin district number: " << citiz.getDistrictNumber() <<endl;
		return os;
    }
	int citizen::getDistrictNumber()const
	{
		return _district->getDistSerialNumber();
	}
	int citizen::getPartySerialNumber()const
	{
		return _partyChoise->getPartySerial();
	}
	void citizen::save(ostream& out)const
	{
		out.write(rcastcc(&_id),sizeof(_id));
		out.write(rcastcc(&_yearOfBirth), sizeof(_yearOfBirth));
		int stringLen = _name.size();
		out.write(rcastcc(&stringLen), sizeof(stringLen));
		out.write(rcastcc(_name.c_str()), sizeof(char)* stringLen);

		int districtSerialNum = -1;
		if (_district != nullptr)
			districtSerialNum = _district->getDistSerialNumber();
		out.write(rcastcc(&districtSerialNum), sizeof(districtSerialNum));
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}
	void citizen::keepHolesAfterSave(ostream& out)const
	{
		int partySerialNum = -1;
		if (_partyChoise != nullptr)
			partySerialNum = _partyChoise->getPartySerial();

		out.write(rcastcc(&_isVote), sizeof(_isVote));
		out.write(rcastcc(&partySerialNum), sizeof(partySerialNum));
		
		out.write(rcastcc(&_isRep), sizeof(_isRep));
		out.write(rcastcc(&_isMainCandidate), sizeof(_isMainCandidate));
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}

	void citizen::load(istream& in, normalRound& n)
	{
		in.read(rcastc(&_id), sizeof(_id));
		in.read(rcastc(&_yearOfBirth), sizeof(_yearOfBirth));

		int stringLen;
		in.read(rcastc(&stringLen), sizeof(stringLen));

		char* temp = new char[sizeof(char) * (stringLen + 1)];
		in.read(temp, sizeof(char) * stringLen);
		temp[stringLen] = '\0';
		_name = temp;
		delete[] temp;

		int districtInd;
		in.read(rcastc(&districtInd), sizeof(districtInd));
		_district = n.getDistrictByIndex(districtInd);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}
	void citizen::setHolesAfterLoad(istream& in, normalRound& n)
	{
		in.read(rcastc(&_isVote), sizeof(_isVote));
		int partyInd;
		in.read(rcastc(&partyInd), sizeof(partyInd));
		if (partyInd != -1)//if the citizen has voted a party we got it
			_partyChoise = n.getPartyBySerial(partyInd);
		in.read(rcastc(&_isRep), sizeof(_isRep));
		in.read(rcastc(&_isMainCandidate), sizeof(_isMainCandidate));
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}
	citizen::citizen(istream& in, normalRound& n) :citizen()
	{
		load(in,n);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}
	citizen::~citizen()//dtor
	{
	}
}