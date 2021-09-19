#include "View.h"
#include "Util.h"
#include "String.h"
#include "Controller.h"

template<class T>
void View<T>::begin()
{
	active = true;
	while (active)
	{
		askForCommand();
		controller->getCommand(this);
	}
}

template<class T>
void View<T>::end()
{
	active = false;
	outputPath = nullptr;
}

template<class T>
void View<T>::setController(Controller* controller)
{
	this->controller = controller;
}

template<class T>
void View<T>::askForCommand() const
{
	if (!outputPath)
	{
		println("ERROR View::askForCommand: outputPath was not initialized");
	}
	else
	{
		outputPath->print();
		print("> ");
	}
}

template<class T>
void View<T>::reaskCommand() const
{
	println("The command is not recognized!");
	println("Try the following commands:");
	showCorrectCommands();
	askForCommand();
}
