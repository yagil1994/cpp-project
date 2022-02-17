#include "normalRound.h"
namespace election
{
	kalpi::kalpi():_totalVotesInParty(0), _currParty(nullptr), _isAmountOfTotalVotesValid(true), _gotFinalRepsInTheEnd(false){}

	kalpi::kalpi(const kalpi& other):kalpi()
	{
		*this = other;
	}
	const kalpi& kalpi::operator=(const kalpi& other)
	{
		if (this != &other)
		{
			_totalVotesInParty = other._totalVotesInParty;
			_currParty = other._currParty;
			_isAmountOfTotalVotesValid = other._isAmountOfTotalVotesValid;
			_gotFinalRepsInTheEnd = other._gotFinalRepsInTheEnd;
		}
		return *this;
	}
}