#include "normalRound.h"
namespace election
{
	districtArr::districtArr() :_districtsArr(DynamicArray<abstractDist*>()) {}
	void districtArr::addDistrict(abstractDist* const newDist)
	{
		_districtsArr.push_back(newDist);
	}
	abstractDist* const districtArr::getDistrictByName(const string& districtNameToFind)const
	{
		int _logs = _districtsArr.size();
		for (int i = 0; i < _logs; ++i)
		{
			if (strcmp((_districtsArr[i])->getDistrictName().c_str(), districtNameToFind.c_str()) == 0)
				return _districtsArr[i];
		}
		return nullptr;
	}
	abstractDist* const districtArr::getDistrictBySerialNumber(int serialNum)const
	{
		int _logs = _districtsArr.size();
		for (int i = 0; i < _logs; ++i)
		{
			if (_districtsArr[i]->getDistSerialNumber() == serialNum)
				return _districtsArr[i];
		}
		return nullptr;
	}
	void districtArr::addCitizenToDistrict(citizen* const newCitizen)
	{
		abstractDist* const tmp = getDistrictBySerialNumber(newCitizen->getDistrictNumber());
		tmp->addCitizen(newCitizen);
	}
	abstractDist* districtArr::operator[](int ind)
	{ 
		if (ind < 0 || ind >= _districtsArr.size())
			throw out_of_range("invalid array index");
		return _districtsArr[ind];
	}
	abstractDist* const districtArr::operator[](int ind)const
	{ 
		if (ind < 0 || ind >= _districtsArr.size())
			throw out_of_range("invalid array index");
		return _districtsArr[ind];
	}

	void districtArr::save(ostream& out)const
	{
		int _logs = _districtsArr.size();
		out.write(rcastcc(&_logs), sizeof(_logs));
		for (int i = 0; i < _logs; i++)
			districtManager::save(_districtsArr[i], out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}
	void districtArr::keepHolesAfterSave(ostream& out)const
	{
		int _logs = _districtsArr.size();

		for (int i = 0; i < _logs; i++)
			_districtsArr[i]->keepHolesAfterSave(out);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}

	void districtArr::load(istream& in, normalRound& n)
	{
		int totalDistrictsToAdd;
		in.read(rcastc(&totalDistrictsToAdd), sizeof(totalDistrictsToAdd));
		for (int i = 0; i < totalDistrictsToAdd; i++)
		{
			abstractDist* tmpDist= districtManager::load(in, n);
			if (!in.good())
				throw FileException("The file did not loaded properly.");
			addDistrict(tmpDist);
		}
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}

	void districtArr::setHolesAfterLoad(istream& in, normalRound& n)
	{
		int _logs = _districtsArr.size();
		for (int i = 0; i < _logs; i++)
				_districtsArr[i]->setHolesAfterLoad(in, n);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}

	districtArr::districtArr(istream& in, normalRound& n):_districtsArr(DynamicArray<abstractDist*>())
	{
		
		load(in,n);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}
}