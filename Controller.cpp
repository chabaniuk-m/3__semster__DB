#include "Controller.h"
#include "Util.h"
#include "String.h"
#include "MainModel.h"
#include "CreateModel.h"
#include "TableModel.h"
#include "Commands.h"

Controller* Controller::obj = nullptr;

Controller::Controller()
{
	mainModel = MainModel::getObj();
	createModel = CreateModel::getObj();
	tableModel = TableModel::getObj();
}

void Controller::getMainCommand()
{
	const int size = 128;
	char command[size];
	for (int i = 0; i < size; i++)
		command[i] = '\0';

	gets_s(command, size);
	String* str = new String(command);
	int commandID = getCommandID(str);
	while (!isMainCommand(commandID))
	{
		mainModel->askForCommand();
		gets_s(command, size);
		delete str;
		str = new String(command);
		commandID = getCommandID(str);
	}

	execute(commandID, str);
}

void Controller::getCreateCommand()
{
	const int size = 128;
	char command[size];
	for (int i = 0; i < size; i++)
		command[i] = '\0';

	gets_s(command, size);
	String* str = new String(command);
	int commandID = getCommandID(str);
	while (!isCreateCommand(commandID))
	{
		createModel->askForCommand();
		gets_s(command, size);
		delete str;
		str = new String(command);
		commandID = getCommandID(str);
	}

	execute(commandID, str);
}

void Controller::getTableCommand()
{
	const int size = 128;
	char command[size];
	for (int i = 0; i < size; i++)
		command[i] = '\0';

	gets_s(command, size);
	String* str = new String(command);
	int commandID = getCommandID(str);
	while (!isTableCommand(commandID))
	{
		tableModel->askForCommand();
		gets_s(command, size);
		delete str;
		str = new String(command);
		commandID = getCommandID(str);
	}

	execute(commandID, str);
}

void Controller::execute(const int command, const String* info)
{
	switch (command)
	{
	case COMMANDS:			mainModel->printCommands();						break;
	case OPEN_FOLDER:		mainModel->open(info->substr(12));				break;
	case CONTENT:			mainModel->content();							break;
	case DELETE_TABLE:		mainModel->deleteTable(info->substr(13));		break;
	case RESTORE:			mainModel->restore(info->substr(8));			break;
	case DELETE_FOLDER:		mainModel->deleteFolder(info->substr(14));		break;
	case CLOSE:				mainModel->close();								break;
	case EXIT:				mainModel->closeProgram();						break;
	
	case CREATE_TABLE:		createModel->createTable(info->substr(13));		break;
	case MOVE_TABLE:		createModel->moveTable(info->substr(5));		break;
	case DELETE:			createModel->deleteCurrentTable();				break;
	case CREATE_FOLDER:		createModel->createFolder(info->substr(14));	break;
	case ADD_FIELD:			createModel->addField();						break;
	case REMOVE_FIELD:		createModel->removeField();						break;
	case SET_KEY_FIELD:		createModel->setKeyField();						break;
	case RESET_KEY_FIELD:	createModel->resetKeyField();					break;
	case SHOW:				createModel->show();							break;
	case DONE:				createModel->done();							break;

	case OPEN_TABLE:		tableModel->openTable(info->substr(11));		break;

	default: {
			println("ERROR: Controller::execute():");
			printf("\tUnrecognized command with id %d\n", command);
			break;
		}
	}

	delete info;
}

void Controller::setAll(MainView* view)
{
	mainModel->mainView = view;
	createModel->setViewController(this);
	tableModel->setViewController(this);
}

int Controller::getCommandID(const String* command)
{
	if (command->empty()) return INCORRECT_COMMAND;

	if (command->startsWith("c"))
	{
		if (command->equals("content"))
			return CONTENT;
		else if (command->startsWith("create table "))
			return CREATE_TABLE;
		else if (command->startsWith("create folder "))
			return CREATE_FOLDER;
		else if (command->equals("close"))
			return CLOSE;
		else if (command->equals("commands"))
			return COMMANDS;
		else
			return INCORRECT_COMMAND;
	}
	else if (command->startsWith("d"))
	{
		if (command->equals("done"))
			return DONE;
		else if (command->equals("delete"))
			return DELETE;
		else if (command->startsWith("delete table "))
			return DELETE_TABLE;
		else if (command->startsWith("delete folder "))
			return DELETE_FOLDER;
		else
			return INCORRECT_COMMAND;
	}
	else if (command->startsWith("open "))
	{
		if (command->startsWith("open folder "))
			return OPEN_FOLDER;
		else if (command->startsWith("open table "))
			return OPEN_TABLE;
		else
			return INCORRECT_COMMAND;
	}
	else if (command->startsWith("restore "))
	{
		return RESTORE;
	}
	else if (command->startsWith("move "))
	{
		return MOVE_TABLE;
	}
	else if (command->equals("exit"))
	{
		return EXIT;
	}
	else if (command->equals("add field"))
	{
		return ADD_FIELD;
	}
	else if (command->equals("remove field"))
	{
		return REMOVE_FIELD;
	}
	else if (command->equals("set key field"))
	{
		return SET_KEY_FIELD;
	}
	else if (command->equals("reset key field"))
	{
		return RESET_KEY_FIELD;
	}
	else if (command->equals("show"))
	{
		return SHOW;
	}

	return INCORRECT_COMMAND;
}

bool Controller::isMainCommand(int command)
{
	return MAIN_COMMAND_BEGIN < command && command < MAIN_COMMAND_END;
}

bool Controller::isCreateCommand(int command)
{
	return CREATE_COMMAND_BEGIN < command && command < CREATE_COMMAND_END;
}

bool Controller::isTableCommand(int command)
{
	return TABLE_COMMAND_BEGIN < command&& command < TABLE_COMMAND_END;
}
