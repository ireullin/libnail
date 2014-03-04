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

	SHOW_VALUES("%s", nail::buildingTime().toString().c_str() );

	return 0;
}
