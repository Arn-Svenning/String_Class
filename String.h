#pragma once

#include <iostream>
#include <vector>
class String
{

public:

	~String();

	String();

	String(const String& rhs);
	String(const char* cstr);

	

#pragma region FUNCTIONS

public:

	void PushBack(char c);

	size_t Size() const;

	size_t Capacity() const;

	String& operator = (const String& rhs);

	char& operator[](size_t i);

	const char& operator[](size_t i) const;

	const char* Data() const;

protected:

private:

	friend bool operator == (const String& lhs, const String& rhs);

	friend bool operator != (const String& lhs, const String& rhs);

	friend std::ostream& operator<< (std::ostream& out, const String& rhs);

	void Invariant() const;
	
#pragma endregion

#pragma region VARIABLES

public:

protected:

private:

	char* StringData;

	size_t StringCapacity; // The allocated capacity for the string
	size_t StringSize; // The size of the string

#pragma endregion



};

