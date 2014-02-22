/*********************************************************************************

the program result

Enter function main
example_exception.cpp(13) shows "no=-1 message=message 1"
example_exception.cpp(14) shows "occur in example_exception.cpp line 9"
example_exception.cpp(15) shows "example_exception.cpp(9) msg:(-1)message 1"
example_exception.cpp(27) shows "no=500 message=message 2"
example_exception.cpp(28) shows "occur in example_exception.cpp line 23"
example_exception.cpp(29) shows "example_exception.cpp(23) msg:(500)message 2"
example_exception.cpp(41) shows "example_exception.cpp(36) msg:(-1)message 3"
Leave function main

*********************************************************************************/



#include "nail/nail.h"

int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	try
	{
		// default is -1 if error NO doesn't be assigned.
		throw NAIL_EXPCEPTION_1("message 1");
	}
	catch(nail::Exception& e)
	{
		SHOW_VALUES("no=%d message=%s", e.no(), e.message().c_str() );
		SHOW_VALUES("occur in %s line %d", e.file().c_str(), e.line() );
		SHOW_VALUES("%s", e.what() );
	}



	try
	{
		// you can assign error NO.
		throw NAIL_EXPCEPTION_2(500, "message 2");
	}
	catch(nail::Exception& e)
	{
		SHOW_VALUES("no=%d message=%s", e.no(), e.message().c_str() );
		SHOW_VALUES("occur in %s line %d", e.file().c_str(), e.line() );
		SHOW_VALUES("%s", e.what() );
	}



	try
	{
		throw NAIL_EXPCEPTION_1("message 3");
	}
	catch(std::exception& e)
	{
		// nail::Exception can be catch by std::exception.
		SHOW_VALUES("%s", e.what() );
	}


	return 0;
}
