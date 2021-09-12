#include "String.h"
#include "Util.h"

String::String() :
	String(32) {}

String::String(const char* str)
{
	int counter = 0;
	for (; str[counter] != '\0'; ++counter);

	length = counter;
	text = new char[length + 1]();
	for (int i = 0; i < length; i++)
	{
		text[i] = str[i];
	}
}

String::String(const String const* other) :
	String(other->text) {}

String::~String()
{
	delete[length + 1] text;
}

String* String::copy() const
{
	String* result = new String(0);
	delete[1] result->text;

	result->text = ucopy(this->text, length);
	result->length = length;

	return result;
}

String* String::substr(int offset, int to) const
{
	if (offset < 0)
		offset = 0;

	if (to > length)
		to = length;

	String* result = new String(to - offset);

	for (int i = offset; i < to; ++i)
		result->text[i - offset] = text[i];

	result->length = to - offset;

	return result;
}

String** String::split(int& len, char delim) const
{
	int numberOfDelimiters = 0;
	int lastOffset = 0;
	for (int i = 0; i < length; i++)
	{
		if (text[i] == delim)
		{
			lastOffset = i;
			++numberOfDelimiters;
		}
	}

	String** parts = new String*[len = numberOfDelimiters + 1];

	int offset = 0;
	int end = length;
	int i = 0;			//index of string in parts

	do
	{
		for (int j = offset + 1; j < length; j++)
		{
			if (text[j] == delim)
			{
				end = j;
				break;
			}
		}

		parts[i++] = substr(offset, end);

		offset = end + 1;
		end = length;
	} 
	while (offset < length);

	return parts;
}

int String::lastIndexOf(char c) const
{
	for (int i = length - 1; i >= 0; i--)
	{
		if (text[i] == c) return i;
	}

	return NPOS;
}

char* String::getData() const { return ucopy(text); }

String* String::append(const char* other)
{
	if (other == nullptr || other[0] == '\0') return this;

	int len = 0;
	for (; other[len] != '\0'; ++len);

	append(other, len);

	return this;
}

String* String::append(const String const* other)
{
	if (other == nullptr) return this;

	append(other->text, other->length);

	return this;
}

bool String::equals(String* other) const
{
	if (length != other->length)
		return false;

	return equals(text, other->text);
}

bool String::equals(const char* str) const
{
	return equals(text, str);
}

int String::compareTo(String* other, bool caseSensetive) const
{
	if (other == nullptr)
		return 1;

	return compareTo(other->text, caseSensetive);
}

int String::compareTo(const char* str, bool caseSensetive) const
{
	if (caseSensetive)
	{
		int i = 0;
		for (; text[i] != '\0'; ++i)
		{
			if (str[i] == '\0') return GREATER;

			if (text[i] != str[i])
				return text[i] - str[i];
		}
		if (str[i] != '\0') return LESS;

		return EQUALS;
	}
	else
	{
		int i = 0;
		for (; text[i] != '\0'; ++i)
		{
			if (str[i] == '\0') return GREATER;

			char a = (isUpperLetter(text[i])) ? toLower(text[i]) : text[i];
			char b = (isUpperLetter(str[i])) ? toLower(str[i]) : str[i];

			if (a != b) return a - b;
		}
		if (str[i] != '\0') return LESS;

		return EQUALS;
	}
}

bool String::startsWith(const char* str, bool caseSensetive) const
{
	if (str == nullptr) return true;

	int i = 0;
	for (; i < length; ++i)	
	{
		if (str[i] == '\0') return true;

		char a = text[i];
		char b = str[i];

		if (!caseSensetive && isUpperLetter(a)) a = toLower(a);
		if (!caseSensetive && isUpperLetter(b)) b = toLower(b);

		if (a != b)
		{
			return false;
		}
	}
	
	if (str[i] != '\0') return false;
	
	return true;
}

bool String::endsWith(const char* str, bool caseSensetive) const
{
	int len = 0;
	for (; str[len] != '\0'; ++len);

	if (length < len) return false;

	for (int i = len - 1, j = length - 1; i >= 0; --i, --j)
	{
		char a = str[i];
		char b = text[j];
		
		if (!caseSensetive)
		{
			if (isUpperLetter(a)) a = toLower(a);
			if (isUpperLetter(b)) b = toLower(b);
		}

		if (a != b) return false;
	}

	return true;
}

bool String::empty() const
{
	return length == 0;
}

char String::at(int index) const { return this->operator[](index); }

String* String::operator+(String* rhs) const
{
	const int len = length + rhs->length;
	String* result = new String(len);
	result->length = len;

	int i = 0;
	for (; i < length; i++)
	{
		result->text[i] = text[i];
	}
	for (int j = 0; j < rhs->length; ++j, ++i)
	{
		result->text[i] = rhs->text[j];
	}

	return result;
}

String* String::operator+(const char* rhs) const
{
	String* temp = new String(rhs);
	String* res = *this + temp;
	delete temp;

	return res;
}

char String::operator[](int index) const
{
	if (!checkBounds(index))
		return '\0';

	return text[index];
}

char& String::operator[](int index)
{
	if (!checkBounds(index))
	{
		char empty = *new char('\0');
		return empty;
	}

	return text[index];
}

void String::print() const
{
	for (int i = 0; i < length; i++)
	{
		putchar(text[i]);
	}
}

void String::println() const
{
	print();
	putchar('\n');
}

String::String(int length)
{
	text = new char[length + 1]();
	this->length = 0;
}

bool String::checkBounds(int index) const
{
	if (index < 0 || index >= length)
		return false;

	return true;
}

bool String::equals(const char* s1, const char* s2) const
{
	int l1 = 0;
	for (; s1[l1] != '\0'; ++l1);
	int l2 = 0;
	for (; s2[l2] != '\0'; ++l2);

	if (l1 != l2) return false;

	for (int i = 0; i < l1; ++i)
		if (s1[i] != s2[i])
			return false;

	return true;
}

bool String::isUpperLetter(char c) const
{
	return 'A' <= c && c <= 'Z';
}

char String::toLower(char upperLetter) const
{
	return char(upperLetter + 'a' - 'A');
}

void String::append(const char* other, const int len)
{
	int newLength = length + len;
	char* result = new char[newLength + 1]();
	int i = 0;

	for (; i < length; ++i)
		result[i] = text[i];
	for (int j = 0; i < newLength; ++i, ++j)
		result[i] = other[j];

	delete[length] text;
	text = result;
	length = newLength;
}
