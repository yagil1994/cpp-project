#include "simpleRound.h"

namespace election
{
	simpleRound::simpleRound(int amountOfReps, int electionDay, int electionMonth, int electionYear)
		:normalRound::normalRound(electionDay, electionMonth, electionYear),_singleDist(new dividedDistrict("",amountOfReps,0))
		{//if alloc for _singleDist(new dividedDistrict("",amountOfReps,0)) will fail the one who called for this ctor will catch the bad alloc throw! 
		_allDistricts.addDistrict(_singleDist);
		}	
	simpleRound::simpleRound(istream& in, int amountOfReps, int electionDay, int electionMonth, int electionYear)
		:normalRound::normalRound(in, electionDay, electionMonth, electionYear)
		{
		 abstractDist* theOnlyDist = normalRound::_allDistricts[0];
		_singleDist=dynamic_cast< dividedDistrict*>(theOnlyDist);
		}
	 void simpleRound::UpdateCitizenDetails(const string& name, int id, int yearOfBirth, int DistrictNum)
 	 {
		 normalRound::UpdateCitizenDetails(name, id, yearOfBirth, 0);
	 }

	 void simpleRound::UpdateRepresentativeDetails(citizen* const newRep, int partyWish, int districtWish)
	 {
		 normalRound::UpdateRepresentativeDetails(newRep, partyWish, 0);
	 }
}
