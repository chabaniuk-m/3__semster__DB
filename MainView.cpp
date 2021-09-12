#include "MainView.h"

void MainView::begin()
{
	printf("*********** Data Base **********\n\n");
	while (true)
	{
		askForCommand();
		controller->getMainCommand();
	}
}

void MainView::askForCommand()
{
	currentDirectory->print();
	print("> ");
}

void MainView::showCorrectMainCommands()
{
	println("The command was not recognized!");
	println("Try the following commands:");
	println(" - create table [tableName];");
	println(" - create folder [folderName];");
	println(" - delete table [tableName];");
	println(" - delete folder;");
	println(" - move [tableName]");
	println(" - open folder [folderName];");
	println(" - open table [tableName];");
	println(" - close;");
	println(" - exit.");
}

void MainView::goToParentDirectory()
{
	int index;

	if ((index = currentDirectory->lastIndexOf('\\') == String::NPOS))
	{
		println("You are trying to close the database,");
		println("this action will actually close the program,");
		print("if you really want to close the program type \"yes\": ");

		if (userWantToDoIt()) controller->execute(EXIT, nullptr);
	}
	else
	{
		String* parent = currentDirectory->substr(0, index);
		delete currentDirectory;
		currentDirectory = parent;
	}

	//test
	print("Current folder: ");
	currentDirectory->println();
}

void MainView::goToChildDirectory(String* folderName)
{
	//test
	folderName->println();

	String* newDir = *(*currentDirectory + folderName->getData()) + "\\";

	if (!existsDir(newDir))
	{
		print("Folder ");
		folderName->print();
		print(" does not exist in the directory ");
		currentDirectory->println();
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
	}

	//test
	print("Current directory: ");
	currentDirectory->println();
}
