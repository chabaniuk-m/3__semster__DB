#ifndef MAIN_VIEW
#define MAIN_VIEW

#include "Util.h"
#include "Controller.h"

class Controller;
class MainView
{
	String* folderPath = new String("database\\");
	int length = 9;
	Controller* controller;

public:
	void setController(Controller* contr) { controller = contr; }
	void begin();
	void askForCommand();
	void showCorrectMainCommands();

};

#endif // !MAIN_VIEW

