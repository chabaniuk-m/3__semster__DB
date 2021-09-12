#ifndef CREATEMODEL
#define CREATEMODEL

#include "CreateView.h"

class CreateView;
class MainView;
class CreateModel
{
	CreateView* createView;
	MainView* mainView;

public:
	void set(CreateView* view) { createView = view; }
	void set(MainView* view) { mainView = view; }
	void createTable(String* name);
	void createFolder(String* name);
	void moveTable(String* name);

private:
	//suppose that file / folder does not exist in the path (parent)
	//path - is path to file / folder starts with "database\\"
	void _createTable(String* path);
	void _createFoler(String* path);
};

#endif // !CREATEMODEL
