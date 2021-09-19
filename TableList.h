#ifndef TABLELIST_H
#define TABLELIST_H

#include "Table.h"

class Table;
class String;
class TableManager;

class TableList
{
	friend class TableManager;

	class Node
	{
		bool deleted = false;

	public:
		Table* table;
		Node* next;

		Node(Table* t, Node* n = nullptr) :
			table(t), next(n) {}
		~Node()
		{
			delete table;
			delete next;
		}

		bool isDeleted() { return deleted; }
		void removeTable() 
		{
			table->simulateDeletion();
			deleted = true;
		}
		Table* restoreTable() 
		{
			deleted = false;
			int err =  table->simulateRestore();

			return err ? nullptr : table;
		}
		bool save();
		void length(int& len) const { if (next) next->length(++len); }
	};

public:

	TableList();
	TableList(Table* arr[], const int size);

	// full path to file
	bool contains(const String* fullPath) const;

	void removeAllTablesInFolder(const String* path);

	//removes table completely without saving if present in the list
	void remove(const Table* table);

	//if table was not found returns nullptr
	TableList::Node* get(const String* path) const;

	//table must be present in database or in list (deleted)
	//if table is not presents in the list opens it,
	//if table can to be loaded returns nullptr
	TableList::Node* open(const String* fullPath);

	//save tables while no proble occurs 
	//but do not actually delete them from the memory
	bool save();

	bool empty() const;

private:

	Node* head;
	Table* unsavedTable;
	int size;

	void add(Table* table);

	//save all tables (ignore unsaved tables)
	void saveAll();

	void deleteSon(Node* parent);

	void deleteHead();
};

#endif // !TABLELIST_H
