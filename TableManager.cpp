#include "TableManager.h"
#include "TableList.h"
#include "Util.h"
#include "String.h"
#include <assert.h>

TableManager* TableManager::obj = nullptr;

int TableManager::removeTable(const String* path)
{
	TableList::Node* table = list->open(path);
	table->removeTable();

	int err = 0;
	err = remove(path->getData());

	return err;
}

void TableManager::removeAllTablesInFolder(const String* path)
{
	list->removeAllTablesInFolder(path);
	added->removeAllTablesInFolder(path);
}

Table* TableManager::restoreTable(const String* path)
{
	//test
	print("TableManager::restoreTable: path - ");
	path->println();

	TableList::Node* table = list->get(path);

	if (table == nullptr)
	{
		return nullptr;
	}

	return table->restoreTable();
}

Table* TableManager::createTable(const String * path, const char* mode)
{
	//test
	print("TableManager::createTable: path - ");
	path->print();
	print(", mode - ");
	println(mode);

	int err = 0;

	Table* table = new Table(path, err, mode, true);

	if (!err)
	{
		list->add(table);

		return table;
	}
	else
	{
		delete table;

		return nullptr;
	}
}

void TableManager::deleteTable(Table* table)
{
	assert(table != nullptr);

	//list call table's destructor, which does all important stuff
	list->remove(table);
}

bool TableManager::addField(Table* table, const char* name, const char* t)
{
	assert(table != nullptr);

	char type;

	if (String::equals(t, "int")) type = 'i';
	else if (String::equals(t, "long")) type = 'l';
	else if (String::equals(t, "double")) type = 'd';
	else if (String::equals(t, "char")) type = 'c';
	else if (String::equals(t, "string")) type = 's';
	else
	{
		print("The type \"");
		print(t);
		println("\" is incorrect or not allowed.");
		println("Try one of the following types:");
		println(" - int;");
		println(" - long;");
		println(" - double;");
		println(" - char;");
		println(" - string;");

		return false;
	}

	int err = table->addField(name, type, true);

	if (err)
	{
		if (err == Table::ERR_INVALID_FIELD_NAME)
		{
			println("You have entered and incorrect field name.");
			println("Here are requirement for fields' names:");
			println(" - must begin with a letter;");
			println(" - can contain only letters and symbols \'_\'");
		}
		else if (err == Table::ERR_NAME_PRESENT)
		{
			println("Table cannot contains fields with the same names");
		}
		else
		{
			println("ERROR: unknown error has been obtained from Table::addField in TableManager::addField");
		}

		return false;
	}
	else
	{
		println("The field was successfully added");

		return true;
	}
}

bool TableManager::removeField(Table* table, const char* name)
{
	assert(table != nullptr);

	int err = table->removeField(name);

	if (err)					//name is absent
	{
		print("The field with name \"");
		print(name);
		println("\" is absent in the table");

		return false;
	}
	else if (err == Table::ERR_CORRECT)
	{
		println("The field was successfully removed");

		return true;
	}
	else
	{
		println("ERROR: unknown error has been obtained from Table::removeField in TableManager::removeField");

		return false;
	}
}

bool TableManager::setKeyField(Table* table, const char* name)
{
	assert(table != nullptr);

	int err = table->setKeyField(name);

	if (err)
	{
		if (err == Table::ERR_NAME_ABSENT)
		{
			print("The is no field \"");
			print(name);
			println("\" in the table");
		}
		else if (err == Table::ERR_KEY_PRESENT)
		{
			println("The key field is already present in the table");
		}
		else
		{
			println("ERROR: unknown error has been obtained from Table::addField in TableManager::addField");
		}

		return false;
	}
	else
	{
		print("Field \"");
		print(name);
		println("\" is now a key field");

		return true;
	}
}

void TableManager::removeKeyField(Table* table)
{
	assert(table);

	table->removeKeyField();
}

void TableManager::showFields(Table* table) const
{
	assert(table != nullptr);

	table->showFields();
}

bool TableManager::done(Table* table)
{
	assert(table != nullptr);

	int err = table->done();

	if (err)				//key absent
	{
		println("Table must contains key field,");
		println("thus tables without field is not allowed");

		return false;
	}
	else
	{
		println("The table was successfully created!");
		println("Now you can start adding notes and dependencies");

		return true;
	}
}

Table* TableManager::openTable(const String* path)
{
	assert(list);

	TableList::Node* node = list->open(path);

	if (node == nullptr || node->isDeleted())
	{
		return nullptr;
	}
	else
	{
		return node->table;
	}
}

bool TableManager::knowsTable(const String* path) const
{
	return list->contains(path) || added->contains(path);
}

bool TableManager::tablesListEmpty() const
{
	return list->empty();
}

TableManager::TableManager()
{
	list = new TableList();
	added = new TableList();
}
