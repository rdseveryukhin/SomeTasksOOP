#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy
using namespace std;

struct String {
	String(const char* str = "") :size(strlen(str)), str(0)
	{
		this->str = new char[size + 1];
		strcpy(this->str, str);
	}

	String(size_t n, char c) :size(n), str(0)
	{
		this->str = new char[size + 1];
		for (int i = 0; i < size; this->str[i] = c, ++i);
		str[size] = '\0';
	}

	~String()
	{
		delete[] str;
	}

	String(const String& other) :size(other.size)
	{
		str = new char[size + 1];
		strcpy(str, other.str);
	}
	String& operator=(const String& other)
	{
		delete[] str;
		size = other.size;
		str = new char[size + 1];
		for (int i = 0; i <= size; this->str[i] = other.str[i], ++i);
	}

	void append(String& other)
	{
		size += other.size;
		char* new_str = new char[size + 1];
		strcpy(new_str, str);
		strcat(new_str, other.str);
		delete[] str;
		str = new_str;
	}

	char* print() {
		return str;
	}

	struct SubStr;
	SubStr operator[](size_t i) const;

private:
	size_t size;
	char* str;
};

struct String::SubStr
{
	SubStr(const String& s, size_t shft) : sub(s), shift(shft) {}

	String operator[](size_t i)
	{
		sub.str[i - shift] = 0;
		return String(sub.str);
	}

	String sub;
	size_t shift;
};

String::SubStr String::operator[](size_t i) const
{
	return String::SubStr(String(str + i), i);
}

int main()
{
	String const hello("hello");
	String hell = hello[0][4]; // now hell hold substring "hell"
	String ell = hello[1][4]; // now ell hold substring "ell"

	cout << hell.print() << endl;
	cout << ell.print() << endl;
}
