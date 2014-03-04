/*******************************************************************************************

the program result.

Enter function main
example_stringplus.cpp(22) shows "toPrintable:  2013-02-01,14:50:47.321,32,48,65.2298,No Commit  \x0d\x0a"
example_stringplus.cpp(25) shows "string _new is   2013-02-01,14:50:47.321,32,48,65.2298,No Commit  "
example_stringplus.cpp(26) shows "toBinaryString:00100000,00100000,00110010,00110000,00110001,00110011,00101101,00110000,00110010,00101101,00110000,00110001,00101100,00110001,00110100,00111010,00110101,00110000,00111010,00110100,00110111,00101110,00110011,00110010,00110001,00101100,00110011,00110010,00101100,00110100,00111000,00101100,00110110,00110101,00101110,00110010,00110010,00111001,00111000,00101100,01001110,01101111,00100000,01000011,01101111,01101101,01101101,01101001,01110100,00100000,00100000"
example_stringplus.cpp(27) shows "toHexString:\x20\x20\x32\x30\x31\x33\x2d\x30\x32\x2d\x30\x31\x2c\x31\x34\x3a\x35\x30\x3a\x34\x37\x2e\x33\x32\x31\x2c\x33\x32\x2c\x34\x38\x2c\x36\x35\x2e\x32\x32\x39\x38\x2c\x4e\x6f\x20\x43\x6f\x6d\x6d\x69\x74\x20\x20"
example_stringplus.cpp(29) shows "toLower:  2013-02-01,14:50:47.321,32,48,65.2298,no commit  "
example_stringplus.cpp(30) shows "toUpper:  2013-02-01,14:50:47.321,32,48,65.2298,NO COMMIT  "
example_stringplus.cpp(32) shows "trimLeft:2013-02-01,14:50:47.321,32,48,65.2298,No Commit  "
example_stringplus.cpp(33) shows "trimRight:  2013-02-01,14:50:47.321,32,48,65.2298,No Commit"
example_stringplus.cpp(34) shows "trim:2013-02-01,14:50:47.321,32,48,65.2298,No Commit"
example_stringplus.cpp(36) shows "replace:  2013-02-01|14:50:47.321|32|48|65.2298|No Commit  "
example_stringplus.cpp(38) shows "padLeft:=========  2013-02-01,14:50:47.321,32,48,65.2298,No Commit  "
example_stringplus.cpp(39) shows "padRight:  2013-02-01,14:50:47.321,32,48,65.2298,No Commit  ========="
example_stringplus.cpp(45) shows "Split[0]=(string)2013-02-01, (int)2013, (double)2013.000000"
example_stringplus.cpp(45) shows "Split[1]=(string)14:50:47.321, (int)14, (double)14.000000"
example_stringplus.cpp(45) shows "Split[2]=(string)32, (int)32, (double)32.000000"
example_stringplus.cpp(45) shows "Split[3]=(string)48, (int)48, (double)48.000000"
example_stringplus.cpp(45) shows "Split[4]=(string)65.2298, (int)65, (double)65.229800"
example_stringplus.cpp(45) shows "Split[5]=(string)no commit, (int)0, (double)0.000000"
example_stringplus.cpp(59) shows "string _a and string _b are same"
Leave function main

*******************************************************************************************/



#include "nail/nail.h"


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	std::string _old("  2013-02-01,14:50:47.321,32,48,65.2298,No Commit  \r\n");
	SHOW_VALUES("toPrintable:%s", nail::StringPlus::toPrintable(_old.c_str(), _old.size()).c_str() );
	
	std::string _new = nail::StringPlus::chomp(_old);
	SHOW_VALUES("string _new is %s", _new.c_str() );
	SHOW_VALUES("toBinaryString:%s", nail::StringPlus::toBinaryString(_new.c_str(), _new.size()).c_str() );
	SHOW_VALUES("toHexString:%s", nail::StringPlus::toHexString(_new.c_str(), _new.size()).c_str() );
	
	SHOW_VALUES("toLower:%s", nail::StringPlus::toLower(_new).c_str() );
	SHOW_VALUES("toUpper:%s", nail::StringPlus::toUpper(_new).c_str() );

	SHOW_VALUES("trimLeft:%s", nail::StringPlus::trimLeft(_new).c_str() );
	SHOW_VALUES("trimRight:%s", nail::StringPlus::trimRight(_new).c_str() );
	SHOW_VALUES("trim:%s", nail::StringPlus::trim(_new).c_str() );

	SHOW_VALUES("replace:%s", nail::StringPlus::replace(_new,",","|").c_str() );

	SHOW_VALUES("padLeft:%s", nail::StringPlus::padLeft(_new, 60, '=').c_str() );
	SHOW_VALUES("padRight:%s", nail::StringPlus::padRight(_new, 60, '=').c_str() );


	nail::StringPlus::Split _sp(_new,',');
	for(int i=0; i<_sp.size(); i++)
	{
		SHOW_VALUES(
			"Split[%d]=(string)%s, (int)%d, (double)%f",
			i,
			_sp[i].trim().toLower().c_str(),
			_sp[i].toInt(),
			_sp[i].toDouble()
			);
	}


	std::string _a = "abcd";
	std::string _b = "ABCD";
	if(nail::StringPlus::insensitiveCompare(_a, _b))
	{
		SHOW_VALUES("string _a and string _b are same");
	}
	else
	{
		SHOW_VALUES("string _a and string _b are not same");
	}

	return 0;
}
