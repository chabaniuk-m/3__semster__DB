#include "CreateView.h"
#include "Controller.h"
#include "Commands.h"
#include "String.h"
#include "Util.h"

CreateView* CreateView::obj = nullptr;

void CreateView::begin()
{
	active = true;
	while (active)
	{
		askForCommand();
		controller->getCreateCommand();
	}
}

void CreateView::end()
{
	active = false;
	outputPath = nullptr;
}

void CreateView::askForCommand()
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

void CreateView::reaskCommand()
{
	println("The command is not recognized!");
	println("Try the following commands:");
	showCorrectCommands();
	askForCommand();
}

bool CreateView::isCommand(int command)
{
	return CREATE_COMMAND_BEGIN < command && command < CREATE_COMMAND_END;
}

void CreateView::showCorrectCommands()
{
	println(" - add field;");
	println(" - remove field;");
	println(" - set key field;");
	println(" - show;");
	println(" - done;");
	println(" - delete.");
}

void CreateView::setController(Controller* c)
{
	controller = c;
}

CreateView::CreateView()
	: active(false),
	controller(nullptr),
	outputPath(nullptr)
{
	//controller = Controller::getObj()			- stack over flow
}