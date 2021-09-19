#include "Util.h"
#include "Table.h"
#include "String.h"
#include "MainView.h"

#include <Windows.h>
#include <string>
#include <assert.h>

const char* defaultPath = "\\Users\\Admin\\Desktop\\database\\";
extern const int databaseIndex = 21;
extern const char* forbiddenSymbols = "<>:\"/\\|\?*";
const int EXISTS = 00;
const int WRITEABLE = 02;
const int READABLE = 04;
const int WRITEABLE_AND_READABLE = 06;
const int ERR_LOADING_TABLE = 100;
const int ERR_NOT_FOUND = 101;

void print(const char* str)
{
	printf("%s", str);
}

void println(const char* str)
{
	printf("%s\n", str);
}

bool userWantToDoIt()
{
	const int size = 10;
	char* reply = new char[size + 1]();
	gets_s(reply, size);
	String* answer = new String(reply);

	if (answer->compareTo("yes", false) == String::EQUALS)
	{
		delete[] reply;
		delete answer;
		return true;
	}
	else
	{
		delete[] reply;
		delete answer;
		return false;
	}
}

const String* currentDirectory()
{
	return MainView::getObj()->getCurrDirectory();
}

char* ucopy(const char* str)
{
	int length = 0;
	for (; str[length] != '\0'; ++length);

	return ucopy(str, length);
}

char* ucopy(const char* str, const int length)
{
	char* result = new char[length + 1]();

	for (int i = 0; i < length; i++)
	{
		result[i] = str[i];
	}

	return result;
}

bool existsDir(String* path)
{
	if (path == nullptr) return false;

	if (!path->endsWith("\\"))
	{
		path->append("\\");
	}

	if (_access_s(path->getData(), EXISTS) == 0)
	{
		return true;
	}

	return false;
}

//full path like
// "\\Users\\Admin\\Desktop\\database\\test.txt"
// maybe without .txt;
bool existsFile(String * path)
{
	if (path == nullptr) return false;
	
	if (!path->contains('.'))
	{
		path->append(".txt");
	}

	if (_access_s(path->getData(), EXISTS) == 0)
	{
		return true;
	}
		
	return false;
}

bool correctFilePath(const String* path, bool onlyName)
{
	if (path == nullptr) return false;

	const String* name = onlyName ? path : getFileName(path);

	for (int i = 0; forbiddenSymbols[i] != '\0'; ++i)
	{
		if (name->contains(forbiddenSymbols[i]))
		{
			return false;
		}
	}

	if (name->count('.') > 1)
	{
		if (!onlyName) delete name;

		return false;
	}

	int index = name->lastIndexOf('.');

	if (index == String::NPOS)
	{
		if (!onlyName) delete name;

		return true;
	}
	else if (index == 0)
	{
		if (!onlyName) delete name;

		return false;
	}

	bool extentionAbsent = true;

	for (int i = index + 1; i < name->getLength(); ++i)
	{
		extentionAbsent = false;

		if (!isalpha(name->at(i)))
		{
			if (!onlyName) delete name;

			return false;
		}
	}

	if (extentionAbsent)
	{
		if (!onlyName) delete name;

		return false;
	}

	if (!onlyName) delete name;

	return true;
}

FILE* uopenFile(const String* path, const char* mode, int& err)
{
	FILE* fp;
	err = fopen_s(&fp, path->getData(), mode);

	return fp;
}

int ucreateDir(const String* path)
{
	return _mkdir(path->getData());
}

void showFileNameForbiddens()
{
	println("- empty name");
	println(" - more than 1 symbol \'.\'");
	println(" - after '.' symbol except letters");
	println(" - after '.' no symbols");
	println(" - the following symbols:   ");

	for (int i = 0; forbiddenSymbols[i] != '\0'; ++i)
	{
		printf("%c ", forbiddenSymbols[i]);
	}

	println("");
}

String* getParentDirectory(String* path)
{
	int index = path->getLength() - 2;

	for (; (*path)[index] != '\\';) --index;

	return path->substr(0, index + 1);
}

