
'''Req: Suppose a resume consists of key/value pairs of strings. Within a resume, these keys are non-repeating. We need to optimize two operations
* Each update(key, value) operation creates or updates a key with a new value, and returns an incremented vid as an int
* Each getResume(vid) returns a key/value dictionary at the specified snapshot
* I think in a realistic syste, we also need a deleteVersion(vid)

By definition, the initial version is an empty version 0.

Q: design an efficient solution. 
Q: What's the (time and space) complexity of next update() after creating N versions? What's the complexity of the next get()?
---
For instance, a simple solution would snapshot entire resume for each updated version. Space complexity is bad, but let's look at time complexity. Worst case -- there are N keys in the resume -- version1 creates key1, version 5 creates key5 etc.
A single get() is O(N) just to read the N fields. I think this is the lowest complexity for get()? I think update() is O(N) since we need to update all N fields

I think the key idea is binary search.

Interviewer said there are ways to beat O(N) read. I felt all tags can be saved in one "big string" to speed up read, but now I feel time-complexity will not improve. 

My design 1 is basically that. I use a vector for each key.

My design 2 is a minor optimization to remove the cloning of unchanged values

My design 3 is lazy update. So update only appends to one vector. The other vectors are updated only when needed. Amortized cost?

My design 4 uses RBTree to optimize for frequent update(). Each update inserts a version into only one tree having height log(T) where T is the typical size of a tree. The sum of all Ts is N, somewhat similar to separate chaining. I feel amortized update cost is O(1)
As to get(), similar story, log(T) for each field, total get() runs in amortized O(N)
'''