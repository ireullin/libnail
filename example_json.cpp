/*******************************************************************************************

the program result.


*******************************************************************************************/



#include "nail/nail.h"

int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	std::string _json = "{'A':'1', 'B':2, 'C':{'c1':'cone','c2':'ctwo'}}";
	std::string _sub = _json.substr(1, _json.size()-2);
	//SHOW_VALUES("%s", _sub.c_str());

	nail::JsonHash _jh( _sub );


	SHOW_VALUES("%s", _jh.get("B").c_str() );
	SHOW_VALUES("%s", _jh.child("C").get("c1").c_str()  );


	return 0;
}
