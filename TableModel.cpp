#include "TableModel.h"
#include "TableView.h"
#include "CreateModel.h"
#include "MainView.h"
#include "TableManager.h"
#include "String.h"
#include "Table.h"
#include "Util.h"

TableModel* TableModel::obj = nullptr;

void TableModel::setViewController(class Controller* c)
{
	tableView->setController(c);
}

void TableModel::askForCommand()
{
	println("The command was not recognized!");
	println("Try the following commands:");
	tableView->showCorrectCommands();
	tableView->askForCommand();
}

TableModel::TableModel()
	: table(nullptr),
	manager(TableManager::getObj()),
	tableView(TableView::getObj()),
	createModel(CreateModel::getObj())
{
	//mainView = MainView::getObj();			- stack over flow
}

void TableModel::openTable(const String* name)
{
	//test
	print("TableModel::openTable: arg - ");
	name->println();

	String* path = *currentDirectory() + name;

	if (!existsFile(path))
	{
		if (manager->knowsTable(path))
		{
			println("The table has been recently deleted.");
			print("Do you want to restore it? ");

			if (userWantToDoIt())
			{
				table = manager->restoreTable(path);
				if (table)
				{
					openTable(table);
				}
				else
				{
					println("Sorry.. Problem restoring file.");
					println("It seems we have lose it completely :(");
				}
			}
		}
		else
		{
			print("The table ");
			name->print();
			println(" does not exist in the current directory.");
			print("Do you want to create it? ");
			if (userWantToDoIt())
			{
				createModel->createTable(name->copy());			//passes copy to exclude errors
			}
		}
	}
	else                                                   //table exists and not deleted
	{
		table = manager->openTable(path);

		if (!table)
		{
			println("Wow! Table exists but we cannot open it.");
			println("Maybe access is denied");
		}
		else
		{
			openTable(manager->openTable(path));
		}
	}

	delete path;
	delete name;
}

void TableModel::openTable(Table* table)
{
	tableView->outputPath = new String("Table: ");
	String* path = new String(table->getPath());
	String* sub = path->substr(databaseIndex);
	tableView->outputPath->append(sub);
	delete path;
	delete sub;
	tableView->begin();
}

