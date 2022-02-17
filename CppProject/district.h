#pragma once
#include "abstractDist.h"

namespace election
{
	class normalRound;
	class district:public abstractDist
	{
	private:
		 citizen* _distWinner;// the final winner of the current district
		 const party* _WinnerParty;
	public:
		district(const string& districtName = "", int numOfRepresentatives = 0, int districtAutoSerialNumber = -1);//ctor
		district(const district&);//copy ctor
		district(istream& in, normalRound& n);
		virtual ~district(){};//dtor

		virtual const party* getPartyWinner()const { return _WinnerParty;}
		virtual const citizen* getDistWinner()const { return _distWinner;}

		virtual int calculateVotesInDist(const partyArr& allTheParties, int isNormalRound)override;
		virtual void addElectors(kalpies& finalRes)const override;//todo
		const district& operator=(const district&);

		virtual void save(ostream&)const;
		virtual void keepHolesAfterSave(ostream& out)const;

		virtual void setHolesAfterLoad(istream& in, normalRound& n);
	};
}
