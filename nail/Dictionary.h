/***************************************************************************************************************
Re-wrap the std::map to suppose you using easier.
But you should use it carefully in muti-thread.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILDICTIONARY__
#define __MAILDICTIONARY__

namespace nail{
/**************************************************************************************************
	Example:
	Dictionary2<std::string,std::string> dic;
	for(dic.begin(); !dic.end(); ++dic)
	{
		printf("key=%s value=%s", dic.key().c_str(), dic.value().c_str());	
		dic.Remove();
	}

	or

	Dictionary2<std::string,std::string> dic;
	DICTIONARY_FOREACH(dic)
	{
		printf("key=%s value=%s", dic.key().c_str(), dic.value().c_str());	
		dic.Remove();
	}

***************************************************************************************************/

template <typename K, typename V>
class Dictionary{
private:
	typedef std::map<K,V>	MapType;
	typedef std::pair<K,V>	PairType;

	Dictionary(const Dictionary&);
	Dictionary& operator=(const Dictionary&);

	MapType						m_map;
	typename MapType::iterator	m_it;
	bool						m_reset;

public:
	Dictionary()
		:m_reset(false)
	{}


	virtual ~Dictionary()
	{}


	/// add a new element.
	/// it will over overwrite old element.
	void add(const K& key, const V& val)
	{m_map.insert(PairType(key, val));}

	
	/// remove the element
	/// it would throw an exception if the element hadn't existed.
	void removeByKey(const K& key)
	{m_map.erase(key);}


	/// whether contain the key
	bool containKey(const K& key)
	{return m_map.find(key)!=m_map.end();}


	/// get the value by key
	/// it would throw an exception if the element hadn't existed.
	V& operator[](const K& key)
	{return m_map[key];}
	

	/// val would be the value if returned true.
	bool tryGet(const K& key, V& val)
	{
		if(!containKey(key))
			return false;

		val = m_map[key];
		return true;
	}


	/// how many elements in this dictionary.
	size_t size()
	{return m_map.size();}


	/// clear all elements.
	void clear()
	{m_map.clear();}


	V& value()
	{return (*m_it).second;}


	const K& key()
	{return (*m_it).first;}


	void begin()
	{
		m_reset = false;
		m_it = m_map.begin();
	}


	bool end()
	{return m_it == m_map.end();}


	void remove()
	{
		typename MapType::iterator _tmp;
		_tmp = m_it;
		
		if(m_it==m_map.begin())
			m_reset = true;
		else
			--m_it;
		
		m_map.erase(_tmp);

		if(m_reset)
			m_it = m_map.begin();
	}


	Dictionary<K,V> & operator++()
	{
		if(m_reset) m_reset=false;
		else		++m_it;
		return (*this);
	}


	const Dictionary<K,V> operator++(int i)
	{
		if(m_reset) m_reset=false;
		else		++m_it;

		++m_it;
		Dictionary<K,V> _tmp;
		return _tmp;
	}


};
}

#endif
