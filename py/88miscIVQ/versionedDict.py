
'''Req: Suppose a resume consists of key/value pairs of strings. Within a resume, these keys are non-repeating. We need to optimize two operations
* Each update(key, value) operation creates or updates a key with a new value, and returns an incremented vid as an int
* Each getResume(vid) returns a key/value dictionary at the specified snapshot
* I think in a realistic syste, we also need a deleteVersion(vid)

By definition, the initial version is an empty version 0.
'''