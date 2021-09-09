#ifndef MAINMODEL
#define MAINMODEL

#include "Util.h"
#include "MainView.h"

class MainView;
class MainModel
{
	MainView* mainView;

public:
	void setMainView(MainView* view) { mainView = view; }
	void askForCommand();
	void deleteTable(String* tableName);
	void deleteFolder(String* folderName);
	void goOut();
	void goIn(String* folderName);
	void closeProgram();
};

#endif // !MAINMODEL
