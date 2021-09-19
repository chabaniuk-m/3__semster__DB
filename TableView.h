#ifndef TABLEVIEW_H
#define TABLEVIEW_H

class Controller;

class TableView
{
	friend class TableModel;

public:

	static TableView* getObj()
	{
		return obj ? obj : (obj = new TableView());
	}

private:

	bool active;
	class String* outputPath;
	Controller* controller;


	//**************methods for model************//

	void begin();						//common for all views

	void end();							//common for all views

	void askForCommand();				//common for all views

	void reaskCommand();				//common for all views

	bool isCommand(int command);		//common for all views

	void showCorrectCommands();

	void setController(Controller*);	//common for all views


	//***************private methods************//

//Singleton
private:
	static TableView* obj;

	TableView();

	~TableView() {}

};

#endif // !TABLEVIEW_H

