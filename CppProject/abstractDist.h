#pragma once
#include "representativesArr.h"
#include "kalpies.h"
#include "DistrictException.h"
#include <vector>
namespace election
{
	//**********************************************************************//
	//This is the "districts' base" class
	//**********************************************************************//
	class normalRound;
	class abstractDist
	{
	protected:
		int _numOfRepresentatives;
		int _serialNumber;
		string _districtName;
		double _votingPercentageInDist;
		citizensArr _districtCivils;
		kalpies _kalpiesResultInDist;//all the kalpies in district which every kalpi represents a party
		representativesArr _finalRepresentativesOfDist;// the representatives remained after the votes to all of the parties
		void handleUncompatiblePartyRepsAfterVotes(vector<int>& candidatesResInDistArr, int amountOfParties, const partyArr& allTheParties);
		void updateFinalRepresentativesInDists(const partyArr& allTheParties, vector<int> &candidatesResInDistArr, int amountOfParties);
	public:
		abstractDist(const string& districtName = "", int numOfRepresentatives = 0, int districtAutoSerialNumber = 0);
		abstractDist(const abstractDist&);
		abstractDist(istream& in, normalRound& n);
		virtual ~abstractDist();
		const string getDistrictName()const { return _districtName;}
		int getDistSerialNumber()const { return _serialNumber;}
		int getAmountOfRepsInDist()const { return _numOfRepresentatives;}
		virtual int getAmountOfFinalReps()const { return _finalRepresentativesOfDist.getAmountOfReps();}
		int getAmountOfCitizensInDist()const { return _districtCivils.getAmountOfTotalCitizens();}
		const citizensArr& getCitizens() { return _districtCivils;}
		representativesArr& getDistReps() { return _finalRepresentativesOfDist;}
		const representativesArr& getDistReps()const{ return _finalRepresentativesOfDist; }
		virtual const kalpi& getKalpi(int ind)const { return _kalpiesResultInDist[ind];}
		virtual const kalpi& getKalpi(int ind){ return _kalpiesResultInDist[ind]; }
		int getTotalVotesAmountInDist()const { return _kalpiesResultInDist.getTotalVotesAmount();}
		double getVotingPercentageInDist()const { return _votingPercentageInDist;}
		void addCitizen(citizen* const newCitiz);
		virtual void addElectors(kalpies& finalRes)const = 0;
		virtual int calculateVotesInDist(const partyArr& allTheParties,int isNormalRound);

		virtual const abstractDist& operator=(const abstractDist&);
		friend ostream& operator<<(ostream& os, const abstractDist& dist);// print operator

		virtual void save(ostream&)const;
		virtual void keepHolesAfterSave(ostream& os)const;

		virtual void load(istream& in, normalRound& n);
		virtual void setHolesAfterLoad(istream& in, normalRound& n);
	};
}