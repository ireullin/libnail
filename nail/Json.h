#ifndef __NAILJSON__
#define __NAILJSON__


namespace nail{

class ReadJson;

class JsonNode
{
private:
	friend class ReadJson;

	typedef std::vector<JsonNode*>				JSONArray;

	JsonNode(const JsonNode&);
	JsonNode& operator= (const JsonNode&);

	static const char SYMBOL;

	std::deque<JsonNode*> 	m_array; // just for type 1 or 2
	std::string 			m_key;
	std::string 			m_val;
	int 					m_type;

public:

	JsonNode()
	{TRACE_THIS_FUNCTION(ONLY_SHOW)

	
	}


	virtual ~JsonNode()
	{

	
	}

	std::string toString()
	{
		//if(m_type==3)
		//	return m_val;

		if(m_type==1)
		{
			std::stringstream _ss;
			_ss << "{";
			for(int i=0; i<m_array.size(); i++)
			{
				_ss << m_array[i]->m_key << ":" << m_array[i]->m_val << ",";
			}

			std::string _rc = _ss.str();
			_rc[_rc.size()-1] = '}';
			return _rc;
		}

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

		std::string _key;
		int _b=0;


		for(int i=0; i<_length; i++)
		{
			//SHOW_VALUES("stack=%d", _stack.size());

			// type 定義有問題
			// toString 寫法有問題
			// 目前寫法缺點是不會stack
			if(_c[i]=='{')
			{
				if(i==0)
					_stack.push(&node);
				else
					_stack.push(new JsonNode());

				_stack.top()->m_type = 1;
				_b=i+1;
				continue;
			}

			
			if( _stack.top()->m_type==1 && _c[i]==':' )
			{
				_key = std::string( &_c[_b], i-_b);
				_b = i+1;
				continue;
			}


			if( _stack.top()->m_type==1 && _c[i]==',' )
			{

				JsonNode* _node = new JsonNode()
				_node->m_type = 3;
				_node->m_key = _key;
				_node->m_val = std::string( &_c[_b], i-_b);
				_stack.top()->m_array.push_back(_node);

				_b = i+1;
				continue;
			}


			if(_c[i]=='}')
			{
				JsonNode* _node = new JsonNode()
				_node->m_type = 3;
				_node->m_key = _key;
				_node->m_val = std::string( &_c[_b], i-_b);
				_stack.top()->m_array.push_back(_node);

				_stack.pop();

				_b = i+1;
				continue;
			}


			/*
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
			}*/

		}

		SHOW_VALUES("stack=%d", _stack.size());
		
	}


};

ReadJson readJson;


}

#endif
