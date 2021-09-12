#ifndef MAIN_VIEW
#define MAIN_VIEW

#include "Util.h"
#include "Controller.h"

class Controller;
class MainView
{
	String* currentDirectory = new String("\\Users\\Admin\\Desktop\\database\\");
	Controller* controller;

public:
	void begin();
	void setController(Controller* contr) { controller = contr; }
	String* getCurrDirectory() { return currentDirectory->copy(); }
	void askForCommand();
	void showCorrectMainCommands();
	void goToParentDirectory();
	void goToChildDirectory(String* folerName);

};

#endif // !MAIN_VIEW

