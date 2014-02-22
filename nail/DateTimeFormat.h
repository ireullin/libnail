/***************************************************************************************************************
Provide for nail::DateTime::toString using.
You can add new pattern if you need it.

Author: Ireul Lin
***************************************************************************************************************/
#ifndef __NAILDATETIMEFORMAT__
#define __MAILDATETIMEFORMAT__

namespace nail{
namespace TimeFormat{


/// 8 yards date format without symbol.
/// Ex. 20110701
struct EightNumDate
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[20];
		memset(&_acBuff[0], 0, sizeof(_acBuff));
		sprintf( _acBuff, "%04d%02d%02d", year, month, day);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct EightNumDate eightNumDate;


/// 6 yards time format without symbol.
/// Ex. 132325
struct SixNumTime
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[20];
		memset(&_acBuff[0], 0, sizeof(_acBuff));
		sprintf( _acBuff, "%02d%02d%02d", hour, minute, second);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct SixNumTime sixNumTime;


/// 6 yards time format without symbol.
/// Ex. 122342021
struct NineNumTime
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[20];
		memset(&_acBuff[0], 0, sizeof(_acBuff));
		sprintf( _acBuff, "%02d%02d%02d%03d", hour, minute, second, millisecond);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct NineNumTime nineNumTime;


/// 13:45:21.254
struct StandardTime
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[25];
		memset(&_acBuff[0], 0, sizeof(_acBuff));
		sprintf( _acBuff, "%02d:%02d:%02d.%03d", hour, minute, second, millisecond);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct StandardTime standardTime;


/// 20070806134521254
struct SeventeenNum
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[25];
		memset(&_acBuff[0], 0, sizeof(_acBuff));
		sprintf( _acBuff, "%04d%02d%02d%02d%02d%02d%03d", year, month, day, hour, minute, second, millisecond);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct SeventeenNum seventeenNum;

}
}

#endif