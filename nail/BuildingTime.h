#ifndef __NAILBUILDINGTIME__
#define __NAILBUILDINGTIME__

namespace nail{

class BuildingTime
{
private:
	static const char ENG_MONTHS[][4];
	static bool st_implemented;

	int getMonth(const std::string& mon)
	{
		for(int i=1; i<=12; i++)
		{
			if( mon.compare(ENG_MONTHS[i])==0 )
				return i;
		}

		throw NAIL_EXPCEPTION_1("unable to get month");
		return -1;
	}


public:
	BuildingTime()
	{
		if(st_implemented)
			throw NAIL_EXPCEPTION_1("class BuildingTime has been implemented");

		st_implemented = true;
	}


	DateTime operator()()
	{
		std::vector<int> _v;

		nail::StringPlus::Split _spDate(__DATE__, ' ');
		for(int i=0; i<_spDate.size(); i++)
		{
			if(_spDate[i].toString()=="")
				continue;

			if(_spDate[i].toString().size()==3)
				_v.push_back(getMonth( _spDate[i].toString() ));
			else
				_v.push_back(atoi(_spDate[i].c_str()));
		}

		nail::StringPlus::Split _spTime(__TIME__, ':');
		for(int i=0; i<_spTime.size(); i++)
		{
			if(_spTime[i].toString()=="")
				continue;

			_v.push_back(atoi(_spTime[i].c_str()));
		}

		if(_v.size()!=6)
			throw NAIL_EXPCEPTION_1("unable to get built time");

		DateTime _dt(_v[2], _v[0], _v[1], _v[3], _v[4], _v[5]);
		return _dt;
	}
};

bool BuildingTime::st_implemented = false;
const char BuildingTime::ENG_MONTHS[][4] ={"NIL","Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
BuildingTime buildingTime;

}//namespace


#endif
