#pragma once

// Capacity is always at least one more than lenght.
// Lenght is the character count, not including the null terminator character.
struct String
{
	char* buffer;
	Allocator_Shell* alloc;
	u32 lenght;		// Character count of the string. Does not include the null terminator.
	u32 capacity; 	// The memory reserved for the string.
	
	
	// CONSIDER: To member function or not? For some reason feels good here.
	void append_character(char c);
	void insert_at(u32 idx, char c);
	void remove_at(u32 idx);
	void erase(u32 from, u32 to);
	void pop_last();
	void free();
};


struct String_View
{
	char* buffer = 0;
	u32 lenght = 0;
};


static String_View Create_String_View(String* str)
{
	Assert(str);
	Assert(str->buffer);
	Assert(str->lenght);
	
	String_View result = {str->buffer, str->lenght};
	
	return result;
}


static String_View Create_String_View(char* c_str)
{
	Assert(c_str);
	String_View result = {c_str, Null_Terminated_Buffer_Lenght(c_str)};
	return result;
}


static String_View Create_String_View(String* str, u32 start, u32 lenght)
{
	Assert(str);
	Assert(str->buffer);
	Assert(str->lenght);
	Assert(str->buffer + start + lenght <= str->buffer + str->lenght);
	
	String_View result = {str->buffer + start, lenght};
	
	return result;
}


static void String_Init_Alloc(String* str, u32 capacity)
{
	if(capacity < str->alloc->min_alloc_size)
		capacity = str->alloc->min_alloc_size;
	
	str->capacity = capacity;
	
	str->buffer = (char*)str->alloc->push(capacity);
	Mem_Zero(str->buffer, str->capacity);
}


static void Copy_String(String* dest, String* src)
{
	Assert(dest);
	Assert(src);
	
	dest->lenght = src->lenght;
	dest->alloc = src->alloc;
	
	String_Init_Alloc(dest, src->capacity);
	
	if(src->lenght)
		Mem_Copy(dest->buffer, src->buffer, src->lenght);
}


static String Create_Copy_String(String* src)
{
	String result;
	Copy_String(&result, src);
	
	return result;
}


// Takes a null terminted C style string, as an argument. Lenght of it, determines capacity.
static void Init_String(String* str, Allocator_Shell* allocator, char* c_str)
{
	Assert(allocator);
	Assert(c_str);
	
	u32 lenght = Null_Terminated_Buffer_Lenght(c_str);
	
	str->lenght = lenght;
	str->alloc = allocator;
	
	String_Init_Alloc(str, lenght + 1);
	if(str->lenght > 0)
		Mem_Copy(str->buffer, c_str, lenght);
	
	str->buffer[lenght] = 0;
}


static inline String Create_String(Allocator_Shell* allocator, char* c_str)
{
	String result;
	Init_String(&result, allocator, c_str);
	
	return result;
}


static void Init_String(String* str, Allocator_Shell* allocator, u32 capacity)
{
	Assert(allocator);
	
	str->lenght = 0;
	str->alloc = allocator;
	
	String_Init_Alloc(str, capacity);
}


static inline String Create_String(Allocator_Shell* allocator, u32 capacity)
{
	String result;
	Init_String(&result, allocator, capacity);
	
	return result;
}


static void Init_String(String* str, Allocator_Shell* allocator, char* c_str1, char* c_str2)
{
	Assert(allocator);
	
	u32 lenght1 = Null_Terminated_Buffer_Lenght(c_str1);
	u32 lenght2 = Null_Terminated_Buffer_Lenght(c_str2);

	str->lenght = lenght1 + lenght2;
	str->alloc = allocator;
	
	String_Init_Alloc(str, str->lenght+ 1);
	if(lenght1 > 0)
		Mem_Copy(str->buffer, c_str1, lenght1);
	
	if(lenght2 > 0)
		Mem_Copy(str->buffer + lenght1, c_str2, lenght2);
	
	str->buffer[str->lenght] = 0;
}


static inline String Create_String(Allocator_Shell* allocator, char* c_str1, char* c_str2)
{
	String result;
	Init_String(&result, allocator, c_str1, c_str2);
	
	return result;
}


static void Init_String(
	String* str, 
	Allocator_Shell* allocator, 
	char* c_str1, 
	char* c_str2, 
	char* c_str3)
{
	Assert(allocator);
	
	u32 lenght1 = Null_Terminated_Buffer_Lenght(c_str1);
	u32 lenght2 = Null_Terminated_Buffer_Lenght(c_str2);
	u32 lenght3 = Null_Terminated_Buffer_Lenght(c_str3);

	str->lenght = lenght1 + lenght2 + lenght3;
	str->alloc = allocator;
	
	String_Init_Alloc(str, str->lenght+ 1);
	if(lenght1 > 0)
		Mem_Copy(str->buffer, c_str1, lenght1);
	
	if(lenght2 > 0)
		Mem_Copy(str->buffer + lenght1, c_str2, lenght2);
	
	if(lenght3 > 0)
		Mem_Copy(str->buffer + lenght1 + lenght2, c_str3, lenght3);
	
	str->buffer[str->lenght] = 0;
}


