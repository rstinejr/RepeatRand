# RepeatRand

I was using rand() to generate handles to objects, and saw a bunch of weird behavior. Finally I learned that the way I was using
```rand()``` caused it to emit duplicate values within a very short span.

This tiny project replicates that behavior.
