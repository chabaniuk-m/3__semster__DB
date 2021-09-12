#include "CreateModel.h"

void CreateModel::createTable(String* name)
{
	//TODO:
	// - checks if this file does not exist in the current directory
	// - call _createTable();

	//test
	printf("CreateModel::createTable: arg - %s", name->getData());

	String* path = *mainView->getCurrDirectory() + name->getData();

	if (existsFile(path))
	{
		printf("File %s is already exists\n", (*name + ".txt")->getData());
	}
	else
	{
		//test
		print("Creating the table ");
		name->println();

		_createTable(path);
	}

	delete name;
}

void CreateModel::createFolder(String* name)
{
	//TODO:
	// - check if the folder does not exist int the current directory
	// - call _createFolder();

	//test
	print("CreateModel::createFolder: arg - ");
	name->println();

	String* path = *mainView->getCurrDirectory() + name;

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

void CreateModel::moveTable(String* name)
{
	print("CreateModel::moveTable: arg - ");
	name->println();
}

void CreateModel::_createTable(String* path)
{
	//TODO
	// - create the file currentDirectory + name + ".txt";
	// - ask for fields types;
	// - write fields types;
	// - save table in TableList;
	// - ask for adding some notes;
	// - continue working with the current table;

	//test
	print("CreateModel::_createTable: arg - ");
	path->println();
}

void CreateModel::_createFoler(String* path)
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
