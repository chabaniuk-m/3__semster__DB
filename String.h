#ifndef STRING
#define STRING

#include <limits.h>
#include "Util.h"

class String
{
	char* text;
	int length;

public:

	String();
	String(const char* str);
	String(const String const* other);
	~String();

	String* substr(int offset, int to = INT_MAX) const;
	String** split(int& length, char delim = '\t') const;
	char* getData();

	void append(const char* other);
	void append(const String const* other);

	bool equals(String* other) const;
	bool equals(const char* str) const;
	int compareTo(String* other, bool caseSensetive = true) const;
	int compareTo(const char* str, bool caseSensetive = true) const;
	bool startsWith(const char* str, bool caseSensetive = true) const;
	bool empty() const;
	char at(int index) const;
	char operator[] (int index) const;
	char& operator[] (int index);

	void print() const;
	void println() const;

private:
	String(int length);
	bool checkBounds(int index) const;
	bool equals(const char* s1, const char* s2) const;
	bool isUpperLetter(char c) const;
	char toLower(char upperLetter) const;
	void append(const char* other, const int len);

};

#endif // !STRING
