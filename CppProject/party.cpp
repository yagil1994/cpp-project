#include "normalRound.h"
namespace election
{
	party::party(citizen*  partyCandidate, const string& partyName, int partySerialNumber,int amountOfDists)
		: _partyCandidate(partyCandidate), _partySerialNumber(partySerialNumber),
	     _partyName(partyName), _PartyRepresentatives(amountOfDists), _totalVotesToParty(0)
	{
		if (partySerialNumber < -1)
			throw invalid_argument("partySerialNumber can't be lower then -1");

		if(amountOfDists < 0)
			throw invalid_argument("amountOfDists can't be a negative number");
	}//ctor
		
		party::~party()//dtor
		{
		}
		 ostream& operator<<(ostream& os, const party& p)
		 {
			 os << "Party Name: " << p._partyName << endl << "Party Serial Number: " << p._partySerialNumber << endl << "Main Party Candidate: " <<endl<< *(p._partyCandidate) << endl;
			 os << "The representatives of the party are: " << endl << endl;
			 int amountOfReps = p._PartyRepresentatives.getAmountOfReps();
			 for (int i = 0; i < amountOfReps; ++i)
			 {
				 if (amountOfReps > 0)
				 {
					 cout << "Representatives of district: " << i << endl << "{" << endl;
					 int amountOfRepsInDist = p._PartyRepresentatives[i].getAmountOfTotalCitizens();
					 for (int j = 0; j < amountOfRepsInDist; j++)
					 {	
						 const citizen* tmp = p._PartyRepresentatives[i].getCitizen(j);
						 if (tmp)
						   cout << *tmp;
					 }
					 cout << "}" << endl;
				 }
			 }
			 return os;
		 }
		 party::party(const party& other):party()//copy ctor
		 {
			 *this = other;
		 }

		 const party& party::operator=(const party& other)
		 {
			 if (this != &other)
			 {
				 _partyCandidate = other._partyCandidate;
				 _partySerialNumber = other._partySerialNumber;
				 _partyName = other._partyName;
				 _totalVotesToParty = other._totalVotesToParty;
			 }
			 return *this;
		 }

		 bool party::operator==(const party& other)const
		 {
			 bool flag = true;
			 if (_partySerialNumber != other._partySerialNumber)
				 flag = false;
			 if (_totalVotesToParty != other._totalVotesToParty)
				 flag = false;
			 if (strcmp(_partyName.c_str(), other._partyName.c_str()))
				 flag = false;
			 return flag;
		 }
		 void party::updateRepsArrSize(int amountOfDistrictsToUpdate)
		 {
			 _PartyRepresentatives.updateAmountOfDistrictsAndResize(amountOfDistrictsToUpdate);
		 }
		 void party::addNewRepresentativeToParty(citizen* const newRep, int districtToJoin)
		 {
			_PartyRepresentatives.addRepresentativeToDist(newRep, districtToJoin); 
		 }
		
		 void party::save(ostream& out)const
		 {
			 int partyCandidateID = -1;
			 if (_partyCandidate != nullptr)
				 partyCandidateID = _partyCandidate->getID();
			 out.write(rcastcc(&partyCandidateID), sizeof(partyCandidateID));

			 int stringLen = _partyName.size();
			 out.write(rcastcc(&stringLen), sizeof(stringLen));
			 out.write(rcastcc(_partyName.c_str()), sizeof(char) * stringLen);

			 out.write(rcastcc(&_partySerialNumber), sizeof(_partySerialNumber));

			 int amountOfDistricts = _PartyRepresentatives.getAmountOfReps();
			 out.write(rcastcc(&amountOfDistricts), sizeof(amountOfDistricts));
			 _PartyRepresentatives.save(out);

			 if (!out.good())
				 throw FileException("The file did not saved properly.");
		 }

		 void party::load(istream& in, normalRound& n,bool sentFromCtor)
		 {
			 int partyCandidateID;
			 in.read(rcastc(&partyCandidateID), sizeof(partyCandidateID));
			 if (partyCandidateID != -1)
				 _partyCandidate = n.getCitizenFromBook(partyCandidateID);

			 int stringLen;
			 in.read(rcastc(&stringLen), sizeof(stringLen));

			 char* temp = new char[sizeof(char) * (stringLen + 1)];
			 in.read(temp, sizeof(char) * stringLen);
			 temp[stringLen] = '\0';
			 _partyName = temp;
			 delete[] temp;

			 in.read(rcastc(&_partySerialNumber), sizeof(_partySerialNumber));
			 
			 int amountOfDistricts;
			 in.read(rcastc(&amountOfDistricts), sizeof(amountOfDistricts));

			 if(!sentFromCtor)
				 _PartyRepresentatives.load(in,n);

			 if (!in.good())
				 throw FileException("The file did not loaded properly.");
		 }
	
		 party::party(istream& in, normalRound& n, int amountOfDists)
			 :_partyCandidate(nullptr), _partySerialNumber(0), _partyName(""),
			  _PartyRepresentatives(amountOfDists), _totalVotesToParty(0)
		 {

			load(in,n,false);
			if (!in.good())
				throw FileException("The file did not loaded properly.");
		 }
}