/***************************************************************************************************************
There are lots of functions(or funtors) or clsses which can assist you to handle std::string conveniently.
But some functions(or funtors) are not as efficient as operating std::string directly.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILSTRINGPLUS__
#define __NAILSTRINGPLUS__


namespace nail{
namespace StringPlus{

	/// Remove "\r\n" or "\n" at a string's end.
	std::string chomp(const std::string& value)
	{
		int i = value.size();
		if(value[i-1]!='\n')	return value;
		if(value[i-2]!='\r')	return value.substr(0, i-1);
		return value.substr(0, i-2);
	}

	/// Convert an unprintable character to \xXX if it was involved in a string.
	std::string toPrintable(const char* data, int size, const std::string& prefix="\\x")
	{
		std::stringstream _ss;
		for(int i=0; i<size; i++)
		{
			if(isprint(data[i]))	_ss << data[i];
			else					_ss << prefix << std::setfill('0') << std::setw(2) << std::setiosflags(std::ios::right) << std::hex << static_cast<int>(data[i]); 
		}
		return _ss.str();
	}


	std::string toBinaryString(const char* data, int size, const std::string& split=",")
	{
		std::stringstream _ss;
		for(int i=0; i<size; i++)
		{
			for(int j=7; j>=0; j--)
			{
				if((data[i] & (1 << j)))_ss << "1";
				else					_ss << "0";
			}
			if(i!=size-1) _ss << split;
		}
		return _ss.str();
	}


	std::string toHexString(const char* data, int size, const std::string& prefix="\\x", const std::string& split="")
	{
		std::stringstream _ss;
		for(int i=0; i<size; i++)
		{
			_ss << prefix << std::setfill('0') << std::setw(2) << std::hex << static_cast<unsigned short>(static_cast<unsigned char>(data[i]));
			if(i!=size-1) _ss << split;
		}
		return _ss.str();
	}


	/// Convert the string to lowercase.
	std::string toLower(const std::string& szParam)
	{
		std::string _szParam(szParam);
		std::transform(_szParam.begin(), _szParam.end(), _szParam.begin(), tolower);
		return _szParam;
	}


	/// Convert the string to uppercase.
	std::string toUpper(const std::string& szParam)
	{
		std::string _szParam(szParam);
		std::transform(_szParam.begin(), _szParam.end(), _szParam.begin(), toupper);
		return _szParam;
	}


	/// Remove space chars of left side.
	std::string trimLeft(const std::string& szParam, char symbol=' ')
	{
		if(szParam.size()==0)
			return szParam;

		if(szParam[0]!=symbol)
			return szParam;

		size_t _end = szParam.find_first_not_of(symbol);
		if(_end==std::string::npos)	
			_end=szParam.size();
		
		std::string _szParam(szParam);
		_szParam.erase(_szParam.begin(), _szParam.begin()+_end);
		return _szParam;
	}


	/// Remove space chars of right side.
	std::string trimRight(const std::string& szParam, char symbol=' ')
	{
		if(szParam.size()==0)
			return szParam;

		if(szParam[szParam.size()-1]!=symbol)
			return szParam;

		size_t _str = szParam.find_last_not_of(symbol);
		if(_str==std::string::npos)	
			_str=-1;

		std::string _szParam(szParam);
		_szParam.erase(_szParam.begin()+1+_str, _szParam.end());
		return _szParam;
	}


	/// Remove all space chars.
	std::string trim(const std::string& szParam, char symbol=' ')
	{
		std::string _rc1 = trimLeft(szParam, symbol);
		std::string _rc2 = trimRight(_rc1, symbol);
		return _rc2;
	}


	/// Replace all old strings by the new string in the source string.
	std::string replace(const std::string& szSrc,const std::string& szOld,const std::string& szNew)
	{
		if(szNew.find(szOld)!=std::string::npos)
			throw NAIL_EXPCEPTION_1("unlimited recurrence");

		std::string _szBuff(szSrc);

		int _oldLength	= szOld.size();
		size_t _found	= _szBuff.find(szOld);

		while( _found!=std::string::npos )
		{
			_szBuff.replace(_found, _oldLength, szNew);
			_found = _szBuff.find(szOld);
		}	

		return _szBuff;
	}


	template <typename X> 
	std::string padLeft(X src, int length , char symbol)
	{
		std::stringstream _ss;
		_ss << std::setfill(symbol) << std::setw(length) << std::setiosflags(std::ios::right) << src;
		return _ss.str();
	}


	template <typename X> 
	std::string padRight(X src, int length , char symbol)
	{
		std::stringstream _ss;
		_ss << std::setfill(symbol) << std::setw(length) << std::setiosflags(std::ios::left) << src;
		return _ss.str();
	}


	/// compare without case of words.
	/// it's a funtor, don't implement it.
	class InsensitiveCompare
	{
	private:
		InsensitiveCompare(const InsensitiveCompare& r);
		InsensitiveCompare& operator=(const InsensitiveCompare& r);
		
		static bool	st_implemented;

		static bool compareChar(char a, char b)
		{return tolower(a)==tolower(b);}

	public:
		InsensitiveCompare()
		{
			if(st_implemented)
				throw NAIL_EXPCEPTION_1("class InsensitiveCompare has been implemented");

			st_implemented = true;
		}

		bool operator()(const std::string& a, const std::string& b)
		{
			if(a.size()!=b.size()) return false;
			return std::equal(a.begin(), a.end(), b.begin(), InsensitiveCompare::compareChar);
		}
	};

	bool InsensitiveCompare::st_implemented = false;
	InsensitiveCompare insensitiveCompare;

}
}

#endif
