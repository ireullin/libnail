/***************************************************************************************************************
Assist handling signals in unix-like OS.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILSIGNAL__
#define __NAILSIGNAL__


namespace nail{
	
class Signal
{
private:
	std::vector<int>	m_arrSignal;
	static IRunable*	st_pRunable;		
	static bool			st_implemented;

	static void event(int signalNo)
	{

		if(st_pRunable==NULL)
		{
			signal(signalNo, Signal::event);
			return;
		}

		void* _tmp = reinterpret_cast<void*>(signalNo);
		bool _rc = (bool)st_pRunable->run(_tmp);

		if(_rc)
			signal(signalNo, Signal::event);
		else
			signal(signalNo, NULL);
	}


	void block()
	{
		// add signals here that you wanna catch
		m_arrSignal.push_back(SIGINT);
		m_arrSignal.push_back(SIGQUIT);
		m_arrSignal.push_back(SIGKILL);
		m_arrSignal.push_back(SIGILL);
		m_arrSignal.push_back(SIGCHLD);
		m_arrSignal.push_back(SIGTERM);

		for(size_t i=0; i<m_arrSignal.size(); i++)
			signal(m_arrSignal[i], Signal::event);
	}


	void unblock()
	{
		for(size_t i=0; i<m_arrSignal.size(); i++)
			signal(m_arrSignal[i], NULL);

		SAFE_DELETE(st_pRunable);
	}


public:
	Signal()
	{
		if(st_implemented)
			throw NAIL_EXPCEPTION_1("class Signal has been implemented");

		st_implemented = true;
	}
	
	~Signal()
	{
		unblock();
	}


	/// DON'T DELETE THE IRunable, it will be deleted in this class
	void operator()(IRunable* p)
	{
		SAFE_DELETE(st_pRunable);

		if(p==NULL)
		{
			unblock();
		}
		else
		{
			st_pRunable = p;
			block();
		}
	}

};


IRunable*	Signal::st_pRunable = NULL;
bool 		Signal::st_implemented = false;
Signal 		signal;

}

#endif
