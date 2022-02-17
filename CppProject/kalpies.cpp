#include "kalpies.h"
namespace election
{
	kalpies::kalpies(): _amountOfKalpies(0), _allKalpies(0), _totalVotesAmount(0){}

	 kalpies::kalpies(int amountOfKalpies, const partyArr& allTheParties):_amountOfKalpies(amountOfKalpies),_allKalpies(DynamicArray<kalpi>(amountOfKalpies)), _totalVotesAmount(0)
	{// initializes the kalpies and updates in each kalpi its own party
		 if (amountOfKalpies < 0)
			 throw invalid_argument("amountOfKalpies cant be a negative number");
		 
		 _amountOfKalpies = allTheParties.getAmountOfParties();
		 for (int i = 0; i < _amountOfKalpies; i++)
		 {
			 _allKalpies.push_back(kalpi());
			 _allKalpies[i].setKalpi(allTheParties.getPartyBySerialnum(i));
		 }
	}
	 void kalpies::initKalpies(const partyArr& allTheParties)// initializes the kalpies and updates in each kalpi its own party
	 {
		 _amountOfKalpies = allTheParties.getAmountOfParties();
		 *this=kalpies(_amountOfKalpies, allTheParties);
	 }
	kalpies::kalpies(const kalpies& other):kalpies()
	{
		*this = other;
	}
	const kalpies& kalpies::operator=(const kalpies&other )
	{
		if (this != &other)
		{
			_totalVotesAmount = other._totalVotesAmount;
			_amountOfKalpies = other._amountOfKalpies;
			_allKalpies = other._allKalpies;
		}
		return *this;
	}
	void kalpies::addVoteToKalpi(const party& partyToVote)
	{
		for (int i = 0; i < _amountOfKalpies; ++i)
		{
			if (*(_allKalpies[i].getCurrParty()) == partyToVote)
			{
				_allKalpies[i].addVote();
				_totalVotesAmount++;
				return;
			}
		}
	}
	void kalpies::sortKalpies(int isNormalRound)
	{
		if (isNormalRound == static_cast<int>(howToSort::sortByElectors))
			sort(_allKalpies.begin(), _allKalpies.end(), KalpiCmp(static_cast<int>(howToSort::sortByElectors)));
		else
			sort(_allKalpies.begin(), _allKalpies.end(), KalpiCmp(static_cast<int>(howToSort::SortByVotes)));
	}
	const kalpi& kalpies::operator[](int ind)const
	{ 
		if (ind < 0 || ind >= _allKalpies.size())
			throw out_of_range("invalid array index");
		return _allKalpies[ind];
	}
	kalpi& kalpies::operator[](int ind)
	{ 
		if (ind < 0 || ind >= _allKalpies.size())
			throw out_of_range("invalid array index");
		return _allKalpies[ind];
	}
}
	

