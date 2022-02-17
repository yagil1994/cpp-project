#pragma once
#include "party.h"
namespace election
{//***********************************************************************************//
	//usually represents a party, and the votes the party got in a specific district
	//and can be used also to sum up the amount of the electors for each main candidate
//*************************************************************************************//
	class kalpi
	{
	private:
		int _totalVotesInParty;
		party* _currParty;
		bool _isAmountOfTotalVotesValid;
		bool _gotFinalRepsInTheEnd;
	public:
		kalpi();
		kalpi(const kalpi&);
		const kalpi& operator=(const kalpi&);

		bool setKalpi(party* const theParty) { _currParty = theParty; return true; }
		bool setWrongAmountOfTotalReps() { _isAmountOfTotalVotesValid = false; return true; }
		bool setGotFinalRepsInTheEnd() { _gotFinalRepsInTheEnd = true; return true; }
		bool SetManyVotes(int manyVotes) { _totalVotesInParty = _totalVotesInParty + manyVotes; return true; }
		bool operator<(const kalpi& other)
		{
			return (_totalVotesInParty < other._totalVotesInParty);
		}
		size_t operator-(const kalpi& other)
		{
			return (_totalVotesInParty - other._totalVotesInParty);
		}
		
		bool CheckIfAmountOfTotalVotesValid()const { return _isAmountOfTotalVotesValid; }

		void addVote() { _totalVotesInParty++;}

		int getTotalVotesInParty()const { return _totalVotesInParty; }
		party* const getCurrParty()const { return _currParty; }
		bool get_gotFinalRepsInTheEnd()const { return _gotFinalRepsInTheEnd; }
	};
}
		