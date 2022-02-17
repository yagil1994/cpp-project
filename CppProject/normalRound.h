#pragma once
#include <iostream>
#include <vector>
#include "book.h"
#include "districtArr.h"
#include "RoundExcepion.h"
#include "FileException.h"
#include "CalculateException.h"
using namespace std;
namespace election
{//**********************************************************************//
	//in this class we storage 3 fields: 
	//#1 book->keeps all the citizens in the country
	//#2 districtArr->keeps all the districts of the country
	//#3 partyArr-> keeps all the parties of the country
//**********************************************************************//
	class normalRound
	{
	protected:
		districtArr _allDistricts;
		book _allVoters;//all the citizens of the country are in this class<<<
		partyArr _allPartiesArr;
		int _electionDay;
		int _electionMonth; 
		int _electionYear;
	public:
		normalRound(int electionDay=0, int electionMonth=0, int electionYear=0);
		normalRound(istream& in, int electionDay = 0, int electionMonth = 0, int electionYear = 0);
		normalRound(const normalRound&) = delete;
		const normalRound& operator=(const normalRound&) = delete;
		virtual ~normalRound(){};
		virtual void calclateTotalResult();

		void UpdateDistrictDetails(const string& districtName, int numOfRepresentatives, int districtType);//updates a new districts in the districts array if it is a valid one
		virtual void UpdateCitizenDetails(const string& name, int id, int yearOfBirth, int DistrictNum);//updates a new citizen if he valid, to the voters book and to the distric he belongs
		void UpdatePartyDetails(const string& partyName,citizen* const PartyCandidate);//updates a new party in the parties array if it is a valid one
		virtual void UpdateRepresentativeDetails(citizen* const newRep, int partyWish, int districtWish);//updates a new representative if he valid,party location he asigned to
		void UpdateVote(citizen* const civil, int partySerialNumber);
		virtual int getAmountOfDistricts()const { return _allDistricts.getAmountOfDistricts();}// get the amount of districts we have untill now
		int getAmountOfParties()const { return _allPartiesArr.getAmountOfParties();}//get the amount of paties we have untill now
		citizen* const getCitizenFromBook(int IDToLookFor)const { return _allVoters.findCitizen(IDToLookFor);}//if the citizen is not exist returns nullptr
		virtual abstractDist* const getDistrictByName(const string& DistrictNameToLookFor) const{return _allDistricts.getDistrictByName(DistrictNameToLookFor);}//if the district does not exist returns nullptr
		virtual const abstractDist* getDistrictByIndex(int ind)const { return _allDistricts.getDistrictBySerialNumber(ind);}//if the district does not exist returns nullptr
		party* const getPartyByName(const string& PartyNameToLookFor)const { return _allPartiesArr.getPartyByName(PartyNameToLookFor);}//if the party does not exist returns nullptr, else the party
		party* const getPartyBySerial(int ind)const { return this->_allPartiesArr.getPartyBySerialnum(ind);}//if the party does not exist returns nullptr, else the party
		const partyArr& getAllParties()const { return _allPartiesArr;}
		const districtArr& getAllDistricts()const { return _allDistricts;}
		virtual const book& getVotersBook()const { return _allVoters; }
		int getElectionDay()const { return _electionDay;}
		int getElectionMonth()const { return _electionMonth; }
		int getElectionYear()const { return _electionYear; }
		

		virtual void save(ostream&)const;
		virtual void keepHolesAfterSave(ostream& out)const;

		virtual void setHolesAfterLoad(istream& in);
	};

}