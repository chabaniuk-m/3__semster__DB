#ifndef CREATEVIEW_H
#define CREATEVIEW_H

// Needs only while creating a table
class CreateView
{
	friend class CreateModel;

public:

	static CreateView* getObj()
	{
		return obj ? obj : (obj = new CreateView());
	}	

private:

	bool active;
	class Controller* controller;
	class String* outputPath;


	//***************methods for model*************//

	void begin();						//common for all views

	void end();							//common for all views

	void askForCommand();				//common for all views

	void reaskCommand();				//common for all views

	bool isCommand(int command);

	void showCorrectCommands();

	void setController(Controller*);	//common for all views


	//***************private methods**************//

private:
	static CreateView* obj;

	CreateView();

	~CreateView() {}

};

#endif // !CREATEVIEW

