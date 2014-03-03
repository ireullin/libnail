/*******************************************************************************************

the program result.

Enter function main
Enter function event
example_signal.cpp(9) shows "received signal 2" //when you press ctrl-c
Leave function event
Leave function main

*******************************************************************************************/



#include "nail/nail.h"


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	// assing a  date
	nail::DateTime _dt1(2014, 2, 27, 17, 8, 55);
	SHOW_VALUES("dt1=%s total second=%f", _dt1.toString().c_str(), _dt1.totalSecond() );

	// it's now
	 //nail::TimeFormat::standardTime 
	nail::DateTime _dt2(2014,3,3,14,53,18,291);
	SHOW_VALUES("dt2=%s total second=%f", _dt2.toString().c_str(), _dt2.totalSecond() );

	nail::DateTimeDiff _diff = _dt2 - _dt1;
	SHOW_VALUES("interval=%d days %d hours %d minutes %d seconds %d milliseconds total seconds=%d",
		_diff.day(),
		_diff.hour(),
		_diff.minute(),
		_diff.second(),
		_diff.millisecond(),
		_diff.tatolSecond()
		);


	return 0;
}
