// Labb5CPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif // _DEBUG
//#include <stdlib.h>
#include <crtdbg.h>
#define VG
#include "String.h"
#include <string>
#include <iostream>
#include <cassert>
#include <utility>
using namespace std;

void AssertStrEqual(const String& lhs, const char* rhs) 
{
	for (size_t i = 0; i < lhs.Size() && *rhs != '\0'; ++i) {
		assert(lhs[i] == rhs[i]);
		assert(rhs[i] != 0);
	}
	assert(rhs[lhs.Size()] == 0);
}
void TestPushBackReallocation() {
	String str("hej");
	assert(str.Size() <= str.Capacity());
	assert(str.Size() == 3);
	auto hej = "hej";
	//AssertStrEqual(str, hej);
	AssertStrEqual(str, "hej");

		auto internalBuf = &str[0];
	auto cap = str.Capacity();
	auto siz = str.Size();
	size_t i;
	std::cout << cap << std::endl;
	for (i = siz + 1; i < cap ; ++i) 
	{
		str.PushBack(char(i) + 'a');
		std::cout << "internalBuf: " << internalBuf << " str: " << &str[0] << std::endl;
		assert(internalBuf == &str[0]);
		assert(cap == str.Capacity());
		assert(i == str.Size());
	}
	str.PushBack(char(i));
	assert(internalBuf != &str[0]);

	assert(cap < str.Capacity());
	assert(i == str.Size());
}
#pragma region DeleteCheckFel
//#pragma push_macro("new")
//#undef new
//
//void* memoryPtr;
//void* operator new(size_t size) {
// memoryPtr = ::malloc(size);
// return memoryPtr;
//}
//
//void operator delete(void* ptr) {
// if (ptr != memoryPtr) {
// cout << "You are deleting the wrong string!?\n";
// }
// ::free(ptr);
//}
//
//void TestDelete() {
// void* sSave = malloc(sizeof(String));
// void* sPtr;
// {
// String s("huj");
// sPtr = &s;
// memcpy(sSave, &s, sizeof(String));
// s.~String();
//#pragma pop_macro("new")
// }
// if (memcmp(sSave, sPtr, sizeof(String)))
// cout << "You are doing uneccessary things in you deconstructor ~String()\
n";
//}
#pragma endregion DeleteCheckFel
void TestDelete() {
	//V lGodk nt (g r att k ra p Godk nt men jag kr ver inte detta!)� � � � � � �
	void* sSave = malloc(sizeof(String));
	void* sPtr;
	{
		String s("hejsan");
		sPtr = &s;
		memcpy(sSave, &s, sizeof(String));
	}
	if (memcmp(sSave, sPtr, sizeof(String)))
		std::cout << "You are doing uneccessary things in you deconstructor ~String()\
n";
	else { //F r att f nga "null" version, tveksamt om den hittar n got!� � �
		{
			String s;
			sPtr = &s;
			memcpy(sSave, &s, sizeof(String));
		}
		if (memcmp(sSave, sPtr, sizeof(String)))
			std::cout << "You are doing uneccessary things in you deconstructor~String()\n";
	}
	delete sSave;
}
void TestCapacitySetting() {
	//F r godk nt� �
	{
		String s, r;
		int size = s.Size();
		for (int i = 0; i < size * 2 + 16; ++i)
			r.PushBack('a' + i % 26);
		s = r;
		assert(s.Size() <= s.Capacity());
	}
	{ //Will probably fail to catch any error :-(
		String r;
		for (int i = 0; i < 65; ++i)
			r.PushBack('a' + i % 26);
		String s(r);
		assert(s.Size() <= s.Capacity());
	}
}
void TestPushBack() {
	//F r Godk nt� �
	{
		String str = "bar";
		str.PushBack('a');
		std::cout << str << " str" << std::endl;
		assert(str == "bara");
	}
	{
		String r;
		int size = 65;
		for (int i = 0; i < size; ++i)
			r.PushBack('a' + i % 26);
		assert(r.Size() <= r.Capacity());
		assert(r.Size() == size);
	}
	//Test No Extra Alloc
	{
		String r;
		int size = 65;
		for (size = 0; size < 65; ++size)
			r.PushBack('a' + size % 26);
		while (r.Size() >= r.Capacity()) {
			r.PushBack('a' + size % 26);
			++size;
		}
		const char* ptr = r.Data();
		int cap = r.Capacity();
		while (ptr == r.Data())
		{
			r.PushBack('x');
		}
		std::cout << r.Size() << cap + 1 << std::endl;
		assert(r.Size() == cap);
	}
}
String* MakeString(size_t size) {
	String* str = new String();
	int i;
	for (i = 0; i < size; ++i)
		str->PushBack('a' + i % 26);
	return str;
}

