#include <SDKDDKVer.h>
#include <Windows.h>

#include <exception>
#include <iostream>
#include <mutex>
#include <set>
#include <sstream>

static std::string CHECK("--check");
static std::string HELP("--help");

bool shutdownThreads = false;
bool checkForDups    =  false;

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

	int r;

	if (!checkForDups)
	{
		r = rand();
		std::set<int>::iterator iter = rands.find(r);
		if (iter != rands.end())
		{
			// Whups - r is already in rands!
			std::stringstream strm;
			strm << "Dup rand " << r << " found, after " << rands.size() << " successfully generated." << std::endl;;

			std::cerr << strm.str().c_str() << std::endl;

			throw new std::exception(strm.str().c_str());
		}
	}
	else
	{
		// Handle dups
		for (; ; )
		{
			r = rand();
			std::set<int>::iterator iter = rands.find(r);
			if (iter == rands.end())
			{
				break;
			}
		}
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

	return h;
}

int main(int argc, char *argv[])
{
	const int THREAD_CNT = 20;
	HANDLE threads[THREAD_CNT] = { 0, };

	if (argc > 1)
	{
		std::string arg(argv[1]);
		if (arg == CHECK)
		{
			checkForDups = true;
		}
		else if (arg == HELP)
		{
			std::cout << "usage: " << argv[0] << " [--check | --help]" << std::endl;
			return 0;
		}
		
	}

	std::cout << "Kick off threads. Checking to avoid dups " << ((checkForDups) ? "IS " : "is NOT ") 
		<< "enabled." << std::endl << std::flush;

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

