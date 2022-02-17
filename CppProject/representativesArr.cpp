#include "normalRound.h"
namespace election
{
	representativesArr::representativesArr(int amountOfDists) :DynamicArray<citizensArr>(amountOfDists)
	{
		if(amountOfDists < 0)
			throw invalid_argument("amountOfDists can't be a negative number.");
	}
	representativesArr::representativesArr(): DynamicArray<citizensArr>(){}


	void representativesArr::addRepresentativeToDist(citizen* const newRep, int joinDistrictSerialNumber)
	{
		if (joinDistrictSerialNumber > size())
				resizeToAspecificPhy_Size((joinDistrictSerialNumber + 1 )* 2);

		if (joinDistrictSerialNumber + 1 > _logicalSize)
			_logicalSize = joinDistrictSerialNumber+1;
		_arr[joinDistrictSerialNumber].addCitizen(newRep);
		
	}

	void representativesArr::updateAmountOfDistrictsAndResize(int amountOfDistrictsToUpdate)
	{
		if (amountOfDistrictsToUpdate > size())
			resize();

		_logicalSize = amountOfDistrictsToUpdate;
	}
	void representativesArr::save(ostream& out)const
	{
		int _logs = size();
		out.write(rcastcc(&_logs), sizeof(_logs));
		for (int i = 0; i < _logs; i++)
				_arr[i].save(out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}

	void representativesArr::keepHolesAfterSave(ostream& out)const
	{
		int _logs = size();
		for (int i = 0; i < _logs; i++)
				_arr[i].keepHolesAfterSave(out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}

	void representativesArr::load(istream& in, normalRound& n)
	{
		int _logs;
		int amountOfDists = n.getAmountOfDistricts();
		updateAmountOfDistrictsAndResize(amountOfDists);
		in.read(rcastc(&_logs), sizeof(_logs));
		for (int i = 0; i < _logs; i++)
		{
			_arr[i].load( in, n);
			if (!in.good())
				throw FileException("The file did not loaded properly.");
		}
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}

	void representativesArr::setHolesAfterLoad(istream& in, normalRound& n)
	{
		int _logs = size();
		for (int i = 0; i < _logs; i++)
				_arr[i].setHolesAfterLoad(in, n);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}
}