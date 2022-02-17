#include "normalRound.h"
namespace election
{
	book::~book()
	{
		for (int i = 0; i < _theVotersBook.getAmountOfTotalCitizens(); ++i)
			delete _theVotersBook[i];

	}
	void book::save(ostream& out)const
	{
		_theVotersBook.save(out,true);
		 if(!out.good())
			 throw FileException("The file did not saved properly.");
	}
	void book::keepHolesAfterSave(ostream& out)const
	{
		_theVotersBook.keepHolesAfterSave(out,true);
		if (!out.good())
			throw FileException("The file did not saved properly.");
	}
	void book::setHolesAfterLoad(istream& in, normalRound& n)
	{
		_theVotersBook.setHolesAfterLoad(in,n);
		if (!in.good())
			throw FileException("The file did not loaded properly.");
	}

	book::book(istream& in, normalRound& n): _theVotersBook(in,n,true)
	{
	}
}