/*******************************************************************************************

the program result.

Enter function main
example_dictionary.cpp(14) shows "here are 5 elements now"
example_dictionary.cpp(17) shows "two is 2"
example_dictionary.cpp(27) shows "the dictionary doesn't contain two"
example_dictionary.cpp(34) shows "key is five, value is 5"
example_dictionary.cpp(34) shows "key is four, value is 4"
example_dictionary.cpp(34) shows "key is one, value is 1"
example_dictionary.cpp(34) shows "key is three, value is 3"
example_dictionary.cpp(45) shows "key is five, value is 5"
example_dictionary.cpp(45) shows "key is one, value is 1"
example_dictionary.cpp(45) shows "key is three, value is 3"
example_dictionary.cpp(57) shows "the dictionary doesn't contain four"
example_dictionary.cpp(63) shows "five is 5"
example_dictionary.cpp(73) shows "here are 0 elements now"
Leave function main

*******************************************************************************************/



#include "nail/nail.h"

int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	
	nail::Dictionary<std::string, int> _dict;

	_dict.add("one",	1);
	_dict.add("two",	2);
	_dict.add("three",	3);
	_dict.add("four",	4);
	_dict.add("five",	5);
	SHOW_VALUES("here are %d elements now", _dict.size()  );


	SHOW_VALUES("two is %d", _dict["two"]  );
	_dict.removeByKey("two");


	if( _dict.containKey("two") )
	{
		SHOW_VALUES("the dictionary contains two");
	}
	else
	{
		SHOW_VALUES("the dictionary doesn't contain two");
	}



	for(_dict.begin(); !_dict.end(); ++_dict)
	{
		SHOW_VALUES("key is %s, value is %d", _dict.key().c_str(), _dict.value()  );		
	}

	for(_dict.begin(); !_dict.end(); ++_dict)
	{
		if( _dict.key()=="four" )
			_dict.remove();
	}

	DICTIONARY_FOREACH(_dict) // it and "for(_dict.begin(); !_dict.end(); ++_dict)" are the same.
	{
		SHOW_VALUES("key is %s, value is %d", _dict.key().c_str(), _dict.value()  );		
	}



	int _tmp = -1;
	if(_dict.tryGet("four", _tmp))
	{
		SHOW_VALUES("four is %d", _tmp  );
	}
	else
	{
		SHOW_VALUES("the dictionary doesn't contain four");
	}


	if(_dict.tryGet("five", _tmp))
	{
		SHOW_VALUES("five is %d", _tmp  );
	}
	else
	{
		SHOW_VALUES("the dictionary doesn't contain five");
	}



	_dict.clear();
	SHOW_VALUES("here are %d elements now", _dict.size()  );

	return 0;
}
