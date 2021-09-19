#ifndef MAINMODEL
#define MAINMODEL

class String;
class MainView;
class TableManager;

//works only inside folders, can't create or change table inside
class MainModel
{
	friend class Controller;

public:

	static MainModel* getObj()
	{
		return obj ? obj : (obj = new MainModel());
	}

private:

	TableManager* manager;
	MainView* mainView;


	//***************methods for controoler*************//

	void setMain(MainView* view);
	
	void askForCommand();
	
	void printCommands();
	
	void deleteTable(const String * name);

	void restore(const String* name);
	
	void deleteFolder(String* name);
	
	void close();
	
	//can open only folder
	void open(const String* name);

	void content();
	
	void closeProgram();


	//****************private methods***************//

private:
	static MainModel* obj;

	MainModel();

	~MainModel() {}
};

#endif // !MAINMODEL
