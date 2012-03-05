---
title: Why you should (or should you?) roll your own memory manager (Part 1)
kind: article
created_at: 2011-10-06 10:51
tags: ['C++', 'memory management']
---

### Intro

Do you write performance-critical applications? Do you feel that the built in
memory manager in C/C++ does not do the trick for you? Then this
article might be of interest :)

All optimizations must however be based on real data so if a custom
memory manager does not improve the performance of your application (or maybe
some other aspect), do not use it!

In high performance applications (for example games), allocation of dynamic memory can be a
real bottleneck and should be kept to a minimum. Of course, it is
impossible to avoid altogether and something has to be done.

The built in memory manager in C/C++ has to handle a lot of different
allocation patterns in a good way. It has to be able to allocate many
small blocks of memory as well as large blocks and it has no knowledge
of the data it has to allocate memory for. This is probably not the
case in your own application. You will know what kind of data your
application handles and therefore can make very important assumptions
to make memory management more efficient and simple whereas the built in memory
manager has to be everything to every application. This makes it
inefficient and also too complicated in some cases.

It also suffers in performance from the fact that is has to switch
from user to kernel mode for each request. This can be avoided with
custom memory management where a large block of memory can be
allocated up front and memory request satisifed from this block. This
means that no mode-switching occurs and we can avoid that bottleneck.

### Placement new

To be able to write your own memory manager and control how data is
laid out in memory, there is an important operator in C/C++ that you
have to know: placement `new`.

Placement `new` lets you specify a memory address where you want to
place your objects.

    #!cplusplus
	void *buffer = new byte[SOME_SIZE];
	MyObject *obj = new (buffer) MyObject();
	
This will place the new instance of `MyObject` at the start of
`buffer`. This operator allows you to control your memory allocation
patterns.

Important to note here is that memory allocated by placement `new` can
not be freed with `delete`. The object destructor has to be called
explicitly: `obj->~MyObject();`.

### When to allocate the memory?

Your application will often have some kind of "memory budget", the
maximum amount of memory it can use. Then it can be a good idea to
allocate a chunk of memory that big when the application starts up and
then divide it and use it (as suggested by Christian Gyrling
[here](http://www.swedishcoding.com/2008/08/31/are-we-out-of-memory/)).

You probably need some extra memory for debugging purposes so you can
allocate that memory in a separate "debugging" chunk.

Of course it is also possible to allocate memory "as we go" and your
custom memory manager will still make it a lot easier to keep track of
your memory usage, detect memory leaks, make memory alignment easier
etc.

In the next part, I will get down to business and show some allocator
implementations. So until then, think about your data access patterns ;)
