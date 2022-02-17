#include "normalRound.h"
namespace election
{
		citizensArr::citizensArr():_citizenArr(DynamicArray<citizen*>()){}
		void citizensArr::addCitizen(citizen* const newCitiz)
		{
			_citizenArr.push_back(newCitiz);
		}
		 const citizensArr& citizensArr::operator=(const citizensArr& other)
		 {
			 _citizenArr.operator=(other._citizenArr);
			 return *this;
		 }
		citizen* const citizensArr::lookForCitizen(int IDToLookFor)const//return nullptr if does not exist
		{
			for (int i = 0; i < _citizenArr.size(); ++i)
			{
				if (getCitizen(i)->getID() == IDToLookFor)
					return getCitizen(i);
			}
			return nullptr;
		}
		citizen* const citizensArr::getCitizen(int ind)const
		{
			if (ind < 0 || ind >= _citizenArr.size())
				throw out_of_range("invalid array index");
			return _citizenArr[ind]; 
		}
		citizen* const citizensArr::operator[](int ind)const 
		{ 
			if (ind < 0 || ind >= _citizenArr.size())
				throw out_of_range("invalid array index");
			return _citizenArr[ind];
		}
		citizen* citizensArr::operator[](int ind)
		{
			return _citizenArr[ind];
		}

		void citizensArr::save(ostream& out, bool isSavedFromBook)const
		{
			int _logs = getAmountOfTotalCitizens();
			out.write(rcastcc(&_logs), sizeof(_logs));
			if (isSavedFromBook)
			{
				for (int i = 0; i < _logs; i++)
						_citizenArr[i]->save(out);
			}
			else// in case we save not from book
			{
				for (int i = 0; i < _logs; i++)
				{
					int id = _citizenArr[i]->getID();
					out.write(rcastcc(&id), sizeof(id));
				}
			}
			if (!out.good())
				throw FileException("The file did not saved properly.");
		}	

		void citizensArr::keepHolesAfterSave(ostream& out, bool isSavedFromBook)const
		{
			int _logs = getAmountOfTotalCitizens();
			if (isSavedFromBook)
			{
				for (int i = 0; i < _logs; i++)
					_citizenArr[i]->keepHolesAfterSave(out);
			}
			if (!out.good())
				throw FileException("The file did not saved properly.");
		}
		void citizensArr::load(istream& in, normalRound& n, bool isLoadFromBook)
		{
			int _logs;
			in.read(rcastc(&_logs), sizeof(_logs));
			for (int i = 0; i < _logs; i++)
			{
				citizen*  tmpCit;
				if (isLoadFromBook)
				{
					try {
						tmpCit = new citizen(in, n);
					}
					catch (exception& ex) {
						cout << "Error: " << ex.what() << endl;
						exit(1);
					}
				}
				else
				{
					int id;
					in.read(rcastc(&id), sizeof(id));
					 tmpCit =n.getCitizenFromBook(id);
				}
				if (!in.good())
					throw FileException("The file did not loaded properly.");
				addCitizen(tmpCit);
			}
			if (!in.good())
				throw FileException("The file did not loaded properly.");
		}
		void citizensArr::setHolesAfterLoad(istream& in, normalRound& n)
		{
			int _logs = getAmountOfTotalCitizens();
			for (int i = 0; i < _logs; i++)
			{
				_citizenArr[i]->setHolesAfterLoad(in, n);
				if (!in.good())
					throw FileException("The file did not loaded properly.");
			}
			if (!in.good())
				throw FileException("The file did not loaded properly.");
		}
		citizensArr::citizensArr(istream& in, normalRound& n, bool isLoadFromBook):_citizenArr(DynamicArray<citizen*>())
		{
			load(in,n, isLoadFromBook);
			if (!in.good())
				throw FileException("The file did not loaded properly.");
		}

};
