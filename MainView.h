#ifndef MAIN_VIEW
#define MAIN_VIEW

class String;
class Controller;

class MainView
{
	friend class MainModel;

public:

	void begin();					//common for all views

	void end();						//common for all views

	static MainView* getObj()
	{
		return obj ? obj : (obj = new MainView());
	}

	const String* getCurrDirectory() const;								//more effective since do not create a new object
	String* getCurrDirectrory();
		
private:

	bool active;
	String* outputPath;
	String* currentDirectory;
	Controller* controller;


	//***************methods for model***********//

	void askForCommand();				//common for all views										//tested

	void reaskCommand();				//common for all views

	bool isCommand(int command);

	void showCorrectCommands();			

	void setController(Controller*);	//common for all views

	//*************private methods************//

//Singleton
private:
	static MainView* obj;

	MainView();

	~MainView() {}
};

#endif // !MAIN_VIEW

