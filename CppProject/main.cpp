//Yagil Sofer 205433808
//Eden Natanzon 205688153
#include "main.h"
int main()
{
	int op = 0;
	normalRound* election = nullptr;
	cout << "1. Create new election round" << endl;
	cout << "2. Load exist election round" << endl;
	cout << "3. Exit" << endl;
	cin >> op;
	while (op != 1 && op != 2 && op != 3)
	{
		cout << "Wrong input" << endl;
		cin >> op;
	}
	switch (op)
	{
		case static_cast<int>(FirstOptions::newRound):
		{
			try {
				makeNewElectionRound(&election);
			}
			catch (exception& ex) {
				cout << "Error: " << ex.what() << endl;
			}		
			break;
		}
		case static_cast<int>(FirstOptions::loadRound):
		{
			try{
				loadElectionRound(&election);
				mainMenu(&election);
			}
			catch(exception& ex) {
				cout << "Error: " << ex.what() << endl;
			}
			break;
		}
		case static_cast<int>(FirstOptions::Firstexit):
		{
			cout << "Exit!" << endl;
			if (election)
				delete election;
			exit(0);
		}
	}
	return 0;
}
void makeNewElectionRound(normalRound** election)
{
	int electionDay, electionMonth, electionYear;
	cout << "Enter the election date: day/month/year" << endl;
	cin >> electionDay >> electionMonth >> electionYear;
	bool ok = false;
	while (!ok)
	{
		try {
			isValidElectionDate(electionDay, electionMonth, electionYear);
			ok = true;
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
			cout << "Enter the election date: day/month/year" << endl;
			cin >> electionDay >> electionMonth >> electionYear;
		}
	}
	cout << "Enter the election type: " << endl;
	cout << "0. normal election" << endl << "1. simple election" << endl;
	int electionType;
	cin >> electionType;
	while (electionType != 0 && electionType != 1)
	{
		cout << "Wrong input" << endl;
		cin >> electionDay;
	}
	normalRound* _election = nullptr;

		if (electionType == static_cast<int>(roundType::normalR))
		{
			try {
				*election = new normalRound(electionDay, electionMonth, electionYear);
			}
			catch (bad_alloc& ex) {
				cout << "Error: " << ex.what() << endl;
				exit(1);
			}
			catch (exception& ex) {
				cout << "Error: " << ex.what() << endl;
			}
		}
		else
		{
			int amountOfTotalElectors;
			cout << "Enter the amount of total electors in the country" << endl;
			cin >> amountOfTotalElectors;
			while (amountOfTotalElectors <= 0)
			{
				cout << "The country needs at least one representative! it is a democracy!";
				cin >> amountOfTotalElectors;
			}
			try {
				*election = new simpleRound(amountOfTotalElectors, electionDay, electionMonth, electionYear);
			}
			catch (bad_alloc& ex) {
				cout << "Error: " << ex.what() << endl;
				exit(1);
			}
			catch (exception& ex) {
				cout << "Error: " << ex.what() << endl;

			}
		}
	
	cout << "Welcome to election: " << electionDay << "/" << electionMonth << "/" << electionYear << "!" << endl << endl;
	mainMenu(election);//we need to to free in the end
}
	void loadElectionRound(normalRound** round)
	{
	string fileName;
	cout << "Enter File name to load" << endl;
	cin.ignore();
	cin >> fileName;
	ifstream infile(fileName, ios::binary);
	if (!infile)
	{
		cout << "Error: File did not open." << endl;
		exit(1);
	}
	roundType type;
	int electionDay, electionMonth, electionYear;
	infile.read(rcastc(&type), sizeof(type));

	infile.read(rcastc(&electionDay), sizeof(electionDay));
	infile.read(rcastc(&electionMonth), sizeof(electionMonth));
	infile.read(rcastc(&electionYear), sizeof(electionYear));
	
	if (type == roundType::normalR)
	{
		try {
			*round = new normalRound( infile, electionDay, electionMonth, electionYear);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
			exit(1);
		}
	}
	else
	{
		int amountOfRepsInSimpleRound;
		infile.read(rcastc(&amountOfRepsInSimpleRound), sizeof(amountOfRepsInSimpleRound));
		try {
			*round = new simpleRound( infile, amountOfRepsInSimpleRound, electionDay, electionMonth, electionYear);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
			exit(1);
		}
	}
	
	if (!infile.good())
		cout << "ERROR. file not loaded." << endl;
	else
		cout << "File loaded successfully" << endl;
	 infile.close();	 
}
void SaveElectionRound(normalRound& round)
{
	string fileName;
	cout << "Enter File name to save" << endl;
	cin.ignore();
	cin >> fileName;
	ofstream outfile(fileName, ios::binary);
	if (!outfile)
	{
		cout << "ERROR. file not opened" << endl;
		return;
	}
	roundType type;
	int amountOfRepsInSimpleRound;
	int electionDay, electionMonth, electionYear;
	if (typeid(round) == typeid(normalRound))
		type = roundType::normalR;
	else
		type = roundType::simpleR;

	outfile.write(rcastcc(&type), sizeof(type));

	electionDay = round.getElectionDay();
	electionMonth = round.getElectionMonth();
	electionYear = round.getElectionYear();

	outfile.write(rcastcc(&electionDay), sizeof(electionDay));
	outfile.write(rcastcc(&electionMonth), sizeof(electionMonth));
	outfile.write(rcastcc(&electionYear), sizeof(electionYear));

	if (type == roundType::simpleR)
	{
		amountOfRepsInSimpleRound = round.getAllDistricts().getDistrictBySerialNumber(0)->getAmountOfRepsInDist();
		outfile.write(rcastcc(&amountOfRepsInSimpleRound), sizeof(amountOfRepsInSimpleRound));
	}
	try {
		round.save(outfile);
	}
	catch (exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}

	bool flag = outfile.good();
	outfile.close();
	if (!flag)
		cout << "ERROR. file not saved." << endl;
	else
		cout << "File saved successfully" << endl;
}
void mainMenu(normalRound** round)
{
	int op = 0;
	while (op != 10)
	{
		cout << "1.  Add district" << endl;
		cout << "2.  Add citizen" << endl;
		cout << "3.  Add party" << endl;
		cout << "4.  Add a representative citizen" << endl;// here we got to add a citizen that will be a representative in a party in a district
		cout << "5.  Show all districts" << endl;
		cout << "6.  Show all citizens" << endl;
		cout << "7.  Show all parties" << endl;
		cout << "8.  Vote" << endl;
		cout << "9.  Show election results" << endl;// we need to handle it somehow TODO
		cout << "10. Exit" << endl;
		cout << "11. Save election Round" << endl;
		cout << "12. Load exist election round" << endl;
		cin >> op;
		casesFilter(op,round);
		cout << endl;
	}
}
void casesFilter(int op, normalRound** state)
{
	switch (op)
	{	
	case static_cast<int>(mainOptions::addnewDistrict):
	{
		try {
			addDistrict(**state);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
		}
		break;
	}
	case static_cast<int>(mainOptions::addNewCitizen):
	{
		try{
			addCitizen(**state);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
		}
		break;
	}
	case static_cast<int>(mainOptions::addNewParty):
	{
		try {
			addParty(**state);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
		}
		break;
	}
	case static_cast<int>(mainOptions::addNewRepresentative):
	{
		try {
			addRepresentative(**state);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
		}
		break;
	}
	case static_cast<int>(mainOptions::printDistricts):
	{
		 printAllDistricts(**state);
		break;
	}
	case static_cast<int>(mainOptions::printCitizens):
	{
		 printAllCitizens(**state);
		break;
	}
	case static_cast<int>(mainOptions::printParties):
	{
		printAllParties(**state);
		break;
	}
	case static_cast<int>(mainOptions::addNewVote):
	{
		try {
			addVote(**state);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
		}
		break;
	}
	case static_cast<int>(mainOptions::printTheResult):
	{
		try {
			printResult(**state);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
		}
		break;
	}
	case static_cast<int>(mainOptions::exitNow):
	{
		cout << "ByeBye! See You In Two Months" << endl;
		if (state)
			delete *state;
		break;
	}
	case static_cast<int>(mainOptions::SaveTheElectionRound):
	{
		try{
			SaveElectionRound(**state);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
		}
		break;
	}
	case static_cast<int>(mainOptions::loadTheElectionRound):
	{
		if (state)
		{
			delete *state;
			*state = nullptr;
		}
		try {
			loadElectionRound(state);
		}
		catch (exception& ex) {
			cout << "Error: " << ex.what() << endl;
		}
		break;	
	}
	default:
	{
		cout << "Input needs to be a value between 1-10" << endl;
		break;
	}
	}
}

