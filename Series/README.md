# Series Project

This tiny project generates a sequence from ```rand()``` from several concurrent threads. It 
demonstrates that:

1. Each thread has its own context for generating a value from ```rand()```.
2. If two threads have the same initial context, they generate the same sequence from 
```rand()```.`

# Building

I created this project on 64-bit Windows 10, using VisualStudio 2017. You can download 
the free, community version VisualStudio from 

    https://www.visualstudio.com/vs/community/ 


I built the executable using VisualStudio 2017. The solution file is ```RepeatRand.sln```.

# Running

The program can be run from the IDE or the command line. The command line is:


```
Sequence
```

# What Does It Do?

The code lauches a few threads. Each thread calls ```rand()``` a few times, and saves 
the values in a vector. 

After all the threads have completed, the main thread displays the values written by each 
thread.


Here's the output I see on my laptop:

```
D:\dev\C++\RepeatRand\Series\x64\Debug>Series.exe
Kick off threads. Each will generate the first 8 values from rand().

All threads have terminated.

rand() sequence from thread 0: 41 18467 6334 26500 19169 15724 11478 29358
rand() sequence from thread 1: 41 18467 6334 26500 19169 15724 11478 29358
rand() sequence from thread 2: 41 18467 6334 26500 19169 15724 11478 29358

D:\dev\C++\RepeatRand\Series\x64\Debug>
```
