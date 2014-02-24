/*******************************************************************************************

the program result.

Enter function main
Enter function event
example_signal.cpp(9) shows "received signal 2" //when you press ctrl-c
Leave function event
Leave function main

*******************************************************************************************/



#include "nail/nail.h"

bool g_running = true;


void* event(void* sender, void* param)
{TRACE_THIS_FUNCTION(ON)

	int* _signal = reinterpret_cast<int*>(sender);
	SHOW_VALUES("received signal %d", _signal);

	g_running = false;

	// register the signal again, if returned true.
	return (void*)true;
}


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	// register a method to catch signal
	// if you would like to catch other signal, please modify nail::Signal::block directly.
	//
	// other of nail::Runable1 please refer example_thread.cpp
	//
	nail::signal(new nail::Runable1(&event));


	while(g_running)
	{
		nail::Threading::sleep(0.1);
	}
	

	// remove registered event.
	nail::signal(NULL);

	return 0;
}