void addDistrict(normalRound& state)
{
	if (typeid(state) == typeid(simpleRound))
	{
		cout << "There are not districts in simple round" << endl;
		return;
	}
	int numOfRepresentatives;
	string districtName;
	int distType = -1;
	cout << "Please enter the district Name " << endl;
	cin.ignore();
	cin >> districtName;
	cout << "Please enter the number Of representatives" << endl;
	cin >> numOfRepresentatives;
	isValidDistrict(districtName, numOfRepresentatives, state);
	cout << "Please enter the District type" << endl;
	cout << "1. Normal district" << endl;
	cout << "2. Divided district" << endl;
	cin >> distType;
	while (distType != 1 && distType != 2)
	{
		cout << "Wrong input, try again" << endl;
		cin >> distType;
	}
	state.UpdateDistrictDetails(districtName, numOfRepresentatives, distType);
}


void addCitizen(normalRound& state)
{
	int id, yearOfbirth, DistrictNum;
	string name;
	cout << "Please enter: Name" << endl;
	cin.ignore();
	cin >> name;
	cout << "Please enter: ID, Year of birth(1900 - 2021), District number" << endl;
	cin >> id >> yearOfbirth >> DistrictNum;
	isValidCitizen(name, id, yearOfbirth, DistrictNum, state);
	state.UpdateCitizenDetails(name, id, yearOfbirth, DistrictNum);
}

