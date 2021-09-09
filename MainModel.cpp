#include "MainModel.h"

void MainModel::askForCommand() 
{ 
	mainView->showCorrectMainCommands();
	mainView->askForCommand();
}
