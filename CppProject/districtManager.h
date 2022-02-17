#pragma once
#include "district.h"
#include "dividedDistrict.h"
namespace election
{
	//****************************************************************************************************************//
	// Helps us with the process of saving and loading districts, because they inherit from the same base class.
	//----------------------------------------------------------------------------------------------------------------//
	//  In the saving process we:
	//#1: Understand which kind of district we have.
	//#2: By using enum we put the district type in the binary file.
	//#3: We do the saving process according to the correct district by polimorphism.
	//-----------------------------------------------------------------------------------------------------------------//
	//  In the loading process we:
	//#1: read the district type that we have already save in advance.
	//#2: allocate and load it according to what we got.
	//#3: return it.
	//-----------------------------------------------------------------------------------------------------------------//
	//****************************************************************************************************************//


	enum class districtType { NormalDistrict = 0, DividedDistrict = 1 };
	class districtManager
	{
	public:
		static abstractDist* load(istream& in, normalRound& n);
		static void save(abstractDist* dist,ostream& out);
	};
}