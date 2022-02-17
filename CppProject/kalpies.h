#pragma once
#include "kalpi.h"
#include "partyArr.h"
#include <algorithm>
#include <iostream>
using namespace std;
namespace election
{
	//****************************************//
	//gathers many kalpies by array of kalpies
	//****************************************//
	enum class howToSort { sortByElectors = 0, SortByVotes };
	enum class roundType { normalR = 0, simpleR };

	class kalpies
	{
	private:
		DynamicArray<kalpi> _allKalpies;
		int _totalVotesAmount;
		int _amountOfKalpies;
	public:
		kalpies();
		kalpies(int amountOfKalpies, const partyArr& allTheParties);
		kalpies(const kalpies&);

		const kalpi& operator[](int ind)const;
		kalpi& operator[](int ind);
		 const kalpies& operator=(const kalpies&);
		
		 int getTotalVotesAmount()const { return _totalVotesAmount;}// getting the total amount of votes in the district

		 void addVoteToKalpi(const party& partyToVote);
		 void initKalpies(const partyArr& allTheParties);

		void sortKalpies(int isNormalRound);

		class KalpiCmp
		{
		public:
			bool type;
			KalpiCmp(bool t) { type = t; }
			bool operator()(const kalpi& k1, const kalpi& k2)
			{
				if (type == 0)
				{
					int resK1 = k1.getTotalVotesInParty();
					int resK2 = k2.getTotalVotesInParty();
					if (resK1 > resK2)
						return true;
					else if (resK1 == resK2)
						return k1.getCurrParty()->getPartySerial() > k2.getCurrParty()->getPartySerial();
					else
						return false;
				}
				else
				{
					int resK1 = k1.getCurrParty()->getAmountOfTotalVotes();
					int resK2 = k2.getCurrParty()->getAmountOfTotalVotes();
					if (resK1 > resK2)
						return true;
					else if (resK1 == resK2)
						return k1.getCurrParty()->getPartySerial()> k2.getCurrParty()->getPartySerial();
					else
						return false;
				}
			}
		};
	};
}
