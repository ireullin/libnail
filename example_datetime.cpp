/*******************************************************************************************

the program result.

Enter function main
example_datetime.cpp(22) shows "_dt1=2014/03/02 19:32:56.227 total second=1393759976.227000"
example_datetime.cpp(25) shows "_dt1=2014/03/25 19:34:01.227 total second=1395747241.227000"
example_datetime.cpp(29) shows "_dt2=2014-3-25_23:17:25.0"
example_datetime.cpp(36) shows "_dt3=20031025"
example_datetime.cpp(40) shows "_dt4=2014/03/03 14:53:18.291 total second=1393829598.291000"
example_datetime.cpp(45) shows "_dt5=2014/03/03 18:04:59.598 total second=1393841099.598000"
example_datetime.cpp(50) shows "_dt5 is newer than _dt4"
example_datetime.cpp(63) shows "interval are total 0.133117 days, total, 3.194808 hours, total 191.688450 minutes, total 11501.307000 seconds"
example_datetime.cpp(71) shows "interval is 0 days 3 hours 11 minutes 41 seconds 307 milliseconds"
Leave function main

*******************************************************************************************/



#include "nail/nail.h"


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	nail::DateTime _dt1(2014, 3, 2, 19, 32, 56 , 227);
	SHOW_VALUES("_dt1=%s total second=%f", _dt1.toString().c_str(), _dt1.totalSecond() );
	_dt1.addSecond(65);
	_dt1.addDay(23);
	SHOW_VALUES("_dt1=%s total second=%f", _dt1.toString().c_str(), _dt1.totalSecond() );


	nail::DateTime _dt2(_dt1, 23, 17, 25);
	SHOW_VALUES(
		"_dt2=%d-%d-%d_%d:%d:%d.%d",
		_dt2.year(), _dt2.month(), _dt2.day(),
		_dt2.hour(), _dt2.minute(), _dt2.second(), _dt2.millisecond());


	nail::DateTime _dt3(2003, 10, 25);
	SHOW_VALUES("_dt3=%s", _dt3.toString(nail::TimeFormat::eightNumDate).c_str());


	nail::DateTime _dt4(1393829598.291);
	SHOW_VALUES("_dt4=%s total second=%f", _dt4.toString().c_str(), _dt4.totalSecond() );


	// it's same with nail::DateTime::now()
	nail::DateTime _dt5;
	SHOW_VALUES("_dt5=%s total second=%f", _dt5.toString().c_str(), _dt5.totalSecond() );


	if(_dt5 > _dt4 )
	{
		SHOW_VALUES("_dt5 is newer than _dt4");
	}
	else if(_dt5 == _dt4 )
	{
		SHOW_VALUES("_dt4 and _dt5 are equal");
	}
	else
	{
		SHOW_VALUES("_dt4 is newer than _dt5");
	}


	nail::DateTimeDiff _diff = _dt5 - _dt4;
	SHOW_VALUES("interval are total %f days, total, %f hours, total %f minutes, total %f seconds",
		_diff.tatolDay(),
		_diff.tatolHour(),
		_diff.tatolMinute(),
		_diff.tatolSecond()
		);
	

	SHOW_VALUES("interval is %d days %d hours %d minutes %d seconds %d milliseconds",
		_diff.day(),
		_diff.hour(),
		_diff.minute(),
		_diff.second(),
		_diff.millisecond()
		);


	nail::DateTime _dtBuilt = nail::buildingTime();
	SHOW_VALUES("this program was built at %s", _dtBuilt.toString().c_str() );

	return 0;
}
