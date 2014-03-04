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

	nail::ExtendItem _item1("  adfdDDDDbbbe7482DeSSs ");

	SHOW_VALUES("%s", _item1.trimRight().padLeft(50,'-').toLower().c_str());
	SHOW_VALUES("%s", _item1.c_str());
	SHOW_VALUES("%d", _item1.toInt());
	SHOW_VALUES("%f", _item1.toDouble());

	return 0;
}
