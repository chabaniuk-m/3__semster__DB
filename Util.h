#ifndef UTIL
#define UTIL

#include <stdio.h>
#include <direct.h>
#include <sys/stat.h>
#include <io.h>
#include <stdlib.h>

#include "Table.h"
#include "String.h"

//returns null-terminated string from offset to the end of str
char* subStrFrom(char str[], const int length, int offset);
int findFirst(char text[], const int length, char target);
char* toString(Table::LineList* lines);
void print(const char* str);
void println(const char* str);

#endif // !UTIL
