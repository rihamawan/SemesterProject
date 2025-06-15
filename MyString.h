#ifndef MYSTRING_H
#define MYSTRING_H
#include<iostream>
using namespace std;
class MyString {
	char* str;
	int len;
	int capacity;
	void mystrcpy(char* dest, const char* src);
	void reverse(char* str, int len);
public:
	MyString();
	MyString(char* _str);
	 int mystrlen(const char* str);
	 static int mystrlen(const MyString str);

	MyString(const char* s);
	char* returnArray()const;
	MyString(const char* a, int length);
	MyString(int value);
	MyString(const MyString& s);
	MyString& operator=(const MyString& s);
	void insert_at(int i, char ch);
	void insert_at(int i, const MyString strObj);
	void replace_first(char c);
	static char* itos(int integer);
	int stoi() const;
	MyString& trim();

	// MyString trim(const MyString& s);
	char& operator[](int i);
	const char& operator[](int i)const;
	bool is_equal(const MyString& M) const;

	bool is_less(const MyString& M) const;

	bool is_greater(const MyString& M) const;
	MyString* split(char delimiter, int& partCount)const;
	int* all_sub_strings(const char* substring, int& count) const;
	MyString concat(const MyString& s2) const;
	MyString& append(const MyString& s2);
	//MyString operator+(const MyString& s2) const;
	float toFloat() const;

	MyString& operator+=(const MyString& s2);
	int find_first(char ch) const;

	int find_first(const MyString& s) const;
	int find_last(char ch) const;

	int find_last(const MyString& s) const;

	int* find_all(char ch, int& count) const;
	int* find_all(const MyString& s, int& count) const;
	void remove_at(int i);
	void remove_first(char ch);

	void remove_last(char ch);

	void remove_all(char ch);
	MyString& to_upper();
	//static MyString to_upper(const MyString& s);

	MyString& to_lower();

	//static MyString to_lower(const MyString& s);
	MyString* tokenize(const char* delim, int& count) const;
	void print() const;
	void clear();
	friend ostream& operator<<(ostream& cout, const MyString& s);
	friend istream& operator>>(istream& cin, MyString& s);
	~MyString();
};
#endif
