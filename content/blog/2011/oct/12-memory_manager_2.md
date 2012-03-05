---
title: How to roll your own memory management system - Part 2
kind: article
created_at: 2011-10-12 18:19
tags: ['C++', 'memory management']
---

### Introduction
In this post, I am going to start talking about implementation of the
actual allocators. This post will in particular deal with the simplest
kind of allocator, the stack allocator.

The need for allocating aligned memory often arises. 128 bit SIMD
vectors for example has to be 16-bit aligned. That is the hexadecimal
address has to end with the nibble 0x0. To account for that I will
also discuss what is needed to extend the allocators to handle aligned
memory allocation.

### A simple Allocator interface

So now we are ready to start defining a simple interface for
allocators. The question arises whether to have the allocators as
full-fledged classes with virtual functions and all that. In this case
it is definately ok since you will probably not create a lot of memory
allocators and memory management is an expensive operation anyway so
the few extra virtual calls wont matter.

The interface will look something like this

    #!cplusplus
	class Allocator
    {
	
    public:
	    virtual void *allocate(uint32 size, uint32 align) = 0;    
	    virtual void deallocate(void *p) = 0;
	    virtual uint32 allocated_size(void *p) = 0;

	    virtual uint32 get_free() = 0;
        virtual uint32 get_used() = 0;

    };

With this interface ready we can start defining a concrete
allocator. The allocation method `allocate` will return a pointer to
allocated memory where the object can then be placed with
placement `new`.

But wait, how do we actually obtain memory from the OS? The above
interface suggest that we do not want to override global `new`. That
is correct. It is much better if each allocator actually has a backing
allocator that fetches raw memory directly from the OS in a
system-dependent manner. This makes it possible to disallow the use of
`new` and `malloc` globally by asserting (or something like it).

### The Stack Allocator

A stack allocator works by allocating in a stack pattern (duh
:P). This is implemented by holding a pointer to the current top of
the stack. Each new allocation is placed on this stack top and the top
pointer is moved to the end of the newly allocated object. The pointer
then points to the new top of the stack.

The pattern is demonstrated in the figure below.

![Stack Allocator](/blog/2011/oct/img/stack_allocator.png)

The pointers to the top and bottom of the stack is illustrated below.

![Stack Allocator Pointers](/blog/2011/oct/img/stack_allocator_pointers.png)

Note that an extra pointer is introduced in the figure above, the
marker. In a stack allocator you could implement this functionality to
provide users of the allocators with a way to hold a reference to a
specific position in the stack. This becomes handy when deallocation
is done with the stack allocator (Object pointers is also markers though). 

Deallocation is simply a matter of rolling the top pointer back to a lower point. This also means that
allocations can not be done in arbitrary order, they have to take place
in an order that is the reverse of allocations.

Now we can make an implementation of a stack allocator

    #!cplusplus
	class StackAllocator : public Allocator
    {
    public:

	    explicit StackAllocator(const uint32, Allocator *);

	    ~StackAllocator();

	     void *allocate(uint32, uint32);

	     void deallocate(void *p);
	
	     uint32 allocated_size(void *p);

         uint32 get_free() { return _size - _allocated_size; }
	     uint32 get_used() { return _allocated_size; }

	     void clear();

    private:
	     Marker _bottom;
	     const uint32 _size;

	     Marker _top, _latest;
	     uint32 _allocated_size;

	     Allocator *_backing_allocator;
    };
	
We can see from this that the allocator holds a pointer to a backing
allocator, an allocator that retrieves raw memory from the OS or
another type of allocator.

To implement the allocate method (first without alignment)

    #!cplusplus
	void *StackAllocator::allocate(uint32 size, uint32 align)
	{
	    if (_size >= (_top+size)-_bottom)
	    {
		    uint32 raw_address = _top;
		    _top += size;
		    _allocated_size += size;

		    return (void*) raw_address;
	    }
	
	    // If we get here we are out of memory :(
	    XASSERT(false, "Out of memory!");
	    return NULL;
	}
	
This is simple enough and it gets the job done nicely, but what about
the alignment now?

To align the allocation we modify the method slightly

    #!cplusplus
    void *StackAllocator::allocate(uint32 size, uint32 align)
    {
	    // Fix proper alignment
	    if (align > 1)
	    {
		    uint32 expanded_size = size + align;

		    if (_size >= (_top+expanded_size)-_bottom)
		    {
			    // Allocate memory
			    _allocated_size += expanded_size;
			    uint32 raw_address = _top;
			    _top += expanded_size;
			
			    // Adjustment
			    uint32 mask = (align - 1);
			    uint32 misalignment = (raw_address & mask);
			    uint32 adjustment = align - misalignment;

			    uint32 aligned_address = 
				     raw_address + adjustment;

			    // Store the alignment
			    // in the extra byte allocated
			    uint8 *p_adjustment = 
				    (uint8*)(aligned_address-1);
			    *p_adjustment = (uint8) adjustment;

			    return (void*)aligned_address;
		    }
	    }
	    else // Allocate unaligned
	    {
		    if (_size >= (_top+size)-_bottom)
		    {
			    uint32 raw_address = _top;
			    _top += size;
			    _allocated_size += size;

			    return (void*) raw_address;
		    }
	    }

	    // If we get here we are out of memory :(
	    XASSERT(false, "Out of memory!");
	    return NULL;
    }

This is the complete allocation method. The problem here is that the
deallocation has to be done in two different ways depending on whether
the allocation is aligned or not but that can be solved in a number of
different ways, for example to have an unaligned version of both
`allocate` and `deallocate`. The best way would be to store the alignment even when alignment is 1.
This way the `deallocate` method can still know how to deallocate.
Either way, all allocators should have the ability to allocate aligned memory.

Worth to note in the above method is that the alignment of memory is
stored in the extra bytes allocated.

That is all for now and I hope this gave you a better understanding of
the stack allocator. In the next part i will discuss the pool
allocator and some alternative allocators.

### Further resources
- [The always great Niklas Frykholm on memory allocation in BitSquid engine](http://bitsquid.blogspot.com/2010/09/custom-memory-allocation-in-c.html)
- [Christian Gyrlings excellent article on memory management](http://www.swedishcoding.com/2008/08/31/are-we-out-of-memory/)