error_t readInt(int& a)
{
	const int size = 32;
	char* buff = new char[size]();
	gets_s(buff, size);
	int err = isInt(buff);

	if (err)
	{
		delete[] buff;

		return err;
	}
	else
	{
		a = parseInt(buff);
		delete[] buff;

		return err;
	}
}

String* getFileName(const String* path)
{
	if (!path->contains('\\')) return path->copy();

	int i = path->getLength() - 2;

	for (; path->at(i) != '\\'; --i);

	return path->substr(i + 1);
}

error_t isInt(const char* str)
{
	int len = 0;
	bool negative = false;
	if (str[len] == '\0')
	{
		return ERR_IMPARSABLE;
	}
	else if (str[len] == '-')
	{
		++len;
		negative = true;
		if (str[len] == '0')
		{
			return ERR_IMPARSABLE;
		}
	}
	else if (str[len] == '0')
	{
		++len;
		if (str[len] != '\0')
		{
			return ERR_IMPARSABLE;
		}
	}

	char c;
	bool begin = true;

	for (; (c = str[len]) != '\0'; ++len)
	{
		if (begin && str[len] == '0')
		{
			//repeated zero or after '-'
			return ERR_IMPARSABLE;
		}
		else
		{
			if (!('0' <= c && c <= '9'))
			{
				return ERR_IMPARSABLE;
			}
		}

		begin = false;
	}

	if (len > 11)
	{
		return ERR_VALUE_OUT_OF_BOUNDS;
	}
	else if (len == 11)
	{
		if (negative)
		{
			String* intMin = new String("-2147483648");
			if (intMin->compareTo(str) < 0)
			{
				return ERR_VALUE_OUT_OF_BOUNDS;
			}
		}
		else
		{
			return ERR_VALUE_OUT_OF_BOUNDS;
		}
	}
	else if (len == 10)
	{
		String* intMax = new String("2147483647");
		if (intMax->compareTo(str) < 0)
		{
			return ERR_VALUE_OUT_OF_BOUNDS;
		}
	}
	
	return ERR_CORRECT;
}

int parseInt(const char* str)
{
	char c;
	int res = 0;
	int i = 0;
	bool negative = false;
	if (str[i] == '-')
	{
		++i;
		negative = 1;
	}


	for (; (c = str[i]) != '\0'; ++i)
	{
		res *= 10;
		res += (c - '0');
	}

	return negative ? -res : res;
}

error_t isLong(const char* str)
{
	int len = 0;
	bool negative = false;
	if (str[len] == '\0')
	{
		return ERR_IMPARSABLE;
	}
	else if (str[len] == '-')
	{
		++len;
		negative = true;
		if (str[len] == '0')
		{
			return ERR_IMPARSABLE;
		}
	}
	else if (str[len] == '0')
	{
		++len;
		if (str[len] != '\0')
		{
			return ERR_IMPARSABLE;
		}
	}

	char c;
	bool begin = true;

	for (; (c = str[len]) != '\0'; ++len)
	{
		if (begin && str[len] == '0')
		{
			//repeated zero or after '-'
			return ERR_IMPARSABLE;
		}
		else
		{
			if (!('0' <= c && c <= '9'))
			{
				return ERR_IMPARSABLE;
			}
		}

		begin = false;
	}

	if (len > 20)
	{
		return ERR_VALUE_OUT_OF_BOUNDS;
	}
	else if (len == 20)
	{
		if (negative)
		{
			String* intMin = new String("-9223372036854775808");
			if (intMin->compareTo(str) < 0)
			{
				return ERR_VALUE_OUT_OF_BOUNDS;
			}
		}
		else
		{
			return ERR_VALUE_OUT_OF_BOUNDS;
		}
	}
	else if (len == 19)
	{
		String* intMax = new String("9223372036854775807");
		if (intMax->compareTo(str) < 0)
		{
			return ERR_VALUE_OUT_OF_BOUNDS;
		}
	}

	return ERR_CORRECT;
}

