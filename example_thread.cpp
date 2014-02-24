#include "nail/nail.h"


// a class inherit nail::Threading::Thread
class DerivedThread : public nail::Threading::Thread
{
protected:
	virtual void run(void* param)
	{TRACE_THIS_FUNCTION(ON)

		for(int i=0; i<10; i++)
		{
			SHOW_VALUES("This is the DerivedThread");
			nail::Threading::sleep(0.4);
		}
	}
};


// a global method
void* fun1(void* sender, void* param)
{TRACE_THIS_FUNCTION(ON)
	
	for(int i=0; i<10; i++)
	{
		SHOW_VALUES("This is the fun1");
		nail::Threading::sleep(0.5);
	}

	return NULL;
}



class Foo
{
public:
	// a static method
	static void* fun2(void* sender, void* param)
	{TRACE_THIS_FUNCTION(ON)
	
		for(int i=0; i<10; i++)
		{
			SHOW_VALUES("This is the Foo::fun2");
			nail::Threading::sleep(0.6);
		}

		return NULL;
	}


	// a memeber method
	void* fun3(void* sender, void* param)
	{TRACE_THIS_FUNCTION(ON)
	
		for(int i=0; i<10; i++)
		{
			SHOW_VALUES("This is the Foo::fun3");
			nail::Threading::sleep(0.7);
		}

		return NULL;
	}
};



// a funtor(function object)
struct Funtor
{
	void* operator()(void* sender, void* param)
	{TRACE_THIS_FUNCTION(ON)
	
		for(int i=0; i<10; i++)
		{
			SHOW_VALUES("This is the funtor");
			nail::Threading::sleep(0.8);
		}

		return NULL;
	}
};
Funtor funtor;



int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)


	Foo _foo;	
	std::vector<nail::Threading::Thread*> _v;

	// a class inherit nail::Threading::Thread
	DerivedThread* _derivedThread = new DerivedThread();
	_derivedThread->start();
	_v.push_back( _derivedThread );


	// bind a global function
	nail::Threading::ThreadBind* _bind1 = new nail::Threading::ThreadBind();
	_bind1->start( new nail::Runable1(&fun1) );
	_v.push_back( _bind1 );


	// bind a static function
	nail::Threading::ThreadBind* _bind2 = new nail::Threading::ThreadBind();
	_bind2->start( new nail::Runable1(&Foo::fun2) );
	_v.push_back( _bind2 );


	// bind a member function
	nail::Threading::ThreadBind* _bind3 = new nail::Threading::ThreadBind();
	_bind3->start( new nail::Runable2<Foo>(&_foo,&Foo::fun3) );
	_v.push_back( _bind3 );


	// bind a funtor
	nail::Threading::ThreadBind* _bind4 = new nail::Threading::ThreadBind();
	_bind4->start( new nail::Runable3<Funtor>(&funtor) );
	_v.push_back( _bind4 );


	for(int i=0; i<_v.size(); i++)
	{
		_v[i]->join();
		SAFE_DELETE( _v[i] );
	}
	

	///
	/// an example for thread pool
	///
	nail::Threading::SimplePool _threadpool;
	_threadpool.create(2); // assign number of thread which you would like to start up.
	SHOW_VALUES( "this pool contains %d threads", _threadpool.threadCount() );

	// you can pass any sequential container to invokeRange.
	std::deque<nail::IRunable*> _runables;
	//std::vector<nail::IRunable*> _runables;
	//std::list<nail::IRunable*> _runables;
	_runables.push_back( new nail::Runable1(&fun1) );
	_runables.push_back( new nail::Runable1(&Foo::fun2) );
	_runables.push_back( new nail::Runable2<Foo>(&_foo,&Foo::fun3) );
	_threadpool.invokeRange( _runables );


	// or just invoke one
	_threadpool.invoke( new nail::Runable3<Funtor>(&funtor) );


	while( _threadpool.workCount()!=0 )
	{
		nail::Threading::sleep(0.5);
	}

	_threadpool.destory();

	return 0;
}
