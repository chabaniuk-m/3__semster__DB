#include "Table.h"
#include "String.h"
#include "ArrayList.h"
#include "Util.h"
#include <ctype.h>

const int Table::ERR_CORRECT = 0;
const int Table::ERR_INCORRECT_FIELD_TYPE = 300;
const int Table::ERR_INVALID_FIELD_NAME = 301;
const int Table::ERR_FIELD_NAME_REPEATING = 302;
const int Table::ERR_KEY_ABSENT = 303;
const int Table::ERR_KEY_PRESENT = 304;
const int Table::ERR_NAME_ABSENT = 305;
const int Table::ERR_NAME_PRESENT = 306;

Table::Table(const String* path, int& err, const char* mode, bool newTable)
	: fpath(path->getData()), fmode(mode)
{
	fp = uopenFile(path, mode, err);

	if (!newTable && fp)
	{
		if (!this->load())
		{
			err = ERR_LOADING_TABLE;
		}
	}

	lines = new LineList();
	fields = new ArrayList<Field*>();
}

Table::~Table()
{
	fclose(fp);
	remove(fpath);

	delete fpath;
	delete fields;
	delete lines;
}

bool Table::save()
{
	//test
	print("Table::save by path ");
	println(fpath);

	bool savedCorrectly = true;

	//TODO

	return savedCorrectly;
}

bool Table::load()
{
	//test
	print("Table::load by path ");
	println(fpath);

	bool loadedCorrectly = true;

	//TODO

	return loadedCorrectly;
}

int Table::addField(const char* name, char type, bool correctType)
{
	if (!correctType && !correctFieldType(type)) return Table::ERR_INCORRECT_FIELD_TYPE;
	if (!correctFieldName(name)) return Table::ERR_INVALID_FIELD_NAME;
	if (containsField(name)) return Table::ERR_FIELD_NAME_REPEATING;
	
	fields->add(new Field(name, type));

	return Table::ERR_CORRECT;
}

void Table::removeKeyField()
{
	for (int i = 0; i < fields->size(); ++i)
	{
		if (fields->get(i)->isKeyField())
		{
			fields->get(i)->unmakeKeyField();
			break;
		}
	}
}

void Table::simulateDeletion()
{
	fclose(fp);
}

int Table::simulateRestore()
{
	return fopen_s(&fp, fpath, "w");
}

int Table::deleteFile()
{
	fclose(fp);
	return remove(fpath);
}

const char* Table::getPath() const
{
	return fpath;
}

int Table::setKeyField(const char* name)
{
	Field* targerField = nullptr;

	for (int i = 0; i < fields->size(); i++)
	{
		Field* field = fields->get(i);

		if (field->isKeyField())
		{
			return Table::ERR_KEY_PRESENT;
		}
		else if (String::equals(name, field->name))
		{
			targerField = field;
		}
	}

	if (targerField == nullptr) return Table::ERR_NAME_ABSENT;

	targerField->makeKeyField();

	return Table::ERR_CORRECT;
}

int Table::removeField(const char* name)
{
	for (int i = 0; i < fields->size(); ++i)
	{
		Field* field = fields->get(i);

		if (String::equals(field->name, name))
		{
			delete fields->remove(i);

			return Table::ERR_CORRECT;
		}
	}

	return Table::ERR_NAME_ABSENT;
}

void Table::showFields() const
{
	if (fields == nullptr || fields->empty())
	{
		println("<empty>");
	}
	else
	{
		String* field = fields->get(0)->toString(false);
		field->print();

		for (int i = 1; i < fields->size(); ++i)
		{
			delete field;
			print(" | ");
			field = fields->get(i)->toString(false);
			field->print();
		}

		println("");
		delete field;
	}
}

int Table::done()
{
	for (int i = 0; i < fields->size(); i++)
	{
		if (fields->get(i)->isKeyField())
		{
			fields->makeImmutable();
			return Table::ERR_CORRECT;
		}
	}

	return Table::ERR_KEY_ABSENT;
}

bool Table::containsField(const char* name)
{
	if (name == nullptr || fields == nullptr) return false;

	for (int i = 0; i < fields->size(); i++)
	{
		if (String::equals(fields->get(i)->name, name))
		{
			return true;
		}
	}

	return false;
}

bool Table::empty() const
{
	return fields ? fields->empty() : true;
}

bool Table::correctFieldType(char c)
{
	return c == 'i' || c == 'l' || c == 'd' || c == 'c' || c == 's';
}

bool Table::correctFieldName(const char* name)
{
	if (name == nullptr || name[0] == '\0' || !isalpha(name[0])) return false;

	for (int i = 1; name[i] != '\0'; ++i)
	{
		if (!isalpha(name[i]) && name[i] != '_')
		{
			return false;
		}
	}

	return true;
}

Table::Field::Field()
	: name(""), type('i'), keyField(false) {}

Table::Field::Field(const char* aName, char aType)
	: name(aName), type(aType), keyField(false) {}

void Table::Field::makeKeyField()
{
	keyField = true;
}

bool Table::Field::isKeyField() const
{
	return keyField;
}

String* Table::Field::toString(bool saving) const
{
	String* str = saving ? new String(toCString(type)) : (new String(getTypeStr()))->append(" ");

	str->append(name);

	return keyField ? str->append("*") : str;
}

void Table::Field::unmakeKeyField()
{
	keyField = false;
}

const char* Table::Field::getTypeStr() const
{
	switch (type)
	{
	case 'i': return "int";
	case 'l': return "long";
	case 'd': return "double";
	case 'c': return "char";
	case 's': return "string";
	default:  return "error: unknown field type";
	}
}
