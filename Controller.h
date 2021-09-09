#ifndef CONTROLLER
#define CONTROLLER

#include "Util.h"
#include "MainModel.h"
#include "CreateModel.h"
#include "TableModel.h"
#include "Commands.h"

class MainModel;
class CreateModel;
class TableModel;
class String;
class Controller
{
	MainModel* mainModel;
	CreateModel* createModel;
	TableModel* tableModel;

public:
	void setMainModel(MainModel* model) { mainModel = model; }
	void setCreateModel(CreateModel* model) { createModel = model; }
	void setTableModel(TableModel* model) { tableModel = model; }
	void getMainCommand();
	//executes concrete command
	void execute(int command, const String const* info);

private:
	/*
	* Main commands:
	* - create table [tableName] - create table in the current folderPath
	* - create folderPath [folderName] - create folderPath in the current folderPath and go in it
	* - delete table [tableName] - delete the table in the current folderPath if exists
	*	otherwise print message "There is no such a table in current folderPath"
	* - delete folderPath - delete folderPath if present and empty, otherwise..
	* - move [tableName] - change the table's location if there are at least one nested folder
	* - open folderPath [folderName] - opens a folderPath and appends it to MainView::folderPath
	* - open table [tableName] - opens the table if possible and start working with it
	* - close - close the current folderPath and go back to the parent folderPath,
	*	if than MainView::folderPath is empty ends the program
	* - exit - ends the program
	*/
	int getCommandID(const String const* command);
};

#endif // !CONTROLLER