static inline String Create_String(
	Allocator_Shell* allocator, 
	char* c_str1, 
	char* c_str2, 
	char* c_str3)
{
	String result;
	Init_String(&result, allocator, c_str1, c_str2, c_str3);
	
	return result;
}


static void Init_String(
	String* str, 
	Allocator_Shell* allocator, 
	char* c_str1, 
	String* str2, 
	char* c_str3)
{
	Assert(allocator);
	
	u32 lenght1 = Null_Terminated_Buffer_Lenght(c_str1);
	u32 lenght3 = Null_Terminated_Buffer_Lenght(c_str3);

	str->lenght = lenght1 + str2->lenght + lenght3;
	str->alloc = allocator;
	
	String_Init_Alloc(str, str->lenght+ 1);
	if(lenght1 > 0)
		Mem_Copy(str->buffer, c_str1, lenght1);
	
	if(str2->lenght > 0)
		Mem_Copy(str->buffer + lenght1, str2->buffer, str2->lenght);
	
	if(lenght3 > 0)
		Mem_Copy(str->buffer + lenght1 + str2->lenght, c_str3, lenght3);
	
	str->buffer[str->lenght] = 0;
}


static void Init_String(String* str, Allocator_Shell* allocator, char* c_str, u32 max_characters)
{
	Assert(allocator);
	Assert(c_str);
	
	u32 lenght = 0;
	char* c = c_str;
	for(; lenght < max_characters && *c != 0; ++lenght, ++c){}
	
	str->lenght = lenght;
	str->alloc = allocator;
	
	String_Init_Alloc(str, lenght + 1);
	if(str->lenght > 0)
		Mem_Copy(str->buffer, c_str, lenght);
	
	str->buffer[lenght] = 0;
}


inline void String::append_character(char c)
{
	if(capacity == 0)
	{
		Assert(lenght == 0);
		String_Init_Alloc(this, 2);
	}
	
	else if(lenght >= capacity - 1)
	{
		// CONSIDER: What kind of growth function to use here?
		capacity += 1;
		capacity = i32(capacity * 1.5f);
		char* mem = (char*)alloc->push(capacity);
		Mem_Zero(mem + lenght, capacity - lenght);
		if(buffer)
		{
			Mem_Copy(mem, buffer, lenght);
			alloc->free(buffer);			
		}
		buffer = mem;
	}
		
	*(buffer + lenght) = c;
	lenght += 1;
}


inline void String::pop_last()
{
	Assert(lenght > 0);
	buffer[lenght - 1] = 0;
	lenght -= 1;
}


inline void String::insert_at(u32 idx, char c)
{
	Assert(idx <= lenght);
	
	if(idx == lenght)
	{
		append_character(c);
	}
	else
	{
		// "append_character" Is used to grow the string if need be,
		// but it also increases the lenght by one. Normaly this is desired.
		// Problem is that "Insert_Element_Into_Packed_Array" also increases the character
		// count. We don't want to increase lenght twise so as a hack,
		// after appending lenght is reduced by one, so it ends up being tracked corretly.
		
		append_character(0);
		lenght -= 1; // :(
		
		// TODO: Make a Insert_Element_Into_Packed_Byte_Array function.
		// A version of the function that assumes size 1.
		Insert_Element_Into_Packed_Array(buffer, &c, &lenght, sizeof(*buffer), idx);
	}
}


inline void String::remove_at(u32 idx)
{
	Assert(idx <= lenght);
	
	if(idx == lenght)
		pop_last();
	else
	{
		// TODO: Make a Remove_Element_From_Packed_Byte_Array function.
		// A version of the function that assumes size 1.
		Remove_Element_From_Packed_Array(buffer, &lenght, sizeof(*buffer), idx);
	}
}


// "To" is exclusive.
inline void String::erase(u32 from, u32 to)
{
	for(u32 i = from; i < to; ++i)
		remove_at(from);
}


inline void String::free()
{
	if(buffer)
		alloc->free(buffer);

	buffer = 0;
	lenght = 0;
	capacity = 0;
}


static void operator += (String& str, char c)
{
	str.append_character(c);
}


static bool String_Compare(String* a, String* b)
{
	if(a->lenght != b->lenght)
		return false;
	
	char* aa = a->buffer;
	char* bb = b->buffer;
	
	u32 c = 0;
	while(*aa++ == *bb++)
	{
		if(++c == a->lenght)
			return true;
	}
	
	return false;
}