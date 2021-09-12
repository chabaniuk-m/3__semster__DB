#include "TableModel.h"

void TableModel::openTable(String* name)
{
	//test
	println("TableModel::openTable: arg - ");
	name->println();

	String* path = *mainView->getCurrDirectory() + name;

	if (!existsFile(path))
	{
		print("The table ");
		name->print();
		println(" does not exist in the current directory.");
		print("Do you want to create it? ");
		if (userWantToDoIt())
		{
			createModel->createTable(name);
		}
	}
	else
	{
		//test
		println("Opening the table");

		//TODO:
		// - if needed add table to the TableList;
		// - Table* table = list.get(path);
		// - _workWith(table);
	}

	delete path;
	delete name;
}