void TestForGodkant() {
	
		//- String()
		String str0; AssertStrEqual(str0, "");
	//- String(Str ng str ng)� �
	String s1("foo"); assert(s1 == "foo");
	std::cout << s1 << "s1" << std::endl;
	String str(s1); assert(str == "foo");
	std::cout << str << "str" << std::endl;
	String s3("bar"); assert(s3 == "bar");
	std::cout << s3 << "s3" << std::endl;
	//- ~String() Kom ih g destruktorn!�
	delete new String("hej");
	//TestDelete();
	// - operator =(Str ng str ng)� �
	str = "hej";
	std::cout << str << std::endl;
	assert((str = s3) == s3);
	assert((str = str) == s3); //self assignment
	//Ej samma buffert
	str = "hej"; s3 = str;
	std::cout << s3 << "s3" << std::endl;
	str[0] = 'x'; assert(s3[0] == 'h');
	s3[1] = 'y'; assert(str[1] == 'e');
	String str1("foo"), str2("bar"), str3("hej");
	str3 = str = str1;
	assert(str3 == str);
	assert(str1 == str);
	TestCapacitySetting();
	//No extra realloc
	AssertStrEqual(str1, "foo");
	auto xxx = str1.Data();
	str1 = String("huj");

	std::cout << "BRAH" << xxx << "str1" << str1.Data() << std::endl;
	assert(xxx == str1.Data());

	//- operator==
	//testas verallt!�
	{
		String s, r;
		s.PushBack(0);
		s.PushBack(0);
		s.PushBack(0);
		r.PushBack(0);
		
		assert(s != r);
		assert(!(r == s));
	}
	//- operator!=
	assert(str1 != str);
	assert(!(str1 != str1));
	//- operator[](size_t i) som indexerar utan range check.
	str = "bar";
	std::cout << str << "str" << std::endl;
	str[-1]; str[1000]; //No error
	assert(str[1] == 'a');
	str[1] = 'y';
	assert(str[1] == 'y');
	
	//std::cout << str << std::endl;
	const String sc(str);
	std::cout << sc << "sc" << std::endl;
	assert(sc[1] == 'y');
	assert(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value); // Kolla att det blir en const resultat av indexering
		//- push_back(char c)
		TestPushBack();
	// data
	const char* temp = str.Data();
	assert(temp == &str[0]);
	//- size(), capacity() and reloccation test;
	TestPushBackReallocation();
	std::cout << String("hej\n");
	std::cout << "If it says hej on previous line, the test is complete\n"; 
}
//void TestF rV lGodk ntString() {
//	� � �
//#ifdef VG
//		TestDelete();
//	TestNoExtraAlloc();
//	String str("bar");
//	//- at(size_t i) som indexerar med range check
//	try {
//		str.at(-1);
//		assert(false);
//	}
//	catch (std::out_of_range&) {};
//	try {
//		str.at(3);
//		assert(false);
//	}
//	catch (std::out_of_range&) {};
//	//- at indexerar
//	//- at(size_t i)
//	str = "bar";
//	assert(str.at(1) == 'a');
//	str.at(1) = 'y';
//	assert(str.at(1) == 'y');
//	const String strC(str);
//	assert(strC.at(1) == 'y');
//	assert(std::is_const<std::remove_reference<
//		decltype(strC.at(1))>::type>::value); //Kolla att det blir en const resultat av
//	indexering
//		// reserve()
//		auto internalBuf = &str[0];
//	auto cap = str.capacity();
//	auto siz = str.size();
//	str.reserve(cap);
//	assert(internalBuf == &str[0]);
//	assert(cap == str.capacity());
//	assert(siz == str.size());
//	str.reserve(cap + 1);
//	assert(internalBuf != &str[0]);
//	assert(cap < str.capacity());
//	assert(siz == str.size());
//	// shrink_to_fit
//	str = "hej";
//	str.reserve(10);
//	internalBuf = &str[0];
//	cap = str.capacity();
//	siz = str.size();
//	str.shrink_to_fit();
//	assert(internalBuf != &str[0]);
//	assert(str.capacity() == str.size());
//	AssertStrEqual(str, "hej");
//	/////////////////
//	//- operator+=(Str ng str ng) som tolkas som konkatenering.� �
//	//foo, bar, hej
//	String str1("foo"), str2("bar"), str3("hej");
//	((str = "xyz") += str1) += (str3 += str1);
//	assert(str3 == "hejfoo" && str == "xyzfoohejfoo" && str1 == "foo");
//	//+= som f r plats;�
//	str = "bar"; str.reserve(10);
//	str += "foo";
//	assert(str == "barfoo");
//	//+= som inte f r plats;�
//	str.reserve(10);
//	str = "";
//	size_t i;
//	for (i = 0; str.size() < str.capacity(); ++i)
//		str.push_back(char('0' + i));
//	str1 = "bar";
//	str += str1;
//	for (size_t k = 0; k < i; ++k)
//		assert(str[k] == '0' + k);
//	assert(str[i] == 'b');
//	//+= Sj lv assignment� //Borde testa med att capacity tar slut!
//	str = "foo";
//	str += str;
//	assert(str == "foofoo");
//	//- operator+
//	str = "bar";
//	assert(str + "foo" == "barfoo");
//	AssertStrEqual(str, "bar");
//	cout << "\nTestF rV lGodk nt klar\n"; � � �
//#endif //VG
//}
int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	locale::global(locale("swedish"));
	TestForGodkant(); 
		std::cout << "G test klart\n";

	new int;
	cout << "There is a memory leak intentionally";

}

