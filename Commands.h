#ifndef COMMANDS_H
#define COMMANDS_H

const int INCORRECT_COMMAND = -1;

//*********main commands***********//

const int MAIN_COMMAND_BEGIN = 0;
const int CREATE_TABLE = 1;
const int CREATE_FOLDER = 2;
const int DELETE_TABLE = 3;
const int DELETE_FOLDER = 4;
const int OPEN_FOLDER = 5;
const int OPEN_TABLE = 6;
const int CLOSE = 7;
const int EXIT = 8;
const int MOVE_TABLE = 9;
const int COMMANDS = 10;
const int RESTORE = 11;
const int CONTENT = 12;

const int MAIN_COMMAND_END = 50;

//**********create commands**********//

const int CREATE_COMMAND_BEGIN = 51;
const int ADD_FIELD = 52;
const int REMOVE_FIELD = 53;
const int SET_KEY_FIELD = 54;
const int RESET_KEY_FIELD = 55;
const int SHOW = 56;
const int DONE = 57;
const int DELETE = 58;							//delete current table

const int CREATE_COMMAND_END = 100;

//**********table commands**********//

const int TABLE_COMMAND_BEGIN = 101;
const int ADD_LINE = 102;						//ask for fields step by step
const int EDIT_LINE = 103;						//ask what field to change (find line fy key)
const int REMOVE_LINE = 104;					//remove line by key
const int GET_KEY = 105;						//returns the name of key field
const int CLEAR = 106;							//removel all line and dependecies of these lines
const int CLOSE_TABLE = 107;
const int FIELDS = 108;							//show all fields (the same as show in CreateTable)
const int TABLE_CONTENT = 109;					//show all lines of the table
const int TABLE_DELETE = 110;					//permanently deletes the table

const int TABLE_COMMAND_END = 150;

#endif // !COMMANDS_H
