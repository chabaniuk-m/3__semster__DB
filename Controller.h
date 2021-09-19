#ifndef CONTROLLER
#define CONTROLLER

class MainModel;
class MainView;
class CreateModel;
class TableModel;
class String;

#include "View.h"

class Controller
{
	template<class T>
	friend class View;
	friend class MainView;
	friend class TableView;
	friend class CreateView;

public:

	static Controller* getObj()
	{
		return obj ? obj : (obj = new Controller());
	}

private:

	MainModel* mainModel;
	CreateModel* createModel;
	TableModel* tableModel;


	//*************methods for views objects**************//

	template<class T>
	void getCommand(View<T>* view) {}

	void getMainCommand();

	void getCreateCommand();

	void getTableCommand();

	//executes concrete command
	void execute(const int command, const String* info);


	//******************private methods****************//

	void setAll(MainView* view);

	int getCommandID(const String* command);

	bool isMainCommand(int command);

	bool isCreateCommand(int command);

	bool isTableCommand(int command);

//Singleton
private:

	static Controller* obj;

	Controller();

	~Controller() {}
};

#endif // !CONTROLLER