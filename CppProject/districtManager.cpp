#include "normalRound.h"
namespace election
{

	abstractDist* districtManager::load(istream& in, normalRound& n)
	{
		districtType type;
		in.read(rcastc(&type), sizeof(type));
		if (!in.good())
			throw FileException("The file did not loaded properly.");
		if(in.good())
		{

			switch (type)
			{
			case districtType::NormalDistrict:
			{
				district* tmpDistrict = nullptr;
				try{
					 tmpDistrict = new district(in, n);
				}
				catch (exception& ex) {
					cout << "Error: " << ex.what() << endl;
					exit(1);
				}
				return tmpDistrict;
			}
			case districtType::DividedDistrict:
			{
				dividedDistrict* tmpDividedDistrict = nullptr;
				try {
					 tmpDividedDistrict = new dividedDistrict(in, n);
				}
				catch (exception& ex) {
					cout << "Error: " << ex.what() << endl;
					exit(1);
				}
				return tmpDividedDistrict;
			}
			}
		}
			return nullptr;
	}

	void districtManager::save(abstractDist* dist,ostream& out)
	{
		if (typeid(*dist) == typeid(district))
		{
			districtType type = districtType::NormalDistrict;
			out.write(rcastcc(&type), sizeof(type));
		}
		else
		{
			districtType type = districtType::DividedDistrict;
			out.write(rcastcc(&type), sizeof(type));
		}
		bool flag = out.good();
		if (flag)
			dist->save(out);
		else
			throw FileException("The file did not saved properly.");
	}
}