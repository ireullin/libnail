#ifndef __NAILSPLIT__
#define __NAILSPLIT__

namespace nail{
namespace StringPlus{

/// Split a string with a char.
class Split
{
private:
	Split(const Split& r);
	Split& operator=(const Split& r);

	std::vector<nail::ExtendItem> m_vec;

public:
	Split(const std::string& str, char symbol)
	{
		const char* _buff = str.c_str();
		int _offset=0;
		for(size_t i=0; i<str.size(); i++)
		{
			if(_buff[i]!=symbol)
				continue;

			nail::ExtendItem _item(std::string(&_buff[_offset],  i-_offset));
			m_vec.push_back(_item);
			_offset = i+1;
		}

		nail::ExtendItem _item(std::string(&_buff[_offset]));
		m_vec.push_back(_item);
	}

	size_t size()
	{return m_vec.size();}

	nail::ExtendItem& operator[](int i)
	{return m_vec[i];}
};

}
}
#endif
