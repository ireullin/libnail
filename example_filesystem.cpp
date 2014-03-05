/*******************************************************************************************

the program result.

Enter function main
example_typewrapper.cpp(60) shows "var=1"
Leave function main

*******************************************************************************************/



#include "nail/nail.h"


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	std::vector<std::string> _v;
	_v.push_back("./example_arg.cpp");
	_v.push_back("./example_arg.cp");
	_v.push_back("./nail");
	_v.push_back("/");

	for(int i=0; i<_v.size(); i++)
	{
		nail::FileSystem::Info _info( _v[i] );
		SHOW_VALUES(
			"%d,%d,%d,%d,%s,%s,%s,%s",
			_info.isExisted(),
			_info.isDirectory(),
			_info.isFile(),
			_info.size(),
			_info.fullname().c_str(),
			_info.path().c_str(),
			_info.filename().c_str(),
			_info.extname().c_str() 
			);
	}
	
	nail::FileSystem::Info _info1("/");
	nail::FileSystem::Info _info2 = _info1.join("var").join("/www").join("phplist/").join("/admin/");

	SHOW_VALUES(
			"%s,%s,%s,%s",
			_info1.fullname().c_str(),
			_info1.path().c_str(),
			_info1.filename().c_str(),
			_info1.extname().c_str() 
			);

	SHOW_VALUES(
			"%s,%s,%s,%s",
			_info2.fullname().c_str(),
			_info2.path().c_str(),
			_info2.filename().c_str(),
			_info2.extname().c_str() 
			);


	std::deque<nail::FileSystem::Info> _q;
	nail::FileSystem::Info _info3("/var");
	_info3.getFiles( _q );

	std::deque<nail::FileSystem::Info>::iterator _it;
	for(_it=_q.begin(); _it!=_q.end(); ++_it)
	{
		SHOW_VALUES("%s", (*_it).fullname().c_str());
	}

	return 0;
}
