# RepeatRand

I was using rand() to generate handles to objects, and saw a bunch of weird behavior. Finally I learned that the way I was using
```rand()``` caused it to emit duplicate values within a very short span. This caused problems, particularly when one thread closed and freed an object identified by a handle, and another thread tried to use that same handle to retrieve the object and execute its methods.

This tiny project replicates that behavior.

# Why Does This Happen?

The rand() method uses the value of the last pseudo random number to produce the next one. Perhaps this context is unique to each thread.
