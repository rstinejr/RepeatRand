# RepeatRand

I was using rand() to generate handles to objects, and saw a bunch of weird behavior. Finally I learned that the way I was using
```rand()``` caused it to emit duplicate values within a very short span. This caused problems, particularly when one thread closed and freed an object identified by a handle, and another thread tried to use that same handle to retrieve the object and execute its methods.

This GitHub project has code for several C++ projects that explore this behavior.

* RepeatRand - A program that mimics the control flow of the program in which seemingly weird behavior from ```rand()``` caught my attention. C++ on Windows.

* Series - A program that shows the initial values from ```rand()``` from several threads.

# Why Are Values Repeated?

The ```rand()``` method uses the value of the last pseudo random number to produce the next one. Perhaps this context is unique to each thread, and each thread is starting 
with the same initial values.

Microsoft's documentation on the [```srand()``` function](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/srand) says that the function only sets ths
seed value for ```rand()``` within the calling thread, and that other threads are not 
affected.  This is consistent with the behavior of *RepeatRand*: calling ```srand()``` 
from the main thread does not change the output ```rand()``` when called from the
worker threads.  All of which is to say that in the Windows standard library, each
thread has a separate state for ```rand()```. The algoritm implemented by ```rand()``` 
is deterministic, so identical state produces identical output.

# What's Next?

I wonder if this happens on Linux?
