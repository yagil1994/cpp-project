#include "normalRound.h"
namespace election
{
	district::district(const string& districtName, int numOfRepresentatives, int districtAutoSerialNumber)
		:abstractDist(districtName, numOfRepresentatives, districtAutoSerialNumber), _distWinner(nullptr), _WinnerParty(nullptr) {}

	district::district(const district& other):district() 
	{
		*this = other;
	}
		
	const district& district::operator=(const district& other)
	{
		abstractDist::operator=(other);
		if (this != &other)
		{
			_distWinner = other._distWinner;
			_WinnerParty = other._WinnerParty;
		}
		return *this;
	}
	int district::calculateVotesInDist(const partyArr& allTheParties, int isNormalRound)
	{
		int maxIndParty=abstractDist::calculateVotesInDist(allTheParties, isNormalRound);
		_distWinner = allTheParties[maxIndParty]->getPartyCandidate();
		_WinnerParty = allTheParties[maxIndParty];
		return 0;
	}

	void district::addElectors(kalpies& finalRes)const
	{
		int amountOfRepresentativesInDist = getAmountOfRepsInDist();
		const citizen* tmpWinner =getDistWinner();
		int partyWinnerInd = getPartyWinner()->getPartySerial();
		finalRes[partyWinnerInd].SetManyVotes(amountOfRepresentativesInDist);
	}

	void district::save(ostream& out)const
	{
		abstractDist::save(out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}

	void district::keepHolesAfterSave(ostream& out)const
	{
		abstractDist::keepHolesAfterSave(out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}
	void district::setHolesAfterLoad(istream& in, normalRound& n)
	{
		abstractDist::setHolesAfterLoad(in, n);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}

	district::district(istream& in, normalRound& n):abstractDist(in,n), _distWinner(nullptr), _WinnerParty(nullptr)
	{	
	}
}