void addParty(normalRound& state)
{
	string partyName;
	int partyCandidateId;
	cout << "Please enter the party Name" << endl;
	cin.ignore();
	cin >> partyName;
	cout << "Please enter the party candidate ID" << endl;
	cin >> partyCandidateId;
	citizen* const PartyCandidate = state.getCitizenFromBook(partyCandidateId);
	isValidParty(partyName, PartyCandidate, state);
	state.UpdatePartyDetails(partyName, PartyCandidate);
}

void addRepresentative(normalRound& state)
{
	int representativeID, partySerialNumber, districtSerialNumber;
	cout << "Enter representative ID, party serial number and district serial number" << endl;
	cin >> representativeID >> partySerialNumber >> districtSerialNumber;
	citizen* citiz = state.getCitizenFromBook(representativeID);
	isValidRepresentative(citiz, partySerialNumber, districtSerialNumber, state);
	state.UpdateRepresentativeDetails(citiz, partySerialNumber, districtSerialNumber);
}

void addVote(normalRound& state)
{
	int citizenID, partySerialNumberToVote;
	cout << "Enter citizen ID and party serial Number" << endl;
	cin >> citizenID >> partySerialNumberToVote;
	citizen* citiz = state.getCitizenFromBook(citizenID);
	isValidVote(citiz, partySerialNumberToVote, state);
	state.UpdateVote(citiz, partySerialNumberToVote);
}

//******************************************************************************************//
                              //validations//
