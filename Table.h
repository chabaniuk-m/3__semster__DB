#ifndef TABLE
#define TABLE

//represents one file in database
class Table
{
	class Line;
	class LineList;

	char* path;
	int numberOfProperties;
	char** properties;
	LineList* lines;
	//bool isDeleted = false;			//it will do MainModel

public:
	class Line
	{
	public:
		char** notes;

		char* getNote(int noteNumber);
		void setNote(int noteNumber, char newNote[]);
		int compareToByNote(Line other, int noteNumber);
		char* toString();
	};
	class LineList
	{

	};
};

#endif // !TABLE
