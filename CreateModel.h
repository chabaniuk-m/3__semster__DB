#ifndef CREATEMODEL
#define CREATEMODEL

class CreateView;
class MainView;
class String;
class Table;
class TableManager;

class CreateModel
{
	friend class Controller;

public:

	void createTable(const String* name);				//for TableModel

	void createFolder(const String* name);				//for TableModel

private:

	Table* table;								//table what the class is initializing
	TableManager* manager;
	CreateView* createView;


	//*************methods for controller*****************//

	void setViewController(class Controller*);

	void deleteCurrentTable();

	void addField();

	void removeField();

	void setKeyField();

	void resetKeyField();

	void show();

	void done();

	void moveTable(const String* name);

	void askForCommand();


	//**************private methods*******************//

	//directly interacts with the table
	//suppose that file / folder does not exist in the path (parent)
	//path - is path to file / folder starts with "database\\"
	void _createTable(const String * path);

	void _createFoler(const String * path);

private:
	static CreateModel* obj;

	CreateModel();

	~CreateModel() {}

public:
	static CreateModel* getObj()
	{
		return obj ? obj : (obj = new CreateModel());
	}
};

#endif // !CREATEMODEL
