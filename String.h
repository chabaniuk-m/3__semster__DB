#ifndef STRING
#define STRING

#include <limits.h>

class String
{
	char* text;
	int length;

public:
	static const int NPOS = INT_MIN;	//searched charecter is not present in the string
	static const int EQUALS = 0;
	static const int GREATER = 1;		//current string starts with another but longer
	static const int LESS = -1;			//another string starts with current so current is shorter

	static String* join(char delim, String* arr[], const int count);
	static bool equals(const char* a, const char* b);

	String();
	String(const char* str);
	String(const String* other);
	~String();

	String* copy() const;
	String* substr(int offset, int to = INT_MAX) const;
	String** split(int& length, char delim = '\t') const;
	//returns the last index of character c or NPOS
	int lastIndexOf(char c) const;
	//returns index of first occurence of the str or NPOS
	int indexOf(const char* str) const;
	char* getData() const;
	int getLength() const { return length; }
	int count(char c) const;

	String* append(const char* other);
	String* append(const String* const other);

	bool equals(const String* other, bool reverse = true) const;
	bool equals(const char* str, bool reverse = true) const;
	bool contains(char c, bool reverse = true) const;
	int compareTo(const String* other, bool caseSensetive = true) const;
	int compareTo(const char* str, bool caseSensetive = true) const;
	bool startsWith(const char* str, bool caseSensetive = true) const;
	bool endsWith(const char* str, bool caseSensetive = true) const;
	bool empty() const;
	char at(int index) const;
	char& at(int index);

	String* operator+ (const String* rhs) const;
	String* operator+ (const char* rhs) const;
	char operator[] (int index) const;
	char& operator[] (int index);

	void print() const;
	void println() const;

private:
	String(int length);
	bool outOfBounds(int index) const;
	//compares 2 strings with the same length which is equals this.length
	bool equals(const char* s1, const char* s2, bool reverse) const;
	bool isUpperLetter(char c) const;
	char toLower(char upperLetter) const;
	void append(const char* other, const int len);

};

#endif // !STRING
