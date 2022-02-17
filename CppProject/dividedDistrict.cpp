#include"normalRound.h"
namespace election
{
	dividedDistrict::dividedDistrict(const string& districtName, int numOfRepresentatives, int districtAutoSerialNumber)
		:abstractDist(districtName, numOfRepresentatives,districtAutoSerialNumber){}


	dividedDistrict::dividedDistrict(const dividedDistrict& other):dividedDistrict()
	{
		*this = other;
	}

	const dividedDistrict& dividedDistrict::operator=(const dividedDistrict& other)
	{
		if (this != &other)
		{
			abstractDist::operator=(other);
			 _electorsElectedPerParty=other._electorsElectedPerParty;
		}
		return *this;
	}
	
	int dividedDistrict::calculateVotesInDist(const partyArr& allTheParties, int isNormalRound)
	{
		abstractDist::calculateVotesInDist(allTheParties, isNormalRound);
		_electorsElectedPerParty.initKalpies(allTheParties);
		for (int i = 0; i < allTheParties.getAmountOfParties(); i++)
		{
			int amountOfTotalElectorsInParty = _finalRepresentativesOfDist[i].getAmountOfTotalCitizens();
			_electorsElectedPerParty[i].SetManyVotes(amountOfTotalElectorsInParty);
		}
		if(isNormalRound==0)//if it is a normalRound
		_electorsElectedPerParty.sortKalpies(static_cast<int>(howToSort::sortByElectors));//in case we need to sort in normal round
		else
			_electorsElectedPerParty.sortKalpies(static_cast<int>(howToSort::SortByVotes));//in case we need to sort in simple round
		return 0;
    }
	void dividedDistrict::addElectors(kalpies& finalRes)const
	{
		int amountOfParties = getAmountOfFinalReps();
		for (int i = 0; i < amountOfParties; i++)
		{
			int amountOfElectorsOfPartyInTheDist= _electorsElectedPerParty[i].getTotalVotesInParty();
			int RealpartyInd = _electorsElectedPerParty[i].getCurrParty()->getPartySerial();
			finalRes[RealpartyInd].SetManyVotes(amountOfElectorsOfPartyInTheDist);
		}
	}
	void dividedDistrict::printFinalResSortedInDist()const
	{
		int amountOfParties =_finalRepresentativesOfDist.getAmountOfReps();
		for (int i = 0; i < amountOfParties; i++)
		{
			int electorsCount = _electorsElectedPerParty[i].getTotalVotesInParty();
			if(electorsCount > 0)
			{
				cout <<(_electorsElectedPerParty[i].getCurrParty()->getPartyCandidate()->getCitizenName()) << " got: ";
				cout << electorsCount << " electors." << endl;
			}
		}
	}

	void dividedDistrict::save(ostream& out)const
	{
		abstractDist::save(out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}

	void dividedDistrict::keepHolesAfterSave(ostream& out)const
	{
		abstractDist::keepHolesAfterSave(out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}

	void dividedDistrict::setHolesAfterLoad(istream& in, normalRound& n)
	{
		abstractDist::setHolesAfterLoad(in, n);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
    }

	dividedDistrict::dividedDistrict(istream& in, normalRound& n):abstractDist(in,n), _electorsElectedPerParty(){}
	
}