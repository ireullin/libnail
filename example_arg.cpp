/*******************************************************************************************

the program result.

execute ./example -ip 192.168.0.1 -port 70 -l pthread --release -ld

Enter function main
example_arg.cpp(40) shows "./example"
example_arg.cpp(40) shows "-ip"
example_arg.cpp(40) shows "192.168.0.1"
example_arg.cpp(40) shows "-port"
example_arg.cpp(40) shows "70"
example_arg.cpp(40) shows "-l"
example_arg.cpp(40) shows "pthread"
example_arg.cpp(40) shows "--release"
example_arg.cpp(40) shows "-ld"
example_arg.cpp(50) shows "doesn't contain the argument"
example_arg.cpp(54) shows "-ip=192.168.0.1"
example_arg.cpp(55) shows "-port=70"
example_arg.cpp(56) shows "-l=pthread"
example_arg.cpp(57) shows "--release="
example_arg.cpp(58) shows "-ld="
Leave function main

*******************************************************************************************/



#include "nail/nail.h"


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)
	nail::arg.set(argc, argv);

	for(int i=0; i<nail::arg.size(); i++)
	{
		SHOW_VALUES("%s", nail::arg[i].c_str());
	}


	if( nail::arg.contain("-k") )
	{
		SHOW_VALUES("contains the argument");	
	}
	else
	{
		SHOW_VALUES("doesn't contain the argument");	
	}


	SHOW_VALUES("-ip=%s", nail::arg["-ip"].c_str());
	SHOW_VALUES("-port=%d", nail::arg["-port"].toInt());
	SHOW_VALUES("-l=%s", nail::arg["-l"].c_str());
	SHOW_VALUES("--release=%s", nail::arg["--release"].c_str());
	SHOW_VALUES("-ld=%s", nail::arg["-ld"].c_str());

	return 0;
}
