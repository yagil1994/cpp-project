#pragma once
#include "normalRound.h"

namespace election
{
	class simpleRound:public normalRound
	{
	private:
		dividedDistrict* _singleDist;
	public:
		simpleRound(int amountOfReps, int electionDay = 0, int electionMonth = 0, int electionYear = 0);
		simpleRound(istream& in, int amountOfReps, int electionDay = 0, int electionMonth = 0, int electionYear = 0);
		simpleRound(const simpleRound& other) = delete;
		const simpleRound& operator=(const simpleRound&) = delete;

		virtual void UpdateCitizenDetails(const string& name, int id, int yearOfBirth, int DistrictNum)override;
		virtual void UpdateRepresentativeDetails(citizen* const newRep, int partyWish, int districtWish)override;
		virtual~simpleRound() {};
	};
}
