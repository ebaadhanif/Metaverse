#pragma once
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <time.h>
#include <string>
#include <tuple>
#include <DIS7\msLibMacro.h>

namespace DIS
{
#define DIS_UNIT_TIME		1.676380635	//Micro Seconds
#define FIRST_QUARTER		15
#define LAST_QUARTER		45
#define SEC_IN_MINS			60
#define QUARTER_MAX_VAL		3600

#define SECONDS_IN_HOUR		3600
#define MILLIS_IN_SEC		(double)1000.0
#define MICROS_IN_SEC		(double)1000000.0

	enum COMPARISON_RESULT
	{
		EQUALS = 0,
		LESS_THAN = 1,
		GREATER_THAN = 2,
	};

	struct _DISTimeStruct
	{
		int seconds;	     /* seconds since 12:00AM, 1 January, 1970 */
		int milliSeconds;    /* milliseconds added to the seconds */
		int microSeconds;    /* microseconds added to the seconds */
		int secondsTopOfTheHour; /* seconds from 12:00AM, 1 January, 1970 to the current top of the hour*/
	};

	struct _Time
	{
		int seconds;
		int milliSeconds;
		int microSeconds;
		_Time()
		{
			seconds = 0;
			milliSeconds = 0;
			microSeconds = 0;
		}
		_Time(int sec, int milli, int micro)
		{
			seconds = sec;
			milliSeconds = milli;
			microSeconds = micro;

		}
		COMPARISON_RESULT CompareWithZero()
		{
			double secondsInDouble = double(seconds) + double(microSeconds / 1000000.0);

			if (secondsInDouble < 0.0)
			{
				return LESS_THAN;
			}
			else if (secondsInDouble > 0.0)
			{
				return GREATER_THAN;
			}
			else // if (secondsInDouble == 0.0)
			{
				return EQUALS;
			}
		}
	};

	struct mytimeb
	{
		time_t time;
		unsigned short millitm;
		int secondsTopOfTheHour; /* seconds from 12:00AM, 1 January, 1970 to the current top of the hour*/
	};

	enum TIMESTAMP_MASK
	{
		ABSOLUTE_TIMESTAMP_MASK = 0x00000001,		//If sync'd to NTP/GPS Clock
		RELATIVE_TIMESTAMP_MASK = 0xFFFFFFFE		//If not sync'd to NTP
	};

	enum HOUR_QUARTER
	{
		QUARTER_ONE = 1,
		QUARTER_TWO = 2,
		QUARTER_THREE = 3,
		QUARTER_FOUR = 4,
	};

	class EXPORT_MACRO CDISTime
	{
	public:
		_DISTimeStruct		_timeSince1970;
		TIMESTAMP_MASK		_timeStampMask;
		_Time               _lastPduRecTime; // To be checked whether this line will stay here or not

	public:
		CDISTime();
		~CDISTime();

		void SetTimeStampMask(TIMESTAMP_MASK mask);
		unsigned int GetTimeStamp();
		static int GetQuarterOfHour(const _Time t);

		COMPARISON_RESULT ComparePduTimeStamp(_Time t, _Time& lagTime);
		COMPARISON_RESULT ComparePduTimeStamp(_Time t, unsigned int prePduTimeStamp);

		static void TimeStampToTime(unsigned int timeStamp, int& seconds, int& milliSeconds, int& microSeconds, TIMESTAMP_MASK& timeStampMask);
		static void DoubleTimeInSecsToTime(double doubleTimeInSecs, int& seconds, int& milliSeconds, int& microSeconds);
		static std::tuple<double, COMPARISON_RESULT>  GetTimeDifference(_Time prevTime, _Time currTime, double& timeDifferenceInSecs, bool isRelative = false);
		static void CalculateClockSkew(_Time localTopOfHour, _Time currPduTime, double& clockSkew);
		static void GetCurrPduTimeRelativeToLocal(double dblAvgClockSkew, _Time currPduTime, _Time& currPduTimeRelativeToLocal);
		_Time Update();
		static std::string TimeStampToReadable(time_t);

	private:

		static bool UpdateTime(_DISTimeStruct* t);
		_Time CalculateTimeDifference(_Time t);
		static void GetCurrTime(/*@out@*/ struct mytimeb* tb);
		static int GetSecondsSinceTopOfHour(time_t timeSince1970);
	};
}

