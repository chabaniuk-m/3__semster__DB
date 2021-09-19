#ifndef TABLEMODEL
#define TABLEMODEL

class Table;
class TableView;
class CreateModel;
class MainView;
class String;
class TableManager;

class TableModel
{
	friend class Controller;

public:

	void openTable(const String* name);

	//opens table and starts working with it
	void openTable(Table* table);

	static TableModel* getObj()
	{
		return obj ? obj : (obj = new TableModel());
	}

private:

	Table* table;
	TableManager* manager;
	TableView* tableView;
	CreateModel* createModel;


	//************methods for controller**************//

	void setViewController(class Controller*);

	void askForCommand();


	//************private methods*****************//

	//void _workWith(Table* table);

private:
	static TableModel* obj;

	TableModel();

	~TableModel() {}
};

#endif // !TABLEMODEL
