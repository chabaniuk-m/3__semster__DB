
#ifndef UTIL
#define UTIL

#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <io.h>
#include <stdlib.h>
class String;
class Table;

extern const char* defaultPath;
extern const int databaseIndex;					//for mainView
extern const char* forbiddenSymbols;
extern const int EXISTS;
extern const int WRITEABLE;
extern const int READABLE;
extern const int WRITEABLE_AND_READABLE;
extern const int ERR_LOADING_TABLE;
extern const int ERR_NOT_FOUND;


//char* toString(Table::LineList* lines);

void print(const char* str);

void println(const char* str);

//before calling this function print something like this:
// if you really want to do it m_type "yes":
bool userWantToDoIt();

//return directory (const ref) used by mainView right now
const String* currentDirectory();

//length of result is the same as length of str
char* ucopy(const char* str);

//length of result is the same as length (argument)
char* ucopy(const char* str, const int length);

//always adds "\\" if needed
bool existsDir(String* path);				//tested

//always adds extension if needed
bool existsFile(String * path);				//tested

//count('.') <= 1, does not contain forbidden symbols, after '.' must be only letters
bool correctFilePath(const String* path, bool onlyName = false);

void showFileNameForbiddens();

//returns file or folder name
String* getFileName(const String* path);

String* getParentDirectory(String* path);

//if file does not exist, creates it
FILE* uopenFile(const String* path, const char* mode, int& err);

int ucreateDir(const String* path);

typedef int error_t;
const int ERR_CORRECT = 0;
const int ERR_VALUE_OUT_OF_BOUNDS = 1;			//integer m_type but can not fit in 32 bits
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

//is str a contains value parsable to long long m_type
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

const char* readString(int bufferLength = 255);

const char* toCString(int a);
const char* toCString(double a);
const char* toCString(long long a);
const char* toCString(char c);

//path must exist
void printFolderContent(const String* path);

#endif // !UTIL
