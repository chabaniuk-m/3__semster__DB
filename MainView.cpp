#include "MainView.h"

void MainView::begin()
{
	printf("*********** Data Base **********\n\n");
	askForCommand();
	controller->getMainCommand();
}

void MainView::askForCommand()
{
	printf("%s> ", folderPath);
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
