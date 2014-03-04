/*******************************************************************************************

the program result.

Enter function main
example_typewrapper.cpp(60) shows "var=1"
Leave function main

*******************************************************************************************/



#include "nail/nail.h"

template<typename T>
class Class1
{
private:
	friend class nail::TypeWrapper<T>::type; // if had marked this line, line 38 would occur error in compiling.
	int m_var;

public:
	int getVar()
	{
		return m_var;
	}
};


class Class2
{
private:
	Class1<Class2> m_c1;

public:
	Class2()
	{
		m_c1.m_var = 1;	
	}

	int getVar()
	{
		return m_c1.getVar();
	}
};


int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	Class2 _c2;
	SHOW_VALUES("var=%d", _c2.getVar());

	return 0;
}
