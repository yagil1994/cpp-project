#pragma once
#include "districtManager.h"
class abstractDist;
namespace election
{
	class normalRound;
	class districtArr
	{
	private:
		DynamicArray<abstractDist*> _districtsArr;
	public:
		districtArr();
		districtArr(istream& in, normalRound& n);

		abstractDist* operator[](int ind);
		abstractDist* const operator[](int ind)const;

		abstractDist*const getDistrictByName(const string& districtNameToFind)const;//if did not find retuns nullptr
		abstractDist* const getDistrictBySerialNumber(int serialNum)const;
		virtual int getAmountOfDistricts()const { return _districtsArr.size();}

	    virtual void addDistrict(abstractDist* const newDist);
		void addCitizenToDistrict(citizen* const newCitizen);
		
		virtual void save(ostream&)const;
		virtual void keepHolesAfterSave(ostream& out)const;

		virtual void load(istream& in, normalRound& n);
		virtual void setHolesAfterLoad(istream& in, normalRound& n);
	};
}