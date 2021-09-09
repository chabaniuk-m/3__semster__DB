#ifndef CREATEMODEL
#define CREATEMODEL

#include "CreateView.h"

class CreateView;
class CreateModel
{
	CreateView* createView;

public:
	void setCreateView(CreateView* view) { createView = view; }
	void createTable(String* tableName);
	void createFolder(String* folderName);
	void moveTable(String* tableName);

};

#endif // !CREATEMODEL
