/***************************************************************************************************************
A date time class provide you to handle date and time.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILDATETIME__
#define __NAILDATETIME__

namespace nail{

class DateTime;
class DateTimeDiff
{
private:
	friend class DateTime;
	double m_timet;
	
	/// Only be constructed by DataTime.
	DateTimeDiff(double timet)
		:m_timet(timet)
	{
	}

public:
	/// Partial of milliseconds.
	int millisecond ()
	{
		double _intpart;
		double _fractpart = modf(m_timet, &_intpart);
		double _milsec = (_fractpart+0.0005)*1000.0f; // round off
		return (int)_milsec;
	}

	int second()		
	{
		int _sur1	= (int)floor(m_timet) % (24*60*60);
		int _sur2	= _sur1 % (60*60);
		int _sec	= _sur2 % (60);
		return _sec;
	}
	
	/// Partial of Minutes.
	int minute()		
	{
		int _sur1	= (int)floor(m_timet) % (24*60*60);
		int _sur2	= _sur1 % (60*60);
		int _min	= _sur2 / (60);
		return _min;
	}
	
	/// Partial of Hours.
	int hour()			
	{
		int _sur1	= (int)floor(m_timet) % (24*60*60);
		int _hour	= _sur1 / (60*60);
		return _hour;
	}
	
	/// Partial of Days.
	int day()
	{
		int _day	= (int)floor(m_timet) / (24*60*60);
		return _day;
	}
	
	/// Tatol seconds.
	double tatolSecond(){return m_timet;}
	
	/// Total minutes.
	double tatolMinute(){return m_timet/60;}
	
	/// Total hours.
	double tatolHour()	{return m_timet/(60*60);}
	
	/// Total days.
	double tatolDay()	{return m_timet/(60*60*24);}
};


class DateTime
{
private:
	typedef struct tm TM;
	
	time_t m_timet;
	int m_milsec;
	
	TM* getTm(){return localtime(&m_timet);}

	void init(int year, int month, int day, int hour, int minute, int second, int milsec)
	{
		if(milsec>999 || milsec<0)
			throw NAIL_EXPCEPTION_1("milsec can't bigger than 1000");

		m_milsec = milsec;

		TM _tm;
		memset(&_tm, 0, sizeof(TM));
		_tm.tm_year = year-1900;
		_tm.tm_mon	= month-1;
		_tm.tm_mday = day;
		_tm.tm_hour = hour;
		_tm.tm_min	= minute;
		_tm.tm_sec	= second;
		m_timet = mktime(&_tm);
	}

public:
	DateTime(int year, int month, int day, int hour, int minute, int second, int milsec=0)
	{init(year, month, day, hour, minute, second, milsec);}


	DateTime(DateTime& dt, int hour, int minute, int second, int milsec=0)
	{init(dt.year(), dt.month(), dt.day(), hour, minute, second, milsec);}


	DateTime(int year, int month, int day)
	{init(year, month, day, 0,0,0,0);}


	DateTime(double totalSecond)
	{
		double _intpart;
		double _fractpart = modf(totalSecond, &_intpart);

		m_timet = (int)_intpart;
		m_milsec = (_fractpart+0.0005)*1000.0f; // round off
	}
	

	/// construct with current time.
	DateTime()
	{
		struct timeb _tmb;    
		ftime(&_tmb);
		m_timet = _tmb.time;
		m_milsec = _tmb.millitm;
	}

	~DateTime()
	{
	}

	/// Add seconds to current time.
	void addSecond(int sec)	{m_timet += sec;}
	
	/// Add minutes to current time.
	void addMinute(int min)	{addSecond(min*60);}
	
	/// Add Hours to current time.
	void addHour(int hour)	{addMinute(hour*60);}
	
	/// Add days to current time.
	void addDay(int day)	{addHour(day*24);}
	
	/// Total seconds from 1900/1/1
	double totalSecond()	
	{return (double)m_timet + (double)millisecond()/1000.0f;}
	
	/// Partial of milliseconds.
	int millisecond ()		{return m_milsec;}
	
	/// Partial of seconds.
	int second()			{return getTm()->tm_sec;}
	
	/// Partial of minutes.
	int minute()			{return getTm()->tm_min;}
	
	/// Partial of hours.
	int hour()				{return getTm()->tm_hour;}
	
	/// Partial of days.
	int day()				{return getTm()->tm_mday;}
	
	/// Partial of months.
	int month()				{return getTm()->tm_mon+1;}
	
	/// Partial of years.
	int year()				{return getTm()->tm_year+1900;}
	
	/// Convert the current time to default string format. 
	/// Ex. 2011/06/03 12:20:23.456
	std::string toString()
	{
		char _acBuff[30];
		memset(&_acBuff[0], 0, sizeof(_acBuff));
		sprintf( _acBuff, "%04d/%02d/%02d %02d:%02d:%02d.%03d", 
			year(),
			month(),
			day(),
			hour(),
			minute(),
			second(),
			millisecond());
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

	/// Convert the current time to string with appointed format. 
	template <typename X>
	std::string toString(X format)
	{
		return format(
			year(),
			month(),
			day(),
			hour(),
			minute(),
			second(),
			millisecond());
	}

	/// Get current time with default format.
	static DateTime now()
	{
		DateTime _dt;
		return _dt;
	}


	/// Time difference with two DateTimes.
	DateTimeDiff operator-(DateTime& dt)
	{
		double _diff = this->totalSecond() - dt.totalSecond();
		return DateTimeDiff( fabs(_diff) );
	}

	bool operator<(const DateTime& dt) const
	{
		if(this->m_timet==dt.m_timet)	return this->m_milsec<dt.m_milsec;
		else							return this->m_timet<dt.m_timet;
	}
		
	bool operator>(const DateTime& dt) const
	{
		if(this->m_timet==dt.m_timet)	return this->m_milsec>dt.m_milsec;
		else							return this->m_timet>dt.m_timet;
	}

	bool operator<=(const DateTime& dt) const
	{
		if(this->m_timet==dt.m_timet)	return this->m_milsec<=dt.m_milsec;
		else							return this->m_timet<=dt.m_timet;
	}

	bool operator>=(const DateTime& dt) const
	{
		if(this->m_timet==dt.m_timet)	return this->m_milsec>=dt.m_milsec;
		else							return this->m_timet>=dt.m_timet;
	}

	bool operator==(const DateTime& dt) const
	{
		if(this->m_timet==dt.m_timet)	return this->m_milsec==dt.m_milsec;
		else							return false;
	}
	
};

}
#endif
