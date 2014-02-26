#ifndef __NAILJSON__
#define __NAILJSON__


namespace nail{

class ReadJson;

class JsonNode
{
private:
	friend class ReadJson;

	typedef std::map<std::string, JsonNode*>	JSONMap;
	typedef std::pair<std::string, JsonNode*>	JSONPair;
	typedef std::vector<JsonNode*>				JSONArray;

	JsonNode(const JsonNode&);
	JsonNode& operator= (const JsonNode&);

	static const char SYMBOL;

	JSONMap*	m_map;
	JSONArray*	m_array;
	std::string m_content;
	int 		m_type;

public:

	JsonNode()
		:m_map(NULL),m_array(NULL)
	{TRACE_THIS_FUNCTION(ONLY_SHOW)

	
	}


	virtual ~JsonNode()
	{

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
		{
			std::string _rc = "\"" + m_content + "\"";
			return _rc;
		}
		
		
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


	double toDouble()
	{
		if(m_array!=NULL || m_map!=NULL)
		{
			throw NAIL_EXPCEPTION_1("this node is an object");
		}

		return atof(m_content.c_str());
	}


	int toInt()
	{
		if(m_array!=NULL || m_map!=NULL)
		{
			throw NAIL_EXPCEPTION_1("this node is an object");
		}

		return atoi(m_content.c_str());
	}


	template<typename T>
	void operator=(const T& val)
	{
		std::stringstream _ss;
		_ss << val;
		m_content = _ss.str();
	}
};

const char JsonNode::SYMBOL = '"';


class ReadJson
{
private:

public:
	void operator()(const std::string& data, JsonNode& node )
	{TRACE_THIS_FUNCTION(ONLY_SHOW)
		
		//int _type = 0; // 1hash 2array 3value

		int _length = data.size();
		const char* _c = data.c_str();
		std::stack<JsonNode*> _stack;
		//_stack.push(&node);
		
		int _b=0;


		for(int i=0; i<_length; i++)
		{
			//SHOW_VALUES("stack=%d", _stack.size());

			if(_c[i]=='{')
			{
				if(i==0)
					_stack.push(&node);
				else
					_stack.push( new JsonNode() );

				_stack.top()->m_map = new JsonNode::JSONMap();
				_stack.top()->m_type = 1;
				_b=i+1;
				continue;
			}

			
			// 問題在於 key 產生出來之後如果value又是一個hash 會把之前的key蓋掉
			if( _stack.top()->m_type==1 && _c[i]==':' )
			{
				std::string _key( &_c[_b], i-_b);
				JsonNode* _node = new JsonNode();
				_stack.top()->m_map->insert( JsonNode::JSONPair(_key, _node) );

				_stack.push(_node);
				_stack.top()->m_type = 3;

				_b = i+1;
				continue;
			}


			if( _stack.top()->m_type==1 && _c[i]==',' )
			{
				std::string _val( &_c[_b], i-_b);
				
				_stack.top()->m_content = _val;
				_stack.pop();

				_b = i+1;
				continue;
			}


			if(_c[i]=='}')
			{
				std::string _val( &_c[_b], i-_b);
				
				_stack.top()->m_content = _val;
				_stack.pop();

				_stack.pop();

				_b = i+1;
				continue;
			}



			if(_c[i]=='[')
			{
				if(i==0)
					_stack.push(&node);
				else
					_stack.push( new JsonNode() );

				_stack.top()->m_array = new JsonNode::JSONArray();
				_stack.top()->m_type = 2;
				_b=i+1;
				continue;
			}


			if( _stack.top()->m_type==2 && _c[i]==',' )
			{
				std::string _val( &_c[_b], i-_b);
				JsonNode* _node = new JsonNode();
				_stack.top()->m_array->push_back( _node );

				_stack.push(_node);
				_stack.top()->m_type = 3;
				_stack.top()->m_content = _val;
				_stack.pop();

				_b = i+1;
				continue;
			}


			if(_c[i]==']')
			{
				std::string _val( &_c[_b], i-_b);
				JsonNode* _node = new JsonNode();
				_stack.top()->m_array->push_back( _node );

				_stack.push(_node);
				_stack.top()->m_type = 3;
				_stack.top()->m_content = _val;
				_stack.pop();

				_stack.pop();

				_b = i+1;
				continue;
			}

		}

		SHOW_VALUES("stack=%d", _stack.size());
		
	}


};

ReadJson readJson;


}

#endif
