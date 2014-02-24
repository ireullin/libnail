/*******************************************************************************************

the program result.

Enter function main
Enter function Derive
Leave function Derive
Enter function fun1
Leave function fun1
Leave function main
Enter function ~Derive
Leave function ~Derive

*******************************************************************************************/



#include "nail/nail.h"


class Derive : public nail::Singleton<Derive>
{
private:
	friend class nail::Singleton<Derive>;	// declare that parent class to be friend class
	Derive(const Derive&);
	Derive& operator= (const Derive&);

	// declare all constructors in private
	Derive()
	{TRACE_THIS_FUNCTION(ON)
	}

public:
	~Derive()
	{TRACE_THIS_FUNCTION(ON)
	}

	void fun1()
	{TRACE_THIS_FUNCTION(ON)
	}
};



int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	Derive::instance().fun1();

	/// it will occur error here in compiling.
	//Derive _d;
	//Derive* _pd = new Derive();

	return 0;
}