long long parseLong(const char* str)
{
	char c;
	long long res = 0;
	int i = 0;
	bool negative = false;
	if (str[i] == '-')
	{
		++i;
		negative = true;
	}


	for (; (c = str[i]) != '\0'; ++i)
	{
		res *= 10;
		res += (c - '0');
	}

	return negative ? -res : res;
}

error_t readLong(long long& a)
{
	const int size = 64;
	char* buff = new char[size]();
	gets_s(buff, size);
	int err = isLong(buff);

	if (err)
	{
		delete[] buff;

		return err;
	}
	else
	{
		a = parseLong(buff);
		delete[] buff;

		return err;
	}
}

error_t isDouble(const char* str)
{
	if (str[0] == '\0') return ERR_IMPARSABLE;

	bool wasDot = false;
	bool negative = false;
	int len = 0;

	//checking for correct '-' and exclude -07.8, 008.3248 etc.
	if (str[0] == '-')
	{
		if (str[1] == '0')
		{
			if (str[2] == '.')
			{
				len = 3;
				goto cycle;
			}
			else
			{
				return ERR_IMPARSABLE;
			}
		}
		else if (str[1] == '.')
		{
			return ERR_IMPARSABLE;
		}
		++len;
		negative = true;
	}
	else if (str[0] == '0')
	{
		if (str[1] == '\0')
		{
			return ERR_CORRECT;
		}
		if (str[1] != '.')
		{
			return ERR_IMPARSABLE;
		}
		++len;
	}
	else if (str[0] == '.')
	{
		wasDot = true;
		++len;
	}

cycle:
	char c;
	for (; (c = str[len]) != '\0'; ++len)
	{
		if (wasDot)
		{
			if (!('0' <= c && c <= '9'))
			{
				return ERR_IMPARSABLE;
			}
		}
		else
		{
			if (c == '.')
			{
				wasDot = true;
			}
			else if (!('0' <= c && c <= '9'))
			{
				return ERR_IMPARSABLE;
			}
		}
	}

	return ERR_CORRECT;
}

double parseDouble(const char* str)
{
	double integerPart = 0;
	double fractionalPart = 0;
	bool negative = false;
	int i = 0;
	if (str[i] == '-')
	{
		negative = true;
		++i;
	}

	for (; str[i] != '\0' && str[i] != '.'; ++i)
	{
		integerPart *= 10;
		integerPart += double(str[i] - '0');
	}

	int end = i;				//index of '.'
	int len = i;

	while (str[len] != '\0') ++len;

	for (i = len - 1; i > end; --i)
	{
		fractionalPart /= 10;
		fractionalPart += double(str[i] - '0') / 10;
	}

	double res = integerPart + fractionalPart;

	return negative ? -res : res;
}

error_t readDouble(double& a)
{
	const int size = 256;
	char* buff = new char[size]();
	gets_s(buff, size);

	int err = isDouble(buff);
	if (err)
	{
		delete[] buff;

		return err;
	}
	else
	{
		a = parseDouble(buff);
		delete[] buff;

		return err;
	}
}

const char* readString(int len)
{
	char* buff = new char[len + 1]();
	assert(gets_s(buff, len + 1) && "Problem reading the line of text");

	return buff;
}

const char* toCString(int a)
{
	return ucopy(std::to_string(a).c_str());
}

const char* toCString(double a)
{
	return ucopy(std::to_string(a).c_str());
}

const char* toCString(long long a)
{
	return ucopy(std::to_string(a).c_str());
}

const char* toCString(char c)
{
	return new char[2]{ c, '\0' };
}

#include <filesystem>
void printFolderContent(const String* fpath)
{
	bool empty = true;
	for (const auto& entry : std::filesystem::directory_iterator(fpath->getData()))
	{
		std::string str = entry.path().string();

		int end = str.length();
		int beg = end - 1;
		for (; str[beg] != '\\'; --beg) {}

		//std::cout << str.substr(beg + 1, end) << std::endl;
		println(str.substr(beg + 1, end).c_str());

		empty = false;
	}

	if (empty) println("<empty>");
}