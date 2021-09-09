#include "Controller.h"

void Controller::getMainCommand()
{
	const int size = 128;
	char command[size];
	for (int i = 0; i < size; i++)
		command[i] = '\0';

	gets_s(command, size);
	String* str = new String(command);
	int commandID = getCommandID(str);
	while (commandID == INCORRECT_COMMAND)
	{
		mainModel->askForCommand();
		gets_s(command, size);
		delete str;
		str = new String(command);
		commandID = getCommandID(str);
	}

	execute(commandID, str);
}

void Controller::execute(int command, const String const* info)
{
	if (command == CREATE_TABLE) createModel->createTable(info->substr(13));

	else if (command == CREATE_FOLDER) createModel->createFolder(info->substr(14));

	else if (command == MOVE_TABLE) createModel->moveTable(info->substr(5));

	else if (command == OPEN_TABLE) tableModel->openTable(info->substr(11));

	else if (command == DELETE_TABLE) mainModel->deleteTable(info->substr(13));

	else if (command == DELETE_FOLDER) mainModel->deleteFolder(info->substr(14));

	else if (command == CLOSE) mainModel->goOut();

	else if (command == OPEN_FOLDER) mainModel->goIn(info->substr(12));

	else if (command == EXIT) mainModel->closeProgram();

	else
	{
		println("Error in method Controller::execute():");
		printf("\tUnrecognized command with id %d\n", command);
	}

	delete info;
}

int Controller::getCommandID(const String const* command)
{
	if (command->empty()) return INCORRECT_COMMAND;

	if (command->startsWith("c"))
	{
		if (command->startsWith("create table "))
			return CREATE_TABLE;
		else if (command->startsWith("create folder "))
			return CREATE_FOLDER;
		else if (command->equals("close"))
			return CLOSE;
		else
			return INCORRECT_COMMAND;
	}
	else if (command->startsWith("delete "))
	{
		if (command->startsWith("delete table "))
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
	else if (command->startsWith("move "))
		return MOVE_TABLE;
	else if (command->equals("exit"))
		return EXIT;

	return INCORRECT_COMMAND;
}
