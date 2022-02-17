#include "abstractDist.h"
#include "normalRound.h"
namespace election
{
	abstractDist::abstractDist(const string& districtName, int numOfRepresentatives, int districtAutoSerialNumber)
		: _districtName(districtName), _numOfRepresentatives(numOfRepresentatives),
		_serialNumber(districtAutoSerialNumber),_votingPercentageInDist(0) 
	{
		if(numOfRepresentatives < 0)
			throw  out_of_range("numOfRepresentatives need to be a positive number");

		if (districtAutoSerialNumber < 0)
			throw  out_of_range("districtAutoSerialNumber need to be a positive number");
	}

	abstractDist::abstractDist(const abstractDist& other) : abstractDist() 
	{
		*this = other;
	}
	 const abstractDist& abstractDist::operator=(const abstractDist& other)
	 {
		if (this != &other)
		{
			_numOfRepresentatives = other._numOfRepresentatives;
			_serialNumber = other._serialNumber;
			_districtName = other._districtName;
			_votingPercentageInDist = other._votingPercentageInDist;
			_districtCivils = other._districtCivils;
			_kalpiesResultInDist = other._kalpiesResultInDist;
			_finalRepresentativesOfDist = other._finalRepresentativesOfDist;
		}
		return *this;
     }
	 int abstractDist::calculateVotesInDist(const partyArr& allTheParties,int isNormalRound)
	{
		_kalpiesResultInDist.initKalpies(allTheParties);
		for (int i = 0; i < getAmountOfCitizensInDist(); i++)//run on all the citizens in the current district
		{
			citizen* const currCitizen = _districtCivils.getCitizen(i);
			if (currCitizen->isVoted())//if the current citizen has voted
			{
				party* partyTmp = currCitizen->getPartyForChanges();//getting the party the citizen has voted
				_kalpiesResultInDist.addVoteToKalpi(*partyTmp);
				partyTmp->addVoteToParty();
			}
		}
		int amountOfParties = allTheParties.getAmountOfParties();
		vector<int> candidatesResInDistArr;  
		candidatesResInDistArr.resize(amountOfParties);// the amount of representatives for each party in the district will get a value in this vector
		for (int i = 0; i < amountOfParties; i++)
			candidatesResInDistArr[i] = 0;

		int maxInd = 0, countGivenReps = 0;
		int totalVotesInDist = _kalpiesResultInDist.getTotalVotesAmount();
		int repsAmountInDist = _numOfRepresentatives;

		for (int i = 0; i < amountOfParties; i++)//in this loop we get the amount of representatives each party gets in the district
		{
			int actualVotesToSpecificParty = _kalpiesResultInDist[i].getTotalVotesInParty();
			if (totalVotesInDist != 0)
			{
				candidatesResInDistArr[i] = ((static_cast<double>(actualVotesToSpecificParty)) / totalVotesInDist) * repsAmountInDist;
				countGivenReps += candidatesResInDistArr[i];
				if (_kalpiesResultInDist[maxInd].getTotalVotesInParty() < actualVotesToSpecificParty)
					maxInd = i;
			}
		}
		if (countGivenReps < repsAmountInDist)
			candidatesResInDistArr[maxInd] += (repsAmountInDist - countGivenReps);
		handleUncompatiblePartyRepsAfterVotes(candidatesResInDistArr, amountOfParties, allTheParties);
		if (getAmountOfCitizensInDist() > 0)
			_votingPercentageInDist = (static_cast<double>(totalVotesInDist) / getAmountOfCitizensInDist()) * 100;

		_finalRepresentativesOfDist.reSizeArr_Specific(amountOfParties);
		updateFinalRepresentativesInDists(allTheParties, candidatesResInDistArr, amountOfParties);
		return maxInd;
	}
	void abstractDist::handleUncompatiblePartyRepsAfterVotes(vector<int> &candidatesResInDistArr, int amountOfParties, const partyArr& allTheParties)
	{
		for (int i = 0; i < amountOfParties; i++)
		{
			if (candidatesResInDistArr[i] > allTheParties[i]->getPartyRepsInDist(_serialNumber).getAmountOfTotalCitizens())
				_kalpiesResultInDist[i].setWrongAmountOfTotalReps();
			if (candidatesResInDistArr[i] > 0)
				_kalpiesResultInDist[i].setGotFinalRepsInTheEnd();
		}
	}

	void abstractDist::updateFinalRepresentativesInDists(const partyArr& allTheParties, vector<int> &candidatesResInDistArr, int amountOfParties)
	{
		for (int i = 0; i < amountOfParties; ++i)
		{
			const citizensArr& tmpReps = allTheParties.getPartyBySerialnum(i)->getPartyRepsInDist(_serialNumber);
			int amountOfRepsInCurDist = candidatesResInDistArr[i];
			if (amountOfRepsInCurDist > tmpReps.getAmountOfTotalCitizens())
				throw CalculateException("Not enough reps.");
			for (int j = 0; j < amountOfRepsInCurDist; j++)
			{
				citizen* const currRep = tmpReps.getCitizen(j);
				_finalRepresentativesOfDist.addRepresentativeToDist(currRep, i);
			}
		}
	}
	ostream& operator<<(ostream& os, const abstractDist& dist)// print operator
	{
		cout << "District name: " << dist._districtName << endl << "District Number: " << dist._serialNumber << endl;
		os << "Amount of representatives: " << dist._numOfRepresentatives << endl << endl;
		return os;
	}
	abstractDist::~abstractDist()
	{
	}
	void abstractDist::addCitizen(citizen* const newCitiz)
	{
		_districtCivils.addCitizen(newCitiz);
	}
	 void abstractDist::save(ostream& out)const
	 {
		 out.write(rcastcc(&_numOfRepresentatives), sizeof(_numOfRepresentatives));
		 out.write(rcastcc(&_serialNumber), sizeof(_serialNumber));

		 int stringLen = _districtName.size();
		 out.write(rcastcc(&stringLen), sizeof(stringLen));
		 out.write(rcastcc(_districtName.c_str()), sizeof(char) * stringLen);

		 if(!out.good())
			 throw FileException("The file did not saved properly.");
	 }
	 void abstractDist::keepHolesAfterSave(ostream& out)const
	 {
		 _districtCivils.save(out);
	 }
	 void abstractDist::load(istream& in, normalRound& n)
	 {
		 in.read(rcastc(&_numOfRepresentatives), sizeof(_numOfRepresentatives));
		 in.read(rcastc(&_serialNumber), sizeof(_serialNumber));

		 int stringLen;
		 in.read(rcastc(&stringLen), sizeof(stringLen));

		 char* temp = new char[sizeof(char) * (stringLen + 1)];
		 in.read(temp, sizeof(char) * stringLen);
		 temp[stringLen] = '\0';
		 _districtName = temp;
		 delete[] temp;

		 if (!in.good())
			 throw FileException("The file did not loaded properly.");
	 }

	 void abstractDist::setHolesAfterLoad(istream& in, normalRound& n)
	 {
		 _districtCivils.load(in,n);
		 if (!in.good())
			 throw FileException("The file did not loaded properly.");
	 }

	 abstractDist::abstractDist(istream& in, normalRound& n):abstractDist()
	 {
		 load(in,n);
		 if (!in.good())
			 throw FileException("The file did not loaded properly.");
	 }


};