//******************************************************************************************//
void  isValidVote(const citizen* civil, int partySerialNumber, normalRound& state)
{
	if (civil == nullptr)
		throw CitizenException("Citizen has not found");
	
	if (civil->isVoted())
		throw CitizenException("Citizen can not vote twice");
	
	int amountOfparties = state.getAmountOfParties();
	if (!(partySerialNumber >= 0 && partySerialNumber < amountOfparties))
		throw out_of_range("Party serial number is not valid");
	
	if (state.getElectionYear()-civil->getYearOfBirth()<18)
		throw CitizenException("Citizen must be 18 years old or older");
}
void isValidRepresentative(citizen* const newRep, int partyWish, int districtWish, normalRound& state)
{
	if (!newRep)
		throw CitizenException("Citizen has not found");
	
	int amountOfDistricts = state.getAmountOfDistricts();
	if (typeid(state) == typeid(normalRound))
	{
		if (!(districtWish >= 0 && districtWish < amountOfDistricts))
			throw out_of_range("District number is not valid");
	}
	int amountOfparties = state.getAmountOfParties();
	if (!(amountOfparties >= 0 && partyWish < amountOfparties))
		throw out_of_range("Party number is not valid");

	if ((newRep->isRep()))
		throw CitizenException("The citizen is already a representative");
	
	if (newRep->isMainCandidate())
		throw CitizenException("The citizen is already a main Candidate");
}
void isValidDistrict(const string& districtName, int numOfRepresentatives, normalRound& state)
{
	if (numOfRepresentatives <= 0)//the minimum representatives at a district is 1
		throw DistrictException("Every districts should have at least one representative");
	
	if (state.getDistrictByName(districtName) != nullptr )//it means that the district is already exist
		throw DistrictException("District is already exist");
}
 void isValidCitizen(const string& name, int id, int yearOfbirth, int DistrictNum, normalRound& state)//add to citizen update function
{
	int amountOfDistricts = state.getAmountOfDistricts();
	if (state.getCitizenFromBook(id) != nullptr)//if the citizen already exist
		throw CitizenException("Citizen is already exist");
	
	if (id < 0)// if the ID is a negative number it is not valid
		throw invalid_argument("ID can't be a negative number");
	
	if (!(yearOfbirth >= 1900 && yearOfbirth <= 2021))//check year time line
		throw out_of_range("Your year of birth is not valid!, how old are you son?");
	
	if (typeid(state) == typeid(normalRound))
	{
		if (!(DistrictNum >= 0 && DistrictNum < amountOfDistricts))//check district serial number
			throw out_of_range("Wrong disctict number");
	}
	//check if ID 9 digits
	int howManyDig = 0;
	while (id > 0)
	{
		id = id / 10;
		howManyDig++;
	}
	if (howManyDig != 9)
		throw invalid_argument("Invalid ID");
}

