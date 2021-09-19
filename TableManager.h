#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

class Table;
class String;
class TableList;

/*
* The main task of the class is to manage tables
* it does all the stuff we need to do with table
* TableManager is not responsible for output
* thus it is not recommend to output anything in methods
*/
class TableManager
{
public:

	//table exists or was deleted is this session
	bool knowsTable(const String* path) const;

	bool tablesListEmpty() const;


	//****************Main Model********************//

	//file must exists in the database
	//explicitely remove table but save in list of tables, returns error code
	int removeTable(const String* path);

	//path - full path to folder starts with default path
	void removeAllTablesInFolder(const String* path);

	//returs nullptr if table was not found
	Table* restoreTable(const String* path);


	//***************Create Model********************//

	//just explicitely creates a table and adds to list of tables
	//if there was a problem creating a file returns nullptr
	Table* createTable(const String * path, const char* mode = "w+");

	//actually delets the table without the ability to restore it
	//table must be present int TableManager::list,
	//otherwise it won't be deleted
	void deleteTable(Table* table);

	//returns false if the task was not performed (manager asks to try again)
	bool addField(Table* table, const char* name, const char* type);

	//returns false if table does not contain field named name
	bool removeField(Table* table, const char* name);

	//returns false if the task was not performed: key present or name absent (manager asks to try again)
	bool setKeyField(Table* table, const char* name);

	//just make table without key field
	void removeKeyField(Table* table);

	void showFields(Table* table) const;

	//returns false if table does not contains key field
	//TableView::begin() after it
	bool done(Table* table);


	//********************Table Model******************//

	Table* openTable(const String* path);

private:

	TableList* list;
	TableList* added;


private:
	static TableManager* obj;

	TableManager();

	~TableManager() {}

public:
	static TableManager* getObj()
	{
		return obj ? obj : (obj = new TableManager());
	}
};

#endif // !TABLEMANAGER_H
