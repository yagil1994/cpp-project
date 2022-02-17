#pragma once
#include "representativesArr.h"
#include "PartyException.h"


namespace election
{
	class party
	{	
	private:
		int _partySerialNumber;//serial number of the party
		int _totalVotesToParty;
	    string _partyName;//party name
		citizen* _partyCandidate;
		representativesArr _PartyRepresentatives;
	public:
		party(citizen* partyCandidate=nullptr, const string& partyName = "", int partySerialNumber = -1,int amountOfDists=0);//ctor
		party(const party&);//copy ctor
		party(istream& in, normalRound& n,int amountOfDists);
		~party();//dtor
		
		friend ostream& operator<<(ostream& os, const party&);// we need to finish it
		const party& operator=(const party&);
		bool operator==(const party&)const;
		void addVoteToParty() { _totalVotesToParty++; }
		void addNewRepresentativeToParty(citizen* const newRep, int districtToJoin);
		void updateRepsArrSize(int amountOfDistrictsToUpdate);

		const citizensArr& getPartyRepsInDist(int distNumber)const { return _PartyRepresentatives.getRepsByInd(distNumber);}
		citizen* const getPartyCandidate()const { return _partyCandidate;}
		int getPartyCandidateId()const { return _partyCandidate->getID();}
		int getPartySerial()const { return _partySerialNumber;}
		const string& getPartyName()const{ return _partyName; }//getter- get party name
		int getAmountOfTotalVotes()const { return _totalVotesToParty; }

		void save(ostream&)const;
		void load(istream& in, normalRound& n, bool sentFromCtor = false);
	};
}