void isValidParty(const string& partyName, citizen* const PartyCandidate, normalRound& state)
{
	if (state.getPartyByName(partyName) != nullptr)//check if the party name is already taken
		throw PartyException("The party is already exist");
	
	if (PartyCandidate == nullptr)
		throw PartyException("The main candidate you are trying to insert is not exist: Wrong ID");

	else if (PartyCandidate->isMainCandidate())
		throw PartyException("The main candidate you are trying to insert is already a main candidate on another party");
	
	else if (PartyCandidate->isRep())
		throw PartyException("The main candidate you are trying to insert is already a representative on another party");
}
 void isValidElectionRes(normalRound& state)
{
	int amountOfDistricts = state.getAmountOfDistricts();
	if (amountOfDistricts == 0)
		throw RoundException("Error! for The election Result, it is necessary to have at least one district");
	
	int amountOfParties = state.getAmountOfParties();
	if (amountOfParties == 0)
		throw RoundException("Error! for The election Result, it is necessary to have at least one party");
}
 void isValidElectionDate(int electionDay, int electionMonth, int electionYear)
 {
	 if (electionDay <= 0 || electionDay > 31)
		 throw out_of_range("invalid electionDay");
	 if (electionMonth <= 0 || electionMonth > 12)
		 throw out_of_range("invalid electionMonth");
	 if (electionYear <= 0)
		 throw out_of_range("invalid electionYear");

	 //Match between month and day
	 if ((electionMonth == 4) || (electionMonth == 6) || (electionMonth == 9) || (electionMonth == 1))//30 max
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

 void printAllDistricts(normalRound& state)
 {
	 int amountOfDists = state.getAmountOfDistricts();
	 if (typeid(state) == typeid(simpleRound))
	 {
		 cout << "There are Not districts in simple Round" << endl;
		 return;
	 }
	  for (int i = 0; i < amountOfDists; ++i)
	  {
		 if (typeid(*(state.getDistrictByIndex(i))) == typeid(district))
			 cout << "District type: United" << endl;
		 else
			 cout << "District type: Divided" << endl;
		 cout << *(state.getDistrictByIndex(i));
	  }
 }

 void printAllCitizens(normalRound& state)
 {
	 const citizensArr& citizensOfBook = state.getVotersBook().getVotersBook();
	 int amountOfCitizens = state.getVotersBook().getAmountOfTotalCitizens();
	 for (int i = 0; i < amountOfCitizens; ++i)
	 {
		 if (citizensOfBook[i])
			 cout << *(citizensOfBook[i]);
	 }
 }
 void printAllParties(normalRound& state)
 {
	 int amountOfParties = state.getAmountOfParties();
	 for (int i = 0; i < amountOfParties; ++i)
		 cout << *(state.getPartyBySerial(i));
 }
 void printResult(normalRound& state)
 {
	 isValidElectionRes(state);
	 int amountOfDistricts = state.getAmountOfDistricts();
	 cout << endl << endl;
	 state.calclateTotalResult();
	 int electionDate, electionMonth, electionYear;
	 electionDate = state.getElectionDay();
	 electionMonth = state.getElectionMonth();
	 electionYear = state.getElectionYear();
	 cout << "Election date: " << electionDate << '/' << electionMonth << "/" << electionYear << endl;
	 for (int i = 0; i < amountOfDistricts; ++i)
	 {
		 if (typeid(state) == typeid(normalRound))
		 {
			 cout << "District Name: " << state.getDistrictByIndex(i)->getDistrictName() << endl;
			 cout << "Gives: " << state.getDistrictByIndex(i)->getAmountOfRepsInDist() << endl;
		 }
		 if (typeid(*(state.getDistrictByIndex(i))) == typeid(district))
		 {
			 const district* tmpDist = static_cast<const district*>(state.getDistrictByIndex(i));
			 cout << "The party winner in the district is: " << tmpDist->getPartyWinner()->getPartyName() << endl;
			 cout << "The main candidate of this party is: " << tmpDist->getDistWinner()->getCitizenName() << endl;
		 }
		 if((typeid(*(state.getDistrictByIndex(i))) == typeid(dividedDistrict)))
		 {
			 const dividedDistrict* tmpDividedDist = static_cast<const dividedDistrict*>(state.getDistrictByIndex(i));
			 printResInDiviedDist(state,*tmpDividedDist);
		 }
		 cout << "The electors of the district are: " << endl;
		 int amountOfParties = state.getAmountOfParties();
		 for (int k = 0; k < amountOfParties; k++)
		 { 
			 if (state.getDistrictByIndex(i)->getKalpi(k).CheckIfAmountOfTotalVotesValid())
			 {
				 if (state.getDistrictByIndex(i)->getKalpi(k).get_gotFinalRepsInTheEnd())
				 {
					 cout << "The electors of party: " << state.getPartyBySerial(k)->getPartyName() << endl << "{" << endl;
					 const citizensArr& reps = state.getDistrictByIndex(i)->getDistReps().getRepsByInd(k);
					 int amountOfReps = reps.getAmountOfTotalCitizens();
					 for (int i = 0; i < amountOfReps; ++i)
					 {
						 if (reps[i])
							 cout << *(reps[i]);
					 }
					 cout << "}" << endl;
				 }
			 }
			 else
				 cout << "Error,there are not enough Representatives for party: " <<state.getPartyBySerial(k)->getPartyName() << endl << endl;
		 }
		 for (int j = 0; j < amountOfParties; j++)
		 {
			 const string par = state.getDistrictByIndex(i)->getKalpi(j).getCurrParty()->getPartyName();
			 int TotalVotesInParty = state.getDistrictByIndex(i)->getKalpi(j).getTotalVotesInParty();
			 int TotalVotesAmountInDist = state.getDistrictByIndex(i)->getTotalVotesAmountInDist();
			 int AmountOfRepsInDist = state.getDistrictByIndex(i)->getAmountOfRepsInDist();
			 double percent = 0;
			 if (TotalVotesAmountInDist != 0)
				 percent = ((static_cast<double>(TotalVotesInParty) / TotalVotesAmountInDist)) * 100;
			 cout << par << " got: " << TotalVotesInParty << " votes and won " << percent << "% of the votes." << endl;
		 }
		 int amountOfCitizenInCurrDist = state.getDistrictByIndex(i)->getAmountOfCitizensInDist();
		 if (amountOfCitizenInCurrDist != 0)
		 {
			 double totalVotesInDistPercents = state.getDistrictByIndex(i)->getVotingPercentageInDist();
			 cout << "Total votes in this district: " << totalVotesInDistPercents << "%" << endl;
		 }
		 else
			 cout << "There are no citizens in this district" << endl;
		 cout << "***************************************************************************" << endl;
	 }
	 if(typeid(normalRound)==typeid(state))
		 PrintFinalResult(state);
 }

 void PrintFinalResult(normalRound& state)
 {
	 const partyArr& allTheParties = state.getAllParties();
	 const districtArr& allTheDistricts = state.getAllDistricts();
	 int amountOfParties = allTheParties.getAmountOfParties();
	 kalpies finalRes;
	 finalRes.initKalpies(allTheParties);

	 for (int i = 0; i < allTheDistricts.getAmountOfDistricts(); i++)// we get from every district their final result and insert them to the kalpi
		 allTheDistricts.getDistrictBySerialNumber(i)->addElectors(finalRes);
	 finalRes.sortKalpies(static_cast<int>(howToSort::sortByElectors));
	 for (int i = 0; i < allTheParties.getAmountOfParties(); ++i)
	 {
		 if (i == 0)
		 {
			 cout << "The winner is: " << finalRes[i].getCurrParty()->getPartyCandidate()->getCitizenName() << " ";
			 cout << finalRes[i].getCurrParty()->getPartyName() << ": got " << finalRes[i].getTotalVotesInParty();
			 cout << " electors, and " << finalRes[i].getCurrParty()->getAmountOfTotalVotes() << " total votes from citizens." << endl;
			 cout << "***************************************************************************" << endl;
		 }
		 else
		 {
			 cout << finalRes[i].getCurrParty()->getPartyCandidate()->getCitizenName() << ": got " << finalRes[i].getTotalVotesInParty();
			 cout << " electors, and " << finalRes[i].getCurrParty()->getAmountOfTotalVotes() << " total votes from citizens." << endl;
		 }
	 }
 }
 void printResInDiviedDist(normalRound& state, const dividedDistrict& dividedDist)
 {
	 int amountOfParties = state.getAmountOfParties();
	 for (int i = 0; i < amountOfParties; i++)
	 {
		 int electorsCount = dividedDist.getElectorsElectedPerParty()[i].getTotalVotesInParty();
		 if (electorsCount > 0||typeid(state)==typeid(simpleRound))
		 {
			const string partyCandidateName = dividedDist.getElectorsElectedPerParty()[i].getCurrParty()->getPartyCandidate()->getCitizenName();
			if (typeid(state) == typeid(simpleRound))
				cout << dividedDist.getElectorsElectedPerParty()[i].getCurrParty()->getPartyName() << " and its main candidate: ";
			 cout << partyCandidateName << " got: ";
		     cout << electorsCount << " electors." << endl;
		 }
	 }
 }

