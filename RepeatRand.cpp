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

int GetRand()
{	
	std::lock_guard<std::mutex> lock(randMtx);

	int r = rand();

	std::set<int>::iterator iter;
	iter = rands.find(r);
	if (iter != rands.end())
	{
		std::stringstream strm;
		strm << "Dup rand found: " << r;
		throw new std::exception(strm.str().c_str());
	}
	
	rands.insert(r);
	
	return r;
}

extern "C"
DWORD WINAPI MyThreadFunc(LPVOID threadParam)
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
	const int THREAD_CNT = 10;
	HANDLE threads[THREAD_CNT] = { 0, };

	std::cout << "Kick off threads." << std::endl;

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
