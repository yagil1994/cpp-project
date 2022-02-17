#include "normalRound.h"
	namespace election
	{
	  //************************************************************************************//updates
		normalRound::normalRound(int electionDay, int electionMonth, int electionYear)
			:_electionDay(electionDay), _electionMonth(electionMonth), _electionYear(electionYear)
		{
			if (electionDay <= 0 || electionDay > 31)
				throw out_of_range("invalid electionDay");
			if (electionMonth <= 0 || electionMonth > 12)
				throw out_of_range("invalid electionMonth");
			if (electionYear <= 0)
				throw out_of_range("invalid electionYear");

			//Match between month and day
			if ((electionMonth == 4) || (electionMonth == 6) || (electionMonth == 9) || (electionMonth == 1))//30 

			{
				if (electionDay <= 0 || electionDay > 30)
					throw out_of_range("invalid election date");
			}
			if (electionMonth == 2)//ex 28 days
			{
				if (electionDay <= 0 || electionDay > 28)
					throw out_of_range("invalid election date");
			}
		}
		
		normalRound::normalRound(istream& in, int electionDay, int electionMonth, int electionYear)
			: _electionDay(electionDay), _electionMonth(electionMonth), _electionYear(electionYear),
			_allDistricts(in,*this), _allVoters(in,*this), _allPartiesArr(in,*this)
		{	
			setHolesAfterLoad(in);
			if (!in.good())
				throw FileException("The file did not loaded properly.");
		}
		void normalRound::UpdateDistrictDetails(const string& districtName, int numOfRepresentatives,int districtType)
		{
			abstractDist* theNewDist = nullptr;
			if (districtType == 1)//we need to create a normal district
			{
				try{
					theNewDist = new district(districtName, numOfRepresentatives, getAmountOfDistricts());
				}
				catch (bad_alloc& ex) {
					cout << "Error: " << ex.what() << endl;
					exit(1);
				}
				catch (exception& ex) {
					cout << "Error: " << ex.what() << endl;
				}
			}
			else// we need to create a normal district
			{
				try {
					theNewDist = new dividedDistrict(districtName, numOfRepresentatives, getAmountOfDistricts());
				}
				catch (bad_alloc& ex) {
					cout << "Error: " << ex.what() << endl;
					exit(1);
				}
				catch (exception& ex) {
					cout << "Error: " << ex.what() << endl;
				}
			}
			_allDistricts.addDistrict(theNewDist);
		}
		void normalRound::UpdateCitizenDetails(const string& name, int id, int yearOfBirth, int DistrictNum)
		{
			abstractDist* const tmpDist = _allDistricts.getDistrictBySerialNumber(DistrictNum);
			citizen* newCitizen = nullptr;
			try {
				 newCitizen = new citizen(name, id, yearOfBirth, tmpDist);
				 _allVoters.addCitizenToBook(newCitizen);//add citizen to the voters book
				 _allDistricts.addCitizenToDistrict(newCitizen);//add the citizen to his district
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
			catch (exception& ex) {
				cout << "Error: " << ex.what() << endl;
			}
		}	
		void normalRound::UpdatePartyDetails(const string& partyName, citizen* const PartyCandidate)
		{
			party* newParty = nullptr;
			try {
				 newParty = new party(PartyCandidate, partyName, getAmountOfParties(), getAmountOfDistricts());
				 _allPartiesArr.addPartyToPartiesArr(newParty);
				 PartyCandidate->setMainCandidate();//update the citizen that he is a main candidate of the party now
			}
			catch (bad_alloc& ex) {
				cout << ex.what() << endl;
				exit(1);
			}
			catch (exception& ex) {
				cout << "Error: " << ex.what() << endl;
			}
		}
		void normalRound::UpdateRepresentativeDetails(citizen* const newRep, int partyWish, int districtWish)
		{
			newRep->setRep();//update that the citizen is representative in the voters book
			int citizenDistrict = newRep->getDistrictNumber();
			_allPartiesArr.resizeRepresentativesArrs(getAmountOfDistricts());
			_allPartiesArr.addRepresentativeToParty(partyWish, districtWish, newRep);
		}
		void normalRound::UpdateVote(citizen*const civil, int partySerialNumber)
		{
			 party* const tmpPartyChoise = _allPartiesArr.getPartyBySerialnum(partySerialNumber);
			civil->setPartyChoise(tmpPartyChoise);
			civil->setVote();
		}

		void normalRound::calclateTotalResult()
		{
			int amountOfDistricts = _allDistricts.getAmountOfDistricts();
			for (int k = 0; k < amountOfDistricts; ++k)
			{
				if(typeid(*this)==typeid(normalRound))
					_allDistricts[k]->calculateVotesInDist(_allPartiesArr, static_cast<int>(roundType::normalR));
				else
					_allDistricts[k]->calculateVotesInDist(_allPartiesArr, static_cast<int>(roundType::simpleR));
			}
		}

		void normalRound::save(ostream& out)const
		{
			_allDistricts.save(out);
		   	_allVoters.save(out);
			_allPartiesArr.save(out);
			keepHolesAfterSave(out);
			if(!out.good())
				throw FileException("The file did not saved properly.");
		 }

		void normalRound::keepHolesAfterSave(ostream& out)const
		{
			_allDistricts.keepHolesAfterSave(out);
			_allVoters.keepHolesAfterSave(out);

		}
		 void normalRound::setHolesAfterLoad(istream& in)
		 {
			 _allDistricts.setHolesAfterLoad(in, *this);
			 _allVoters.setHolesAfterLoad(in, *this);
			 if (!in.good())
				 throw FileException("The file did not loaded properly.");
		 } 
	}