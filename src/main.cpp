#include <stdio.h>
#include <sys/time.h>
#include <ctime>

typedef unsigned long long uint64;
uint64 myTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);

	uint64 ret = tv.tv_usec;
	/* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
	ret /= 1000;

	/* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
	ret += (tv.tv_sec * 1000);

	return ret;
}

struct TimeInt{

	double* _ret = 0;
	double _t = 0;
	
	double myTm()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return double(tv.tv_usec) / 1000000 + tv.tv_sec;
	}
	
	TimeInt(double* ret = 0)
	{
		_ret = ret;
		if(_ret)
		{
			_t = myTm();
		}
	}
	
	~TimeInt()
	{
		if(_ret)
		{
			*_ret = myTm() - _t;
		}
	}
};

uint64 cpu()
{
	//count checks
	uint64 checks = 0;
	
	//numbers to check
	for(int i = 5; i < 300000; i++)
	{
		int x = i / 2;
		int j;
		
		//check for divisor
		for(j = 2; j < x; j++)
		{
			if(i % j == 0)
			{
				break;
			}
		}
		
		//was it prime?
		/*if(j==x)
		{
			printf("%d is prime\n", i);
		}*/
		
		//count checks
		checks += j - 1;
	}
	
	return checks;
}

double timeJob(uint64 (*fptr)())
{
	uint64 cnt;
	double tm;
	{
		TimeInt ti(&tm);
		cnt = fptr();
	}
	double r = double(cnt)/tm;
	printf("%llu iterations in %lfs (%lf)\n", cnt, tm, r);
	return r;
}

int main()
{
	timeJob(cpu);
	return 0;
}
