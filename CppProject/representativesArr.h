#pragma once
#include "citizensArr.h"
#include "DynamicArray.h"
namespace election
{
	class representativesArr:public DynamicArray<citizensArr>
	{
		/*
		 protected:
		 DynamicArray<citizensArr> _arr ->>> we inherited it, and we work on it
		*/
	public:
		representativesArr(int size);//ctor
		representativesArr();
		virtual ~representativesArr() {};
		void reSizeArr_Specific(int amountOfParties) {resizeToAspecificPhy_Size(amountOfParties);}
		void updateAmountOfDistrictsAndResize(int amountOfDistrictsToUpdate);
		void addRepresentativeToDist(citizen* const newRep, int joinDistrictSerialNumber);
		const citizensArr& getRepsByInd(int distNumber)const { return _arr[distNumber]; }
		int getAmountOfReps()const { return size();}

		const citizensArr operator[](int ind)const { return _arr[ind]; }
		citizensArr operator[](int ind) { return _arr[ind]; }
	
		void save(ostream&)const;
		void keepHolesAfterSave(ostream& out)const;

		void load(istream& in, normalRound& n);
		void setHolesAfterLoad(istream& in, normalRound& n);
	};
}

