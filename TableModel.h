#ifndef TABLEMODEL
#define TABLEMODEL

#include "TableView.h"

class TableView;
class TableModel
{
	TableView* tableView;

public:
	void setTableView(TableView* view) { tableView = view; }
	void openTable(String* tableName);
};

#endif // !TABLEMODEL
