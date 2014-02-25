#ifndef __NAILJSON__
#define __NAILJSON__


namespace nail{

class JsonNode
{
protected:
	std::string find(const std::string& data, size_t& offset, const char endSign)
	{
		std::stack<char> _stack;
		
		size_t _length = std::string::npos;
		size_t _total = data.size()-offset;

		for(size_t i=0; i<_total; i++ )
		{
			char _c = data[offset+i];

			if( _c=='{' || _c=='[')
				_stack.push( _c );

			if( _c=='}' || _c==']')
			{
				if( _c != _stack.top()+2 )
				{
					throw NAIL_EXPCEPTION_1("JSON format error");
				}
				
				_stack.pop();
			}


			if(_stack.empty())
			{
				if( _c==endSign )
				{
					_length = i;
					break;
				}
			}
		}

		std::string _rc = data.substr(offset, _length);
		
		if(_length != std::string::npos)
			offset += _length;
		else
			offset = std::string::npos;

		size_t _b = _rc.find_first_not_of("' ");
		size_t _e = _rc.find_last_not_of("' ");

		if(_b!=std::string::npos && _e!=std::string::npos)
			return _rc.substr(_b, _e-_b+1);

		if(_b==std::string::npos && _e!=std::string::npos)
			return _rc.substr(0, _e+1);

		if(_b!=std::string::npos && _e==std::string::npos)
			return _rc.substr(_b);

		return _rc;
	}

public:
	JsonNode()
	{}
	
	virtual ~JsonNode(){}

	template< typename T >
	virtual JsonNode& child(const T& key)=0;

	template< typename T >
	virtual std::string get(const T& key)=0;
};


class JsonHash : public JsonNode
{
private:
	typedef nail::JsonNode	super;
	typedef std::map<std::string, std::string>	JSONMap;
	typedef std::pair<std::string, std::string>	JSONPair;

	JsonHash(const JsonHash&);
	JsonHash& operator= (const JsonHash&);

	JSONMap		m_map;
	JsonNode*	m_child;

public:

	JsonHash(const std::string& content)
		:m_child(NULL)
	{TRACE_THIS_FUNCTION(ONLY_SHOW)

		size_t _offset = -1;
		do
		{
			_offset++;
			std::string _key = super::find(content, _offset, ':');

			_offset++;
			std::string _val = super::find(content, _offset, ',');
			
			//SHOW_VALUES("ley=%s val=%s", _key.c_str(), _val.c_str());
			m_map.insert(JSONPair(_key, _val));

		}while(_offset!=std::string::npos);
	}


	virtual ~JsonHash()
	{
		SAFE_DELETE(m_child);
	}

	template< typename T >
	virtual JsonNode& child(const T& key)
	{
		SAFE_DELETE(m_child);

		std::string _content = m_map[key];

		if(_content[0]=='{' && _content[ _content.size()-1 ]=='}'  )
			m_child = new JsonHash( _content.substr(1, _content.size()-2) );
		else if(_content[0]=='[' && _content[ _content.size()-1 ]==']'  )
			m_child = new JsonHash( _content.substr(1, _content.size()-2) );// array
		else
		{
			throw NAIL_EXPCEPTION_1("JSON format error");
		}

		return (*m_child);
	}

	template< typename T >
	std::string get(const T& key)
	{
		return m_map[key];
	}


};


}

#endif
