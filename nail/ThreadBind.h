/***************************************************************************************************************
A thread class, which derived form nail::Threading::Thread, 
allows you running several threads in a class or running a thread without inheritance.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILTHREADBIND__
#define __NAILTHREADBIND__

namespace nail{
namespace Threading{

class ThreadBind : public Thread
{
private:
	typedef Thread super;
	ThreadBind(const ThreadBind&);
	ThreadBind& operator= (const ThreadBind&);

	nail::IRunable* m_pRunable;


protected:
	virtual void run(void* param=NULL)
	{
		if(m_pRunable==NULL)
		{
			throw NAIL_EXPCEPTION_1("Runable can't be empty.");
		}


		m_pRunable->run(this);
	}

public:
	ThreadBind()
		:m_pRunable(NULL)
	{}


	virtual ~ThreadBind()
	{
		SAFE_DELETE(m_pRunable);
	}


	virtual void start(void* param=NULL)
	{
		throw NAIL_EXPCEPTION_1("This method has been denied, please call another method void start(nail::IRunable* pRunable)");
	}


	void start(nail::IRunable* pRunable)
	{
		SAFE_DELETE(m_pRunable);
		m_pRunable = pRunable;
		super::start(NULL);
	}
};

}
}


#endif
