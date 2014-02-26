#ifndef __NAILJSON__
#define __NAILJSON__


namespace nail{

class JsonNode
{
private:
	typedef std::map<std::string, JsonNode*>	JSONMap;
	typedef std::pair<std::string, JsonNode*>	JSONPair;
	typedef std::vector<JsonNode*>				JSONArray;

	JsonNode(const JsonNode&);
	JsonNode& operator= (const JsonNode&);

	static const char SYMBOL;

	JSONMap*	m_map;
	JSONArray*	m_array;
	std::string m_content;
	

	std::string find(const std::string& data, size_t& offset, const char endSign)
	{TRACE_THIS_FUNCTION(ONLY_SHOW)

		std::stack<char> _stack;
		
		size_t _length = std::string::npos;
		size_t _total = data.size()-offset;

		for(size_t i=0; i<_total; i++ )
		{
			char _c = data[offset+i];

			if( _c=='{' || _c=='[' )
				_stack.push( _c );

			if( _c=='}' || _c==']' )
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

		size_t _b = _rc.find_first_not_of(std::string(" "));
		size_t _e = _rc.find_last_not_of(std::string(" "));

		if(_b!=std::string::npos && _e!=std::string::npos)
			return _rc.substr(_b, _e-_b+1);

		if(_b==std::string::npos && _e!=std::string::npos)
			return _rc.substr(0, _e+1);

		if(_b!=std::string::npos && _e==std::string::npos)
			return _rc.substr(_b);

		throw NAIL_EXPCEPTION_1("JSON format error");
		return "";
	}


	void hashType(const std::string& content)
	{TRACE_THIS_FUNCTION(ONLY_SHOW)

		m_map = new JSONMap();

		size_t _offset = -1;
		do
		{
			_offset++;
			std::string _key = find(content, _offset, ':');
			if( _key[0]!=JsonNode::SYMBOL || _key[ _key.size()-1 ]!=JsonNode::SYMBOL )
			{
				throw NAIL_EXPCEPTION_1("JSON format error");
			}

			_offset++;
			std::string _val = find(content, _offset, ',');
			
			m_map->insert(
				JSONPair(
					_key.substr(1,_key.size()-2),
					 new JsonNode( _val )
					 )
				);

		}while(_offset!=std::string::npos);
	}


	void arrayType(const std::string& content)
	{TRACE_THIS_FUNCTION(ONLY_SHOW)

		m_array = new JSONArray();

		size_t _offset = -1;
		do
		{
			_offset++;
			std::string _val = find(content, _offset, ',');
			m_array->push_back( new JsonNode( _val ) );

		}while(_offset!=std::string::npos);
	}


public:

	JsonNode(const std::string& content)
		:m_map(NULL),m_array(NULL)
	{TRACE_THIS_FUNCTION(ONLY_SHOW)

		// to do:
		// check the rule
		if(content[0]=='{' && content[content.size()-1]=='}')
			hashType( content.substr(1, content.size()-2) );
		else if(content[0]=='[' && content[content.size()-1]==']')
			arrayType( content.substr(1, content.size()-2) );
		else
			m_content = content;
	}


	virtual ~JsonNode()
	{TRACE_THIS_FUNCTION(ON)

		if(m_map!=NULL)
		{
			for(JSONMap::iterator it=m_map->begin(); it!=m_map->end(); ++it)
			{
				JsonNode* _node = it->second;
    			delete _node;
    		}

    		delete m_map;
		}

		if(m_array!=NULL)
		{
			for(JSONArray::iterator it=m_array->begin(); it!=m_array->end(); ++it)
			{
    			JsonNode* _node = (*it);
    			delete _node;
    		}

    		delete m_array;
		}
	}


	JsonNode& operator[](const std::string& key)
	{
		return (*(*m_map)[key]);
	}


	JsonNode& operator[](int key)
	{
		return (*(*m_array)[key]);
	}


	std::string toString()
	{
		if( !m_content.empty() )
			return m_content;
		
		
		if(m_map!=NULL)
		{
			std::stringstream _ss;
			_ss << "{";
			for(JSONMap::iterator it=m_map->begin(); it!=m_map->end(); ++it)
			{
				JsonNode* _node = it->second;
    			_ss << '"' << it->first << "\":" << _node->toString() << ",";
    		}

    		std::string _rc = _ss.str();
    		_rc[ _rc.size()-1 ] = '}';
    		return _rc;
		}


		if(m_array!=NULL)
		{
			std::stringstream _ss;
			_ss << "[";
			for(JSONArray::iterator it=m_array->begin(); it!=m_array->end(); ++it)
			{
				JsonNode* _node = (*it);
    			_ss << _node->toString() << ",";
    		}

    		std::string _rc = _ss.str();
    		_rc[ _rc.size()-1 ] = ']';
    		return _rc;
		}

		return "";
	}
};

const char JsonNode::SYMBOL = '"';

}

#endif
