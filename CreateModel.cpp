#include "CreateModel.h"
#include "CreateView.h"
#include "MainView.h"
#include "TableManager.h"
#include "TableModel.h"
#include "Util.h"
#include "Table.h"
#include "String.h"
#include <cassert>

CreateModel* CreateModel::obj = nullptr;

CreateModel::CreateModel()
	: table(nullptr),
	createView(CreateView::getObj()),
	manager(TableManager::getObj())
{
	//mainView = MainView::getObj();			- stack over flow
}

void CreateModel::createTable(const String* name)
{
	//TODO:
	// - checks if this file does not exist in the current directory
	// - call _createTable();

	//test
	printf("CreateModel::createTable: arg - %s\n", name->getData());

	String* path = *currentDirectory() + name->getData();

	if (existsFile(path))
	{
		String* file = new String(name->getData());
		if (!file->contains('.'))
		{
			file->append(".txt");
		}
		printf("File %s is already exists\n", file->getData());

		delete file;
		delete path;
	}
	else
	{
		//test
		print("Creating the table ");
		name->println();

		if (correctFilePath(name, true))
		{
			if (manager->knowsTable(path))			//table was deleted
			{
				println("You can not create a table with the same name as recently ");
				print("deleted table while it does not deleted permanently.\n But you can restore table ");
				String* fileName = getFileName(path);
				fileName->print();
				delete fileName;
				println(" and then clear it instead");
			}
			else
			{
				_createTable(path);
			}
		}
		else
		{
			println("You have entered an incorrect table name.");
			println("Forbiddens for table names:");
			showFileNameForbiddens();

			delete path;
		}
	}

	delete name;
}

void CreateModel::createFolder(const String* name)
{
	//TODO:
	// - check if the folder does not exist int the current directory
	// - call _createFolder();

	//test
	print("CreateModel::createFolder: arg - ");
	name->println();

	String* path = *currentDirectory() + name;

	if (existsDir(path))
	{
		print("Folder ");
		name->print();
		println(" is already exists in the currect directory");
	}
	else
	{
		_createFoler(path);
	}

	delete path;
}

void CreateModel::moveTable(const String* name)
{
	//test
	print("CreateModel::moveTable: arg - ");
	name->println();

	String* path = *currentDirectory() + name;

	if (!existsFile(path))
	{
		print("Table ");
		name->print();
		println(" does not exist in the current directory");

		delete name;
	}
	else
	{
		//test
		println("Moving the table");

		//TODO
		// - interact with TableView to move the file to another directory
		// pass name but don't delete
	}

	delete path;
}

void CreateModel::askForCommand()
{
	println("The command was not recognized!");
	println("Try the following commands:");
	createView->showCorrectCommands();
	createView->askForCommand();
}

void CreateModel::setViewController(class Controller* c)
{
	createView->setController(c);
}

void CreateModel::deleteCurrentTable()
{
	//test
	println("CreateModel::deleteCurrentTable");

	manager->deleteTable(table);
	table = nullptr;

	println("The table was successfully deleted");
	createView->end();
}

void CreateModel::addField()
{
	int len;
	const char* str;
	String* nameAndType;
	String** arr;

askForNameAndType:

	print("Enter field name and type: ");
	str = readString(63);
	nameAndType = new String(str);
	arr = nameAndType->split(len, ' ');

	if (arr[0]->equals("cancel")) return;

	if (len != 2)
	{
		for (int i = 0; i < len; i++)
		{
			delete arr[i];
		}

		println("Your input is incorrect. Try like in");
		println("example: \"user_name string\"");

		goto askForNameAndType;
	}

	while (!manager->addField(table, arr[0]->getData(), arr[1]->getData()))
	{
		delete str;
		delete nameAndType;
		delete arr[0];	
		delete arr[1];

		goto askForNameAndType;
	}

	delete str;
	delete nameAndType;
	delete arr[0];
	delete arr[1];
}

void CreateModel::removeField()
{
	assert(table);

	if (table->empty())
	{
		println("The table is empty");

		return;
	}

	const char* name = nullptr;

	do
	{
		delete name;

		print("Enter field name to remove: ");
		name = readString();

		if (String::equals(name, "cancel")) break;
	}
	while (!manager->removeField(table, name));

	delete name;
}

void CreateModel::setKeyField()
{
	assert(table);

	if (table->empty())
	{
		println("To set key field table must contains at least one field");
	}

	const char* name = nullptr;

	do
	{
		delete name;

		print("Enter field name: ");
		name = readString(63);

		if (String::equals(name, "cancel")) break;
	}
	while (!manager->setKeyField(table, name));

	delete name;
}

void CreateModel::resetKeyField()
{
	manager->removeKeyField(table);

	setKeyField();
}

void CreateModel::show()
{
	manager->showFields(table);
}

void CreateModel::done()
{
	print("Do you really want to finish creating the table? You won't be able\nto edit its' fields. Are you sure? ");

	if (userWantToDoIt())
	{
		if (manager->done(table))
		{
			createView->end();
			TableModel::getObj()->openTable(table);
			table = nullptr;
		}
	}
}

void CreateModel::_createTable(const String * path)
{
	//test
	print("CreateModel::_createTable: path - ");
	path->println();

	table = manager->createTable(path);

	if (table)
	{
		//test
		print("We are ready to create the table by path ");
		println(table->getPath());

		String* out = new String("Creating: ");

		createView->outputPath = out->append(path->substr(path->indexOf("database")));
		createView->begin();
	}
	else
	{
		println("There was an unknown problem when creating a table");
	}

	delete path;
}

void CreateModel::_createFoler(const String * path)
{
	//test
	print("CreateModel::_createFoler: arg - ");
	path->println();

	int err = ucreateDir(path);
	if (err)
	{
		println("Problem creating folder");
	}
	else
	{
		println("Folder was successfully created");
	}
}
