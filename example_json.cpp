/*******************************************************************************************

the program result.


*******************************************************************************************/



#include "nail/nail.h"

int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)



	// SHOW_VALUES("%d", std::string::npos);
	// return 0;


	std::string _json = "{\"A\":\"1\", \"B\":2, \"C\":{\"c1\":\"cone\",\"c2\":\"ctwo\"}, \"D\":\"\", \"E\":[\"z\",\"x\",\"y\"] }";
	nail::JsonNode _jh( _json );


	SHOW_VALUES("%s", _jh.get("B").c_str() );
	SHOW_VALUES("%s", _jh.child("C").get("c1").c_str()  );
	SHOW_VALUES("%s", _jh.child("E").get(1).c_str()  );

	return 0;
}
