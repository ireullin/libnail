/****************************************************************************

the program result

Enter function main
Enter function function1
example_trace.cpp(7) is current position
example_trace.cpp(8) shows "this is function1"
Leave function function1
example_trace.cpp(15) is current position
example_trace.cpp(16) shows "this is function2"
example_trace.cpp(35) error "here will assert"
example: nail/Trace.h:119: void nail::Trace::error(const char*, ...): Assertion `false' failed.

******************************************************************************/



#include "nail/nail.h"

// here will show function stack and which you would like to show.
void function1()
{TRACE_THIS_FUNCTION(ON)
	SHOW_POSITION;
	SHOW_VALUES("this is %s", "function1");
}


// here will only show which you would like to.
void function2()
{TRACE_THIS_FUNCTION(ONLY_SHOW)
	SHOW_POSITION;
	SHOW_VALUES("this is %s", "function2");
}


// here will show nothing.
void function3()
{TRACE_THIS_FUNCTION(OFF)
	SHOW_POSITION;
	SHOW_VALUES("this is %s", "function3");
}


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	function1();
	function2();
	function3();


	SHOW_ERRORS("here will assert");
	return 0;
}
