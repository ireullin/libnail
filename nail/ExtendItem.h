#ifndef __NAILEXTENDITEM__
#define __NAILEXTENDITEM__

namespace nail{


class ExtendItem
{
private:
	std::string m_buff;

public:
	ExtendItem()
	{}

	ExtendItem(const ExtendItem& item)
	{m_buff = item.m_buff;}

	ExtendItem(const std::string& item)
	{m_buff = item;}
	
	ExtendItem& operator= (const ExtendItem& item)
	{m_buff = item.m_buff;}

	ExtendItem& operator= (const std::string& item)
	{m_buff = item;}

	ExtendItem& operator= (int x)
	{
		std::stringstream _ss;
		_ss << x;
		m_buff = _ss.str();
	}

	ExtendItem& operator= (double x)
	{
		std::stringstream _ss;
		_ss << x;
		m_buff = _ss.str();
	}

	template <typename X>
	ExtendItem& operator<< (X& x)
	{
		std::stringstream _ss;
		_ss << x;
		m_buff = _ss.str();
	}

	virtual ~ExtendItem()
	{}

	virtual const std::string& toString() const
	{return m_buff;}

	virtual const char* c_str() const
	{return m_buff.c_str();}

	virtual int toInt()
	{return atoi(m_buff.c_str());}

	virtual double toDouble()
	{return atof(m_buff.c_str());}

	virtual long toLong()
	{return atol(m_buff.c_str());}

	nail::ExtendItem padLeft(int length , char symbol)
	{
		std::string _tmp = nail::StringPlus::padLeft(m_buff, length, symbol);
		return ExtendItem(_tmp);
	}

	nail::ExtendItem padRight(int length , char symbol)
	{
		std::string _tmp = nail::StringPlus::padRight(m_buff, length, symbol);
		return ExtendItem(_tmp);
	}

	nail::ExtendItem trimLeft(char symbol=' ')
	{
		std::string _tmp = nail::StringPlus::trimLeft(m_buff, symbol);
		return ExtendItem(_tmp);
	}

	nail::ExtendItem trimRight(char symbol=' ')
	{
		std::string _tmp = nail::StringPlus::trimRight(m_buff, symbol);
		return ExtendItem(_tmp);
	}

	nail::ExtendItem trim(char symbol=' ')
	{
		std::string _tmp = nail::StringPlus::trim(m_buff, symbol);
		return ExtendItem(_tmp);
	}

	nail::ExtendItem toLower(char symbol=' ')
	{
		std::string _tmp = nail::StringPlus::toLower(m_buff);
		return ExtendItem(_tmp);
	}

	nail::ExtendItem toUpper(char symbol=' ')
	{
		std::string _tmp = nail::StringPlus::toUpper(m_buff);
		return ExtendItem(_tmp);
	}

	nail::ExtendItem chomp()
	{
		std::string _tmp = nail::StringPlus::chomp(m_buff);
		return ExtendItem(_tmp);
	}
	
};


}
#endif
