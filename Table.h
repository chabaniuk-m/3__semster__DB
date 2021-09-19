#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

//represents one file in database
class String;
class Stack;
template <class T>
class ArrayList;

class Table
{
	class Line;
	class Field;
	class LineList;

public:
	static const int ERR_CORRECT;					//0, everything is correct
	static const int ERR_INCORRECT_FIELD_TYPE;		//only chars 'i', 'l', 'd', 'c', 's'
	static const int ERR_INVALID_FIELD_NAME;		//must contains only letter and '_' (but don't start) and does not be empty
	static const int ERR_FIELD_NAME_REPEATING;		//field name is already present in Table::fields
	static const int ERR_KEY_ABSENT;
	static const int ERR_KEY_PRESENT;
	static const int ERR_NAME_PRESENT;
	static const int ERR_NAME_ABSENT;

	Table(const String* path, int& err, const char* mode = "r+", bool newTable = false);
	
	//close FILE*, removes file and clear memory
	~Table();

	//true is table was saved correctly
	bool save();

	//reads the data from the table
	bool load();

	/*
	* return error type: CORRECT || INCORRECT_TYPE
	* || INVALID_NAME || NAME_IS_PRESENT
	*/
	int addField(const char* name, char type, bool correctType = false);

	//returns error type: CORRECT || NAME_ABSENT
	int removeField(const char* name);

	//return error type: CORRECT, NAME_ABSENT, KEY_PRESENT
	int setKeyField(const char* name);

	void removeKeyField();

	//return error type (KEY_ABSENT || CORRECT)
	int done();

	//prints fields' names and types
	void showFields() const;

	void simulateDeletion();

	int simulateRestore();

	int deleteFile();

	const char* getPath() const;

	static bool correctFieldType(char c);

	static bool correctFieldName(const char* name);

	bool containsField(const char* name);

	//delete all lines
	void clear();

	bool empty() const;

	bool emptyLine() const;

private:
	char* fpath;						//dynamic
	const char* fmode;
	ArrayList<Field*>* fields;				//dynamic & can be immutable
	FILE* fp;
	LineList* lines;					//dynamic

	class Line
	{
		String** notes;

	public:

		char* getNote(int noteNumber);
		void setNote(int noteNumber, char newNote[]);
		int compareToByNote(Line other, int noteNumber);
		char* toString();
	};

	class Field
	{
		bool keyField;				//if the field is key (*) in each table must be only one key field

	public:

		const char* name;
		const char type;				//i - int, l - long long, d - double, s - string, c - char

		Field();
		Field(const char* aName, char aType);
		~Field() {}						//delete nothing

		void makeKeyField();

		void unmakeKeyField();

		bool isKeyField() const;

		String* toString(bool saving = true) const;
		
		const char* getTypeStr() const;
	};
	class LineList
	{

	};

};

#endif	// !TABLE_H
