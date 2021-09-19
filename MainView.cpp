#include "MainView.h"
#include "Util.h"
#include "String.h"
#include "Commands.h"
#include "Controller.h"

MainView* MainView::obj = nullptr;

MainView::MainView()
	: active(false)
{
	currentDirectory = new String(defaultPath);
	outputPath = new String("database");
	controller = Controller::getObj();
	controller->setAll(this);
}

void MainView::begin()
{
	printf("*********** Data Base **********\n\n");
	active = true;
	while (active)
	{
		askForCommand();
		controller->getMainCommand();
	}
}

void MainView::end()
{
	active = false;
	outputPath = nullptr;
}


const String* MainView::getCurrDirectory() const
{ 
	return currentDirectory;
}

String* MainView::getCurrDirectrory()
{
	return currentDirectory->copy();
}

void MainView::askForCommand()
{
	if (!outputPath)
	{
		println("ERROR TableView::askForCommand: outputPath was not initialize");
	}
	else
	{
		outputPath->print();
		print("> ");
	}
}

void MainView::reaskCommand()
{
	println("The command was not recognized!");
	println("Try the following commands:");
	showCorrectCommands();
	askForCommand();
}

bool MainView::isCommand(int command)
{
	return MAIN_COMMAND_BEGIN < command && command < MAIN_COMMAND_END;
}

void MainView::showCorrectCommands()
{
	println(" - commands;");
	println(" - create table [tableName];");
	println(" - create folder [folderName];");
	println(" - delete table [tableName];");
	println(" - restore [tableName]");
	println(" - delete folder [folderName];");
	println(" - move [tableName]");
	println(" - open folder [folderName];");
	println(" - content;");
	println(" - open table [tableName];");
	println(" - close;");
	println(" - exit.");
}
