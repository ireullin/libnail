/***************************************************************************************************************
This class provides a singleton pattern for derived class.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILSINGLETON__
#define __NAILXSINGLETON__

namespace nail{

/****************************************************************
	Example:
	class Derive : public nail::Singleton<Derive>
	{
	private:
		friend class nail::Singleton<Derive>;	// declare that parent class to be friend class
		Derive(){}								// declare all constructors in private
		Derive(const Derive&);
		Derive& operator= (const Derive&);
		etc....
*******************************************************************/

template<typename T>
class Singleton
{
private:
	static Threading::Mutex	st_mutex;
	static std::auto_ptr<T> st_ptr;
	Singleton(const Singleton&);
	Singleton& operator= (const Singleton&);

protected:
	Singleton(){}

public:
	static T& Instance()
	{
		st_mutex.lock();
		if(st_ptr.get()==NULL)st_ptr.reset(new T);
		st_mutex.unlock();
		return (*st_ptr.get());
	}
};

template<typename T>Threading::Mutex Singleton<T>::st_mutex;
template<typename T>std::auto_ptr<T> Singleton<T>::st_ptr;

}

#endif
