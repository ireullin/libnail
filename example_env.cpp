/*******************************************************************************************

the program result.

Enter function main
example_env.cpp(33) shows "LANG=en_US.UTF-8"
example_env.cpp(34) shows "SHLVL=1"
example_env.cpp(35) shows "MY_HMOE="
Leave function main


*******************************************************************************************/



#include "nail/nail.h"


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)
	
	SHOW_VALUES("LANG=%s",		nail::env["LANG"].c_str());
	SHOW_VALUES("SHLVL=%d", 	nail::env["SHLVL"].toInt());
	SHOW_VALUES("MY_HMOE=%s",	nail::env["MY_HMOE"].c_str());
	
	return 0;
}
