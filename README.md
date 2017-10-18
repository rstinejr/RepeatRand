# RepeatRand

I was using rand() to generate handles to objects, and saw a bunch of weird behavior. Finally I learned that the way I was using
```rand()``` caused it to emit duplicate values within a very short span. This caused problems, particularly when one thread closed and freed an object identified by a handle, and another thread tried to use that same handle to retrieve the object and execute its methods.

This tiny project replicates that behavior.

# Building and Running

I created this project on 64-bit Windows 10, using VisualStudio 2017. You can download 
the free, community version VisualStudio from https://dot.net.

The code lauches a few threads. Each thread gets a value from ```rand()```. If
two threads generate the same value, then the code throws an exception.


# Why Does This Happen?

The ```rand()``` method uses the value of the last pseudo random number to produce the next one. Perhaps this context is unique to each thread.
