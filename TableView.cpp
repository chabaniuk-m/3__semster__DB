#include "TableView.h"
#include "Controller.h"
#include "Commands.h"
#include "Util.h"
#include "String.h"

TableView* TableView::obj = nullptr;

void TableView::begin()
{
	active = true;
	while (active)
	{
		askForCommand();
		controller->getTableCommand();
	}
}

void TableView::end()
{
	active = false;
	outputPath = nullptr;
}

void TableView::askForCommand()
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

void TableView::reaskCommand()
{
	println("The command was not recognized!");
	println("Try the following commands:");
	showCorrectCommands();
	askForCommand();
}

bool TableView::isCommand(int command)
{
	return TABLE_COMMAND_BEGIN < command && command < TABLE_COMMAND_END;
}

void TableView::showCorrectCommands()
{
	println(" - add line;");
	println(" - edit line;");
	println(" - remove line;");
	println(" - get key;");
	println(" - clear;");
	println(" - close;");
}

void TableView::setController(Controller* c)
{
	controller = c;
}

TableView::TableView()
	: active(false),
	controller(nullptr),
	outputPath(nullptr)
{
}

