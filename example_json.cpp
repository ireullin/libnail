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


	SHOW_VALUES("%s", _jh["B"].toString().c_str() );
	SHOW_VALUES("%s", _jh["C"]["c1"].toString().c_str()  );
	SHOW_VALUES("%s", _jh["E"][1].toString().c_str()  );

	_jh["B"] = 68.9996;
	_jh["C"] = 23;

	SHOW_VALUES("%s", _jh.toString().c_str()  );

	return 0;
}
