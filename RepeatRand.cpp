#include <SDKDDKVer.h>
#include <Windows.h>

#include <exception>
#include <iostream>
#include <mutex>
#include <set>
#include <sstream>

bool shutdownThreads = false;

std::mutex    randMtx;
std::set<int> rands;

/*
* GetRand: get a value from rand(). If it is the same as a previously generated value, throw
* an exception.  All actions within this method are synchornized by mutex randMtx.:w
*/
int GetRand()
{	
	static int cnt = 0;

	std::lock_guard<std::mutex> lock(randMtx);

	int r = rand();

	std::set<int>::iterator iter;
	iter = rands.find(r);
	if (iter != rands.end())
	{
		// Whups - r is already in rands!
		std::stringstream strm;
		strm << "Dup rand " << r << " found, after " << rands.size() << " successfully generated." << std::endl;;

		std::cerr << strm.str().c_str() << std::endl;

		throw new std::exception(strm.str().c_str());
	}

	rands.insert(r);
	
	std::cout << "Rand value " << r << " generated, number " << ++cnt << std::endl << std::flush;

	return r;
}

/*
* Function executed by threads. It gets a random value, then goes into a sleep/check/sleep loop until 
* the global bool "shutdownThreads" is set.
*/
extern "C" DWORD WINAPI MyThreadFunc(LPVOID threadParam)
{
	int h = GetRand();

	while (!shutdownThreads)
	{
		Sleep(2);
	}

	return 0;
}

int main()
{
	const int THREAD_CNT = 3;
	HANDLE threads[THREAD_CNT] = { 0, };

	std::cout << "Kick off threads." << std::endl << std::flush;

	for (int ii = 0; ii < THREAD_CNT; ii++) 
	{
		threads[ii] = CreateThread(
			NULL,                 // Default security attributes
			0,                    // Use default stack size  
			MyThreadFunc,         // Thread function name
			NULL,                 // Argument to thread function 
			0,                    // Use default creation flags 
			NULL);                // Address of thread identifier. Null for not interested.
	}

	Sleep(2000);
	shutdownThreads = true;
	WaitForMultipleObjects(THREAD_CNT, threads, TRUE, INFINITE);

	std::cout << "All threads completed. Ciao!" << std::endl;

    return 0;
}

