#include "MainModel.h"

void MainModel::askForCommand() 
{ 
	//test
	println("MainModel::askForCommand");

	mainView->showCorrectMainCommands();
	mainView->askForCommand();
}

void MainModel::deleteTable(String* name)
{
	//test
	print("MainModel::deleteTable: arg - ");
	name->println();

	String* path = *mainView->getCurrDirectory() + name;

	if (!existsFile(path))
	{
		println("Table is already absent in the currect folder");
	}
	else
	{
		int err = remove(path->getData());

		if (err)
		{
			println("Problem deleting table");
		}
		else
		{
			println("The table was successfully deleted");
		}
	}

	delete path;
}

void MainModel::deleteFolder(String* name)
{
	//test
	print("MainModel::deleteFolder: arg - ");
	name->println();

	String* path = *mainView->getCurrDirectory() + name;

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
			println("The folder was successfully deleted");
		}
	}

	delete path;
}

void MainModel::goOut()
{
	//test
	println("MainModel::goOut");

	mainView->goToParentDirectory();
}

void MainModel::goIn(String* name)
{
	//test
	println("MainModel::goIn");

	mainView->goToChildDirectory(name);
}

void MainModel::closeProgram()
{
	//TODO some important actions before exiting, such as
	// - save all opened tables;

	//test
	println("MainModel::closeProgram");

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
