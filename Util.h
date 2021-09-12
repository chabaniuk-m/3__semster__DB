#ifndef UTIL
#define UTIL

#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <io.h>
#include <stdlib.h>

#include "Table.h"
#include "String.h"

const int EXISTS = 00;
const int WRITEABLE = 02;
const int READABLE = 04;
const int WRITEABLE_AND_READABLE = 06;


//char* toString(Table::LineList* lines);

void print(const char* str);

void println(const char* str);

//before calling this function print something like this:
// if you really want to do it type "yes":
bool userWantToDoIt();

//length of result is the same as length of str
char* ucopy(const char* str);

//length of result is the same as length (argument)
char* ucopy(const char* str, const int length);

//if dir exists adds "\\" if needed
bool existsDir(String* path);				//tested

//if file exists adds ".txt" if needed
bool existsFile(String * path);				//tested

//if file does not exist, creates it
FILE* uopenFile(String* path, const char* mode, int& err);

int ucreateDir(String* path);

typedef int error_t;
const int ERR_CORRECT = 0;
const int ERR_VALUE_OUT_OF_BOUNDS = 1;			//integer type but can not fit in 32 bits
const int ERR_IMPARSABLE = 2;

//ask user for input integer value before calling it
error_t readInt(int& a);					//tested

// "-0", "008" etc. - are incorrect
// error types: 
// - ERR_CORRECT - str can be correctly parse to int value
// - ERR_VALUE_OUT_OF_BOUNDS, ERR_IMPARSABLE - can not be parsed to int
error_t isInt(const char* str);				//tested

//str must be parseable to int
int parseInt(const char* str);				//tested

//is str a contains value parsable to long long type
error_t isLong(const char* str);

//str must be parsable to long long
long long parseLong(const char* str);

//ask user for input a long value
error_t readLong(long long& a);

//does not check out of bounds
error_t isDouble(const char* str);			//tested

//str must be parseable to double
double parseDouble(const char* str);		//tested

//ask user for input a double value before
error_t readDouble(double& a);				//tested

const char* toCString(int a);
const char* toCString(double a);
const char* toCString(long long a);

#endif // !UTIL
