#ifndef TABLEMODEL
#define TABLEMODEL

#include "TableView.h"
#include "CreateModel.h"

class TableView;
class CreateModel;
class TableModel
{
	TableView* tableView;
	MainView* mainView;
	CreateModel* createModel;

public:
	void setTable(TableView* view) { tableView = view; }
	void setMain(MainView* view) { mainView = view; }
	void setCreate(CreateModel* model) { createModel = model; }
	void openTable(String* name);

private:
	void _workWith(Table* table);
};

#endif // !TABLEMODEL
