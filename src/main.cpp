#include <stdio.h>
#include <sys/time.h>
#include <ctime>
#include <string.h>

typedef unsigned char u8;
typedef unsigned long long u64;

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

u64 cpu()
{
	//count checks
	u64 checks = 0;
	
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

u8* memPtr = NULL;
u64 memSize = 0;
u64 memAlloc()
{
	if(!memPtr)
	{
		memPtr = new u8[memSize];
	}
	return memSize;
}
u64 memSet()
{
	if(memPtr)
	{
		memset(memPtr, 0, memSize);
	}
	return memSize;
}
u64 memDel()
{
	if(memPtr)
	{
		delete[] memPtr;
		memPtr = NULL;
	}
	return memSize;
}

double timeJob(u64 (*fptr)())
{
	u64 cnt;
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
	//timeJob(cpu);
	memSize = (u64)1024*1024*2048;
	timeJob(memAlloc);
	//getchar();
	timeJob(memSet);
	getchar();
	timeJob(memDel);
	return 0;
}
