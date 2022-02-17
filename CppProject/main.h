#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <cstring>
#include "simpleRound.h"
#include <fstream>
using namespace election;
enum class FirstOptions { newRound = 1, loadRound, Firstexit};

enum class mainOptions 
{ addnewDistrict = 1, addNewCitizen, addNewParty, addNewRepresentative, 
printDistricts,printCitizens,
printParties, addNewVote, printTheResult, exitNow, SaveTheElectionRound, loadTheElectionRound 
};
void mainMenu(normalRound** round);
void makeNewElectionRound(normalRound** round);
void loadElectionRound(normalRound**  round);
void SaveElectionRound(normalRound& round);
void casesFilter(int op, normalRound** state);//seperated cases for every input of the user
void addDistrict(normalRound& state);
void addCitizen(normalRound& state);
void addParty(normalRound& state);
void addRepresentative(normalRound& state);
void addVote(normalRound& state);

void isValidElectionRes(normalRound& state);
void isValidRepresentative(citizen* const newRep, int partyWish, int districtWish, normalRound& state);
void isValidVote(const citizen* newVote, int partySerialNumber, normalRound& state);
void isValidCitizen(const string& name, int id, int yearOfbirth, int DistrictNum, normalRound& state);
void isValidDistrict(const string& districtName, int numOfRepresentatives, normalRound& state);
void isValidParty(const string& partyName, citizen* const PartyCandidate, normalRound& state);
void isValidElectionDate(int electionDay, int electionMonth, int electionYear);

void printAllDistricts(normalRound& state);
void printResult(normalRound& state);
void printResInDiviedDist(normalRound& state, const dividedDistrict& dividedDist);
void PrintFinalResult(normalRound& state);
void printAllCitizens(normalRound& state);
void printAllParties(normalRound& state);