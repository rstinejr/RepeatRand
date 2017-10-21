#include <SDKDDKVer.h>
#include <Windows.h>

#include <exception>
#include <iostream>
#include <mutex>
#include <vector>
#include <sstream>

using namespace std;

const int SAMPLE_SIZE = 8;
const int THREAD_CNT  = 3;

vector<int> rands[THREAD_CNT];

/*
* Function executed by threads. It writes a sequence from rand(), then exits.
*/
extern "C" DWORD WINAPI MyThreadFunc(LPVOID threadParam)
{
	int threadID = (int) threadParam;
	cout << "Thread " << threadID << endl;
	return NULL;
}

int main(int argc, char *argv[])
{
	HANDLE threads[THREAD_CNT] = { 0, };

	std::cout << "Kick off threads. Each will generate the first " << SAMPLE_SIZE << " values from rand()." << endl << flush;

	for (int ii = 0; ii < THREAD_CNT; ii++) 
	{
		threads[ii] = CreateThread(
			NULL,                 // Default security attributes
			0,                    // Use default stack size  
			MyThreadFunc,         // Thread function name
			(void *) ii,          // Argument to thread function 
			0,                    // Use default creation flags 
			NULL);                // Address of thread identifier. Null for not interested.
	}

	WaitForMultipleObjects(THREAD_CNT, threads, TRUE, INFINITE);

	std::cout << "All threads completed." << std::endl;

    return 0;
}

