/***************************************************************************************************************
A simple thread pool, number of threads have to be assigned in creating and can't be modified till destoried.
All of work will be push to a queue to wait handling.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILSIMPLEPOOL__
#define __NAILSIMPLEPOOL__

namespace nail{
namespace Threading{

class SimplePool
{
private:
	SimplePool(const SimplePool&);
	SimplePool& operator=(const SimplePool&);

	std::queue<IRunable*>		m_queue;
	std::vector<ThreadBind*>	m_threads;
	Condition					m_condition;
	Mutex						m_mutex;
	bool						m_continue;

	void* proc(void* sender, void* param)
	{

		while(m_continue)
		{
			if(m_queue.empty())
			{
				m_condition.wait(5);
				continue;
			}


			IRunable* _runable = NULL;
			m_mutex.lock();
			_runable = m_queue.front();			
			m_queue.pop();
			m_mutex.unlock();

			if(_runable==NULL)
				continue;
			
			_runable->run(this);
			SAFE_DELETE(_runable);
		}

		return NULL;
	}

public:
	SimplePool()
		:m_continue(true)
	{
	}


	virtual ~SimplePool()
	{
		if(m_threads.size()!=0)
			throw NAIL_EXPCEPTION_1("the pool has not been released");
	}


	void create(int threadCount)
	{
		if(m_threads.size()!=0)
			throw NAIL_EXPCEPTION_1("the pool has been working");

		m_continue = true;
		for(int i=0; i<threadCount; i++)
		{
			ThreadBind* _pThread = new ThreadBind();
			_pThread->start( new Runable2<SimplePool>(this, &SimplePool::proc) );
			m_threads.push_back(_pThread);
		}
	}


	void destory()
	{
		m_continue = false;
		for(size_t i=0; i<m_threads.size(); i++)
		{
			m_threads[i]->join();
			SAFE_DELETE( m_threads[i] );
		}
		m_threads.clear();
	}


	int threadCount()
	{
		return m_threads.size();
	}


	int workCount()
	{
		return m_queue.size();
	}


	void invoke(IRunable* r)
	{
		m_mutex.lock();
		m_queue.push(r);			
		m_mutex.unlock();
		m_condition.broadcast();
	}


	template<typename T>
	void invokeRange(T& t)
	{
		m_mutex.lock();
		
		for (typename T::iterator it = t.begin(); it!=t.end(); ++it)
			m_queue.push( (*it) );
		
		m_mutex.unlock();
		m_condition.broadcast();
	}

};

} // namespace Threading
} // namespace nail
#endif
