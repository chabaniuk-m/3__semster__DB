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

	String();
	String(const char* str);
	String(const String const* other);
	~String();

	String* copy() const;
	String* substr(int offset, int to = INT_MAX) const;
	String** split(int& length, char delim = '\t') const;
	//returns the last index of character c or NPOS
	int lastIndexOf(char c) const;
	char* getData() const;
	int getLength() const { return length; }

	String* append(const char* other);
	String* append(const String const* other);

	bool equals(String* other) const;
	bool equals(const char* str) const;
	int compareTo(String* other, bool caseSensetive = true) const;
	int compareTo(const char* str, bool caseSensetive = true) const;
	bool startsWith(const char* str, bool caseSensetive = true) const;
	bool endsWith(const char* str, bool caseSensetive = true) const;
	bool empty() const;
	char at(int index) const;

	String* operator+ (String* rhs) const;
	String* operator+ (const char* rhs) const;
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
