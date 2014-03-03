/***************************************************************************************************************
1. A header file include other header files in common use form STL, ubuntu system, nail library and so on....
2. Dedfined some marcos for nail library.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAIL__
#define __NAIL__


#define NAIL_EXPCEPTION_1(param)		nail::Exception(param, __FILE__, __LINE__);
#define NAIL_EXPCEPTION_2(no, msg)		nail::Exception(no, msg, __FILE__, __LINE__);


#ifndef AUTO_LOCK
	#define AUTO_LOCK(a)				nail::Threading::AutoLock _autolock(a)
#endif


#ifndef DICTIONARY_FOREACH
	#define DICTIONARY_FOREACH(a)		for(a.begin(); !a.end(); ++a)
#endif


#ifndef SAFE_DELETE
	#define SAFE_DELETE(a)				if( (a) != NULL ) {delete (a); (a) = NULL;}
#endif

#ifndef SAFE_DELETE_ARRAY
	#define SAFE_DELETE_ARRAY(a)		if( (a) != NULL ) {delete[] (a); (a) = NULL;}
#endif


#ifndef ON
	#define ON 1
#endif

#ifndef OFF
	#define OFF 2
#endif

#ifndef ONLY_SHOW
	#define ONLY_SHOW 3
#endif

	
#ifdef NAIL_TRACE_ENABLE
	#define TRACE_THIS_FUNCTION(x)	nail::Trace _nailtrace_(x, __FILE__,__FUNCTION__);
	#define SHOW_POSITION			_nailtrace_.position(__LINE__)
	#define SHOW_VALUES				_nailtrace_.line(__LINE__); _nailtrace_.show
	#define SHOW_ERRORS				_nailtrace_.line(__LINE__); _nailtrace_.error
#else
	#define TRACE_THIS_FUNCTION(x)	/* NAIL_TRACE_DISABLE */
	#define SHOW_POSITION			/* NAIL_TRACE_DISABLE */
	#define SHOW_VALUES				//
	#define SHOW_ERRORS				//
#endif


#ifndef NANO
#define NANO 1000000000LL
#endif


// STL pure c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <stddef.h>
#include <ctype.h>

// STL C++
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <exception>
#include <queue>
#include <memory>
#include <tr1/memory>
#include <list>
#include <iomanip>

// developing os are unbuntu 12.04
#include <unistd.h>
#include <signal.h>
#include <sys/shm.h>
#include <libgen.h> 
#include <sys/timeb.h>
#include <pthread.h>
#include <errno.h>

// nail
#include "Exception.h"
#include "Trace.h"
#include "ExtendItem.h"
#include "Runable.h"
#include "Signal.h"
#include "Thread.h"
#include "ThreadBind.h"
#include "Mutex.h"
#include "Condition.h"
#include "Dictionary.h"
#include "Singleton.h"
#include "SimplePool.h"
#include "DateTimeFormat.h"
#include "DateTime.h"
#include "Common.h"
#include "StringPlus.h"



#endif
