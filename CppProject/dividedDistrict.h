#pragma once
#include "abstractDist.h"
namespace election
{
	class dividedDistrict:public abstractDist
	{
	private:
		kalpies _electorsElectedPerParty;
	public:
		dividedDistrict(const string& districtName = "", int numOfRepresentatives = 0, int districtAutoSerialNumber = -1);
		dividedDistrict(const dividedDistrict&);
		dividedDistrict(istream& in, normalRound& n);
		virtual ~dividedDistrict(){};
		virtual void addElectors(kalpies& finalRes)const override;
		virtual int calculateVotesInDist(const partyArr& allTheParties,int isNormalRound)override; //sorts as well the result of the district
		const dividedDistrict& operator=(const dividedDistrict&);
		void printFinalResSortedInDist()const;
		const kalpies& getElectorsElectedPerParty()const { return _electorsElectedPerParty;}

		virtual void save(ostream&)const;
		virtual void keepHolesAfterSave(ostream& out)const;

		virtual void setHolesAfterLoad(istream& in, normalRound& n);
	};
}