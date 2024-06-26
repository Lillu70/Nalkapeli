
#pragma once

template<typename T>
struct Dynamic_Array
{	
	u32 count;
	u32 capacity;
};


template<typename T>
static Dynamic_Array<T>* Create_Dynamic_Array(Allocator_Shell* allocator, u32 capacity)
{
	Assert(capacity);
	
	u32 size = sizeof(Dynamic_Array<T>) + capacity * sizeof(T);
	
	if(size < allocator->min_alloc_size)
	{
		u32 s = allocator->min_alloc_size - sizeof(Dynamic_Array<T>);
		s /= sizeof(T);
		capacity = s;
		size = sizeof(Dynamic_Array<T>) + capacity * sizeof(T);
	}
	Dynamic_Array<T>* darray = (Dynamic_Array<T>*)allocator->push(size);
	
	darray->count = 0;
	darray->capacity = capacity;

	
	Assert(darray->capacity);
	return darray;
}


template<typename T>
static T* Begin(Dynamic_Array<T>* darray)
{
	return (T*)(darray + 1);
}


template<typename T>
static T* End(Dynamic_Array<T>* darray)
{
	return (T*)(darray + 1) + darray->count;
}


template<typename T>
static T* Push(Dynamic_Array<T>** darray_ptr, Allocator_Shell* allocator)
{
	Assert(*darray_ptr);
	Assert((*darray_ptr)->count <= (*darray_ptr)->capacity);
	
	if((*darray_ptr)->count == (*darray_ptr)->capacity)
	{
		u32 new_capacity = (*darray_ptr)->capacity * 2;
		
		u32 new_size = new_capacity * sizeof(T) + sizeof(Dynamic_Array<T>);
		Dynamic_Array<T>* new_header = (Dynamic_Array<T>*)allocator->push(new_size);
		
		u32 old_size = (*darray_ptr)->capacity * sizeof(T) + sizeof(Dynamic_Array<T>);
		Mem_Copy(new_header, *darray_ptr, old_size);
		allocator->free(*darray_ptr);
		
		new_header->capacity = new_capacity;
		*darray_ptr = new_header;
		
	}
	
	T* result = Begin(*darray_ptr) + (*darray_ptr)->count;
	(*darray_ptr)->count += 1;
	
	return result;
}