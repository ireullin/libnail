/***************************************************************************************************************


Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILFILESYSTEM__
#define __NAILFILESYSTEM__

namespace nail{
namespace FileSystem{


class Info
{
private:
	std::string m_name;
	static const char SPLIT_CHAR;

public:
	Info(const std::string& name)
		:m_name(name)
	{
	}


	bool isExisted()
	{
		struct stat _info;
		return stat(m_name.c_str(), &_info)==0;
	}

	bool isDirectory()
	{
		struct stat _info;
		if(stat(m_name.c_str(), &_info)!=0)
			return false;

		return S_ISDIR(_info.st_mode);
	}

	bool isFile()
	{
		struct stat _info;
		if(stat(m_name.c_str(), &_info)!=0)
			return false;

		return S_ISREG(_info.st_mode);
	}

	int size()
	{
		struct stat _info;
		if(stat(m_name.c_str(), &_info)!=0)
			return -1;

		return _info.st_size;
	}

	const std::string& fullname() const
	{return m_name;}

	std::string extname()
	{
		std::string _filename = filename();
		size_t _pos = _filename.find_last_of(".");
		if(_pos==std::string::npos)	return "";
		else						return _filename.substr(_pos);
	}

	std::string filename()
	{
		size_t _pos = m_name.find_last_of(SPLIT_CHAR);
		if(_pos==std::string::npos)	return m_name;
		else						return m_name.substr(_pos+1);
	}

	std::string path()
	{
		size_t _pos = m_name.find_last_of(SPLIT_CHAR);
		if(_pos==std::string::npos)	return m_name;
		else						return m_name.substr(0, _pos);
	}

	nail::FileSystem::Info join(const std::string& path)
	{
		std::stringstream _newpath;
		
		if(m_name[ m_name.size()-1 ]!=SPLIT_CHAR && path[0]!=SPLIT_CHAR )
			_newpath << m_name << SPLIT_CHAR <<path;

		else if(m_name[ m_name.size()-1 ]==SPLIT_CHAR && path[0]!=SPLIT_CHAR )
			_newpath << m_name << path;

		else if(m_name[ m_name.size()-1 ]!=SPLIT_CHAR && path[0]==SPLIT_CHAR )
			_newpath << m_name << path;

		else
			_newpath << m_name << path.substr(1);

		return nail::FileSystem::Info( _newpath.str() );
	}

	nail::FileSystem::Info join(nail::FileSystem::Info& info)
	{
		join( info.m_name );
	}

	template<typename T>
	void getFiles(T& t)
	{
		DIR* _dir = opendir(m_name.c_str());
		if(_dir==NULL)
			return;

		while(true)
		{
			dirent* _dirent = readdir(_dir);
			if ((_dirent == NULL) || (_dirent->d_name == NULL))
				break;

			if(strcmp(_dirent->d_name,"..")==0 
				|| strcmp(_dirent->d_name,".")==0
				|| strcmp(_dirent->d_name,"/")==0
				)
				continue;

			nail::FileSystem::Info _info = this->join(std::string(_dirent->d_name));
			t.push_back(_info);
		}
	}

};

const char Info::SPLIT_CHAR = '/';

}
}
#endif
