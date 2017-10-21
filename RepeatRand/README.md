# RepeatRand Project

This tiny project replicates that behavior that piqued my curiosity: ```rand()``` emitted 
duplicate values within a very sort interval.

# Building

I created this project on 64-bit Windows 10, using VisualStudio 2017. You can download 
the free, community version VisualStudio from 

    https://www.visualstudio.com/vs/community/ 


I built the executable using VisualStudio 2017.

# Running

The program can be run from the IDE or the command line. The command line is:


```
RepeatRand [--help | --check]
```

If run with no arguments, the program throws an exception at the frist duplicate return from ```rand()```.


# What Does It Do?

The code lauches a few threads. Each thread gets a value from ```rand()```. If
two threads generate the same value and "--check" was not specified, then the program
throws an exception. If "--check" WAS specified, then the program keeps calling ```rand()``` until it gets a new value.

After retrieving a value from ```rand()```, a
thread loops over a short sleep command until the global bool ```shutdownThreads```
is set, at which point it terminates.


If executed with no arguments,```RepeatRand``` throws an exception at the first duplicate
output from ```rand()```. On my machine, this happens the second time that ```rand()``` is called.

After the exception is dismissed, the output from ```RepeatRand``` is:

```
D:\RepeatRand>x64\Debug\RepeatRand
Kick off threads. Checking to avoid dups is NOT enabled.
Rand value 41 generated, number 1
Dup rand 41 found, after 1 successfully generated.
```

Here is an example of output when "--check" is specified:

```
D:\RepeatRand>x64\Debug\RepeatRand --check
Kick off threads. Checking to avoid dups IS enabled.
Rand value 41 generated, number 1
Rand value 18467 generated, number 2
Rand value 6334 generated, number 3
Rand value 26500 generated, number 4
Rand value 19169 generated, number 5
Rand value 15724 generated, number 6
Rand value 11478 generated, number 7
Rand value 29358 generated, number 8
Rand value 26962 generated, number 9
Rand value 24464 generated, number 10
Rand value 5705 generated, number 11
Rand value 28145 generated, number 12
Rand value 23281 generated, number 13
Rand value 16827 generated, number 14
Rand value 9961 generated, number 15
Rand value 491 generated, number 16
Rand value 2995 generated, number 17
Rand value 11942 generated, number 18
Rand value 4827 generated, number 19
Rand value 5436 generated, number 20
All threads completed. Ciao!
```
