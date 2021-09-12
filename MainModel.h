#ifndef MAINMODEL
#define MAINMODEL

#include "Util.h"
#include "MainView.h"

class MainView;
class MainModel
{
	MainView* mainView;

public:
	void setMain(MainView* view) { mainView = view; }
	void askForCommand();
	void deleteTable(String* name);
	void deleteFolder(String* name);
	void goOut();
	void goIn(String* name);
	void closeProgram();
};

#endif // !MAINMODEL
