#include "MainModel.h"
#include "Util.h"
#include "String.h"
#include "MainView.h"
#include "TableManager.h"

MainModel* MainModel::obj = nullptr;

MainModel::MainModel()
	: mainView(nullptr)
{
	manager = TableManager::getObj();
	//mainView = MainView::getObj();			stack over flow
}

void MainModel::setMain(MainView* view) { mainView = view; }

void MainModel::askForCommand()
{ 
	println("The command was not recognized!");
	println("Try the following commands:");
	mainView->showCorrectCommands();
	mainView->askForCommand();
}

void MainModel::printCommands()
{
	mainView->showCorrectCommands();
}

void MainModel::deleteTable(const String * name)
{
	String* path = *currentDirectory() + name;

	if (!existsFile(path))
	{
		println("Table is already absent in the currect folder");
	}
	else
	{
		int err = manager->removeTable(path);

		if (err)
		{
			println("Problem deleting table");
		}
		else
		{
			println("The table was successfully deleted");
			println("But until you exite the program you can restore it.");
			println("To do it you need to open folder where was the table and type:");
			println(" restore [tableName]");
		}
	}

	delete path;
	delete name;
}

void MainModel::restore(const String* name)
{
	print("MainModel::restore: name - ");
	name->println();

	String* path = *currentDirectory() + name;

	if (!correctFilePath(path))
	{
		println("You have entered an incorrect table name.");
		println("Forbiddens for table names:");
		showFileNameForbiddens();

		delete name;
		delete path;
		
		return;
	}

	if (existsFile(path))
	{
		println("The table is already exists");
	}
	else
	{
		Table* table = manager->restoreTable(path);

		if (!table)
		{
			println("The table have never been created or deleted permanently");
			println("thus it is not possible to restore it");
		}
		else
		{
			println("The table was successfully restored");
		}
	}

	delete name;
	delete path;
}

void MainModel::deleteFolder(String* name)
{
	//test
	print("MainModel::deleteFolder: arg - ");
	name->println();

	println("If you delete this folder you won't be able to restore its' content");
	print("Are you sure\? ");

	if (userWantToDoIt())
	{
		String* path = *currentDirectory() + name;

		delete name;

		if (!existsDir(path))
		{
			println("This folder is already absent in the current directory");
		}
		else
		{
			int err = _rmdir(path->getData());

			if (err)
			{
				println("Problem deleting the folder.");
				println("Maybe folder is not empty thus we can not delete it");
			}
			else
			{
				manager->removeAllTablesInFolder(path);
				println("The folder was successfully deleted.");
			}
		}

		delete path;
	}
}

void MainModel::close()
{
	if (mainView->outputPath->equals("database"))
	{
		if (manager->tablesListEmpty())
		{
			closeProgram();
		}
		println("If you close the database you won't be able");
		print("to restore all deleted tables. Are you sure? ");

		if (userWantToDoIt()) closeProgram();
	}
	else
	{
		String* parent = getParentDirectory(mainView->currentDirectory);

		delete mainView->currentDirectory;

		mainView->currentDirectory = parent;

		int idx = mainView->outputPath->getLength() - 2;

		while (mainView->outputPath->at(idx) != '\\') --idx;

		parent = mainView->outputPath->substr(0, idx);

		delete mainView->outputPath;

		mainView->outputPath = parent;
	}
}

void MainModel::open(const String* name)
{
	String* newDirectory = *mainView->currentDirectory + name->getData();
	newDirectory->append("\\");
		
	if (!existsDir(newDirectory))
	{
		print("The folder ");
		name->print();
		println(" does not exist in the current directory.");
		print("Do you want to create it? ");

		if (userWantToDoIt())
		{
			ucreateDir(newDirectory);
			goto openDir;
		}
		else
		{
			delete newDirectory;
		}
	}
	else openDir:
	{
		delete mainView->currentDirectory;
		mainView->currentDirectory = newDirectory;

		mainView->outputPath->append("\\")->append(name);
	}
	/*String* newDir = *mainView->currentDirectory + name->getData();
	newDir->append("\\");
	if (!existsDir(newDir))
	{
		print("Folder ");
		name->print();
		print(" does not exist in the directory ");
		mainView->outputPath->print();
		print(".\nIf you want to create it type \"yes\": ");
		if (userWantToDoIt())
		{
			ucreateDir(newDir);
			goto goIn;
		}
		else
		{
			delete newDir;
		}
	}
	else
	{
	goIn:
		delete currentDirectory;
		currentDirectory = newDir;
		outputPath->append("\\")->append(name);
	}*/

	delete name;
}

void MainModel::content()
{
	printFolderContent(mainView->currentDirectory);
}

void MainModel::closeProgram()
{
	//TODO some important actions before exiting, such as
	// - save all opened tables;

	bool savedStuffCorrectly = true;

	//save all stuff

	if (savedStuffCorrectly)
	{
		println("The program has successfully finished it's executing");
		exit(0);
	}
	else
	{
		println("Error: something went wrong while saving the data");
		print("If you really want to exit type \"yes\": ");

		if (userWantToDoIt()) exit(1);
	}
}
