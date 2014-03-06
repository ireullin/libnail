/*******************************************************************************************

the program result.

Enter function main
example_filesystem.cpp(28) shows "1,0,1,1560,./example_arg.cpp,.,example_arg.cpp,.cpp"
example_filesystem.cpp(28) shows "0,0,0,-1,./example_arg.cp,.,example_arg.cp,.cp"
example_filesystem.cpp(28) shows "1,1,0,4096,./nail,.,nail,"
example_filesystem.cpp(28) shows "1,1,0,4096,/,,,"
example_filesystem.cpp(44) shows "/,,,"
example_filesystem.cpp(52) shows "/var/www/phplist/admin/,/var/www/phplist/admin,,"
example_filesystem.cpp(68) shows "/var/cache"
example_filesystem.cpp(68) shows "/var/crash"
example_filesystem.cpp(68) shows "/var/local"
example_filesystem.cpp(68) shows "/var/opt"
example_filesystem.cpp(68) shows "/var/www"
example_filesystem.cpp(68) shows "/var/log"
example_filesystem.cpp(68) shows "/var/tmp"
example_filesystem.cpp(68) shows "/var/mail"
example_filesystem.cpp(68) shows "/var/lib"
example_filesystem.cpp(68) shows "/var/backups"
example_filesystem.cpp(68) shows "/var/test"
example_filesystem.cpp(68) shows "/var/develop"
example_filesystem.cpp(68) shows "/var/libnail"
example_filesystem.cpp(68) shows "/var/run"
example_filesystem.cpp(68) shows "/var/spool"
example_filesystem.cpp(68) shows "/var/lock"
example_filesystem.cpp(86) shows "line1"
example_filesystem.cpp(86) shows "line2"
example_filesystem.cpp(86) shows "line3"
example_filesystem.cpp(86) shows "line4"
example_filesystem.cpp(86) shows "finished"
example_filesystem.cpp(89) shows "line1
line2
line3
line4
finished
"
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
		nail::FileSystem _fs( _v[i] );
		SHOW_VALUES(
			"%d,%d,%d,%d,%s,%s,%s,%s",
			_fs.isExisted(),
			_fs.isDirectory(),
			_fs.isFile(),
			_fs.size(),
			_fs.fullname().c_str(),
			_fs.path().c_str(),
			_fs.filename().c_str(),
			_fs.extname().c_str() 
			);
	}
	
	nail::FileSystem _fs1("/");
	nail::FileSystem _fs2 = _fs1.join("var").join("/www").join("phplist/").join("/admin/");

	SHOW_VALUES(
			"%s,%s,%s,%s",
			_fs1.fullname().c_str(),
			_fs1.path().c_str(),
			_fs1.filename().c_str(),
			_fs1.extname().c_str() 
			);

	SHOW_VALUES(
			"%s,%s,%s,%s",
			_fs2.fullname().c_str(),
			_fs2.path().c_str(),
			_fs2.filename().c_str(),
			_fs2.extname().c_str() 
			);


	std::deque<nail::FileSystem> _q;
	nail::FileSystem _fs3("/var");
	_fs3.getFiles( _q );

	std::deque<nail::FileSystem>::iterator _it;
	for(_it=_q.begin(); _it!=_q.end(); ++_it)
	{
		SHOW_VALUES("%s", (*_it).fullname().c_str());
	}


	std::list<std::string> _list;
	_list.push_back("line1");
	_list.push_back("line2");
	_list.push_back("line3");
	_list.push_back("line4");
	
	nail::FileSystem _fs4("./foo.txt");
	_fs4.writeLines(_list, false);
	_fs4.writeAll("\nfinished\n", true);

	std::vector<std::string> _lines;
	_fs4.readLines(_lines);
	for(int i=0; i<_lines.size(); i++)
	{
		SHOW_VALUES("%s", _lines[i].c_str());
	}

	SHOW_VALUES("%s", _fs4.readAll().c_str());

	return 0;
}
