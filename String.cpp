#include "String.h"
#include <iostream>
#include <cassert>

String::~String()
{
    if (StringData != nullptr)
    {
        delete[] StringData;
        StringData = nullptr;
        Invariant();
    }    
}

String::String()
{   
    StringSize = 0;
    StringCapacity = 10; // Set initial value for fewer reallocations
    
    StringData = new char[StringCapacity];
    
    Invariant();
}

String::String(const String& rhs)
{
    StringSize = rhs.StringSize;
    StringCapacity = rhs.StringCapacity;

    StringData = new char[StringCapacity];

    strcpy_s(StringData, StringCapacity, rhs.StringData); // Copy all the elements from rhs.StringData
}


String::String(const char* cstr)
{
    StringSize = strlen(cstr);
    StringCapacity = StringSize * 2;
    StringData = new char[StringCapacity];

    strcpy_s(StringData, StringCapacity, cstr);

    Invariant();
}


void String::PushBack(char c)
{
    if (StringData != nullptr)
    {
        if (Size() + 1 >= Capacity()) // If all the allocated memory is occupied, reallocate for larger string 
        {
            StringCapacity = StringSize * 2 + 1; // Set the new capacity of the string

            char* newStringData = new char[StringCapacity];
            strcpy_s(newStringData, StringCapacity, StringData); // Copy all the previous chars from data to newData

            delete[] StringData; // Delete the previously allocated memory
            StringData = newStringData; // Point to the new allocated memory
        }

        StringData[StringSize++] = c;
        StringData[StringSize] = '\0'; // Set null terminator at the end

        Invariant();
    }
}


size_t String::Size() const
{
    return StringSize;
}

size_t String::Capacity() const
{
    return StringCapacity - 1; // Don't include null terminator (-1)
}

String& String::operator=(const String& rhs)
{
    if (this == &rhs)
    {
        return *this; // Return early for self-assignment
    }

    if (rhs.StringSize >= Capacity())
    {
        StringCapacity = rhs.StringSize * 2 + 1; // Set the new capacity of the string

        char* newStringData = new char[StringCapacity];
        memcpy(newStringData, rhs.StringData, rhs.StringSize); // Copy data from rhs

        delete[] StringData; // Delete the previously allocated memory
        StringData = newStringData; // Point to the new allocated memory
    }
    else
    {
        StringSize = rhs.StringSize; // Update the size
        memcpy(StringData, rhs.StringData, rhs.StringSize); // Copy data from rhs
    }

    return *this;
}



char& String::operator[](size_t i)
{
    return StringData[i]; // Return the chosen element (for writing)
}

const char& String::operator[](size_t i) const
{
    return StringData[i]; // Return the chosen element (for reading)
}

const char* String::Data() const
{
    return StringData; // Return the array
}

void String::Invariant() const
{
    assert(StringSize <= StringCapacity); // Always check so that the StringSize isn't bigger than stringCapacity
}

bool operator==(const String& lhs, const String& rhs)
{
    if(lhs.Size() != rhs.Size())
    { 
        return false; // If size is not the same, they are not the same
    }

    for (size_t i = 0; i < lhs.Size(); i++)
    {
        if (lhs[i] != rhs[i])
        {
            return false; // If contents of the array is not the same, they are not the same
        }
    }

    return true;
}

bool operator!=(const String& lhs, const String& rhs)
{
    return !(lhs == rhs); // return that left hand side is not equal to right hand side
}

std::ostream& operator<<(std::ostream& out, const String& rhs)
{
    return out << rhs.Data(); // Print the Data to the cout
}