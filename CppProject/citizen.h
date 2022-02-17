#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "CitizenException.h"
#include <typeinfo>
#include <iostream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
namespace election
{
	class abstractDist;//forward decleration
	 class party;//forward decleration
	 class normalRound; //forward decleration
	class citizen
	{
	private:
		int _id;
		int _yearOfBirth;
		string _name;
		const abstractDist*  _district;
	    party* _partyChoise;
		bool _isVote;
		bool _isRep;
		bool _isMainCandidate;
	public:
		citizen(const string& name ="", int id = -1, int yearOfbirth = -1, abstractDist* const dist = nullptr, party* const partyChoise=nullptr);//ctor
		citizen(istream& in, normalRound& n);
		citizen(const citizen&) = delete;
		~citizen();//dtor

		friend ostream& operator<<(ostream& os, const citizen& citiz);//operator <<
		const citizen& operator=(const citizen&) = delete; //we are not supposed to copy citizen to a citizen
		int getID()const { return _id; }//get ID
		int getYearOfBirth()const { return _yearOfBirth; }
		int getDistrictNumber()const;
		int getPartySerialNumber()const;
		const string& getCitizenName()const { return _name;}
		const party* getParty()const { return _partyChoise;}
	     party* getPartyForChanges()const { return _partyChoise; }

		bool isVoted()const { return _isVote; }//check if voted
		bool isRep()const { return _isRep; }//check if representative
		bool isMainCandidate()const { return _isMainCandidate; }//check if Main Candidate

		bool setPartyChoise(party* const partyChoise) { _partyChoise = partyChoise; return true; }//set the party choise 
		bool setVote() { _isVote = true; return true; }//update that the citizen has voted
		bool setRep() { _isRep = true; return true; }//update that the citizen has become a represenatative
		bool setMainCandidate() { _isMainCandidate = true; return true; }//update that the citizen has become the main candidate of the party

		void save(ostream&)const;
		void keepHolesAfterSave(ostream&)const;

		void load(istream& in, normalRound& n);
		void setHolesAfterLoad(istream& in, normalRound& n);
	};
}