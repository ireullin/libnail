#ifndef __NAILARG__
#define __NAILARG__

namespace nail{

class Arg
{
private:
	Arg(const Arg&);
	Arg& operator= (const Arg&);

	static bool st_implemented;
	std::vector<std::string> m_vec;
	bool m_hasSet;

	int find(const std::string& key)
	{
		for(int i=1; i<m_vec.size(); i++)
		{
			if(m_vec[i]==key)
				return i;
		}
		return -1;
	}

public:
	Arg():m_hasSet(false)
	{
		if(st_implemented)
			throw NAIL_EXPCEPTION_1("class Arg has been implemented");

		st_implemented = true;
	}

	void set(int argc, char** argv)
	{
		if(m_hasSet)
			throw NAIL_EXPCEPTION_1("Arguments have set");

		for(int i=0; i<argc; i++)
			m_vec.push_back(std::string(argv[i]));

		m_hasSet = true;
	}

	int size()
	{return m_vec.size();}


	bool contain(const std::string& key)
	{return find(key)!=-1;}


	nail::ExtendItem operator[](int i)
	{
		nail::ExtendItem _item(m_vec[i]);
		return _item;
	}


	nail::ExtendItem operator[](const std::string& key)
	{
		if(key[0]!='-')
			throw NAIL_EXPCEPTION_1("it's not a key");

		int i = find(key);
		if(i==-1)
			throw NAIL_EXPCEPTION_1("doesn't contain the key");

		if(i==m_vec.size()-1)
			return nail::ExtendItem("");

		std::string _next = m_vec[i+1];
		if(_next[0]=='-')
			return nail::ExtendItem("");
		
		nail::ExtendItem _item(_next);
		return _item;
	}

};

Arg arg;
bool Arg::st_implemented = false;

}
#endif
