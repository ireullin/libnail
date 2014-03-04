#ifndef __NAILENV__
#define __NAILENV__

namespace nail{

class Env
{
private:
	Env(const Env&);
	Env& operator= (const Env&);

	static bool st_implemented;

public:
	Env()
	{
		if(st_implemented)
			throw NAIL_EXPCEPTION_1("class Env has been implemented");

		st_implemented = true;
	}

	// return empty string if the key doesn't exist.
	nail::ExtendItem operator[](const std::string& key)
	{
		const char* _env = getenv(key.c_str());
		if(_env==NULL)
			return nail::ExtendItem("");
		
		std::string _szEnv(_env);
		nail::ExtendItem _item(_szEnv);
		return _item;
	}

};

Env env;
bool Env::st_implemented = false;

}
#endif
