#include "TableList.h"
#include "Util.h"
#include "String.h"

TableList::TableList()
	: head(nullptr), size(0),
	unsavedTable(nullptr)
{
}

TableList::TableList(Table* arr[], const int size)
	: TableList()
{
	for (int i = 0; i < size; i++)
	{
		add(arr[i]);
	}
}

bool TableList::contains(const String* fullPath) const
{
	Node* curr = head;

	while (curr)
	{
		if (fullPath->equals(curr->table->getPath()))
		{
			return true;
		}

		curr = curr->next;
	}

	return false;
}

TableList::Node* TableList::get(const String* path) const
{
	Node* curr = head;

	while (curr)
	{
		if (path->equals(curr->table->getPath()))
		{
			return curr;
		}

		curr = curr->next;
	}

	return nullptr;
}

TableList::Node* TableList::open(const String* fullPath)
{
	Node* table = get(fullPath);

	if (table)
	{
		return table;
	}
	else
	{
		int err = 0;
		add(new Table(fullPath, err));

		return err ? nullptr : head;
	}
}

bool TableList::save()
{
	Node* curr = head;

	while (curr)
	{
		if (!curr->save())
		{
			unsavedTable = curr->table;

			return false;
		}
	}

	return true;
}

bool TableList::empty() const
{
	return size == 0;
}

void TableList::deleteSon(Node* parent)
{
	if (parent == nullptr || parent->next == nullptr) return;
	
	Node* node = parent->next;

	parent->next = node->next;
	node->next = nullptr;

	delete node;

	--size;
}

void TableList::deleteHead()
{
	if (head == nullptr) return;

	Node* n = head;

	head = head->next;
	n->next = nullptr;

	delete n;

	--size;
}

void TableList::removeAllTablesInFolder(const String* path)
{
	if (head == nullptr) return;

	String* tablePath = new String(head->table->getPath());

	if (tablePath->startsWith(path->getData()))
	{
		delete tablePath;

		deleteHead();

		removeAllTablesInFolder(path);
	}
	else
	{
		Node* parent = head;

		while (parent->next)
		{
			delete tablePath;
			tablePath = new String(parent->next->table->getPath());

			if (tablePath->startsWith(path->getData()))
			{
				deleteSon(parent);
			}

			parent = parent->next;
		}
	}
}

void TableList::remove(const Table* table)
{
	if (head == nullptr) return;

	if (head->table == table)
	{
		deleteHead();
	}
	else
	{
		Node* parent = head;

		while (parent->next)
		{
			if (parent->next->table == table)
			{
				deleteSon(parent);

				break;
			}
		}
	}
}

void TableList::add(Table* table)
{
	if (head)
	{
		head = new Node(table, head);
	}
	else
	{
		head = new Node(table);
	}

	++size;
}

bool TableList::Node::save()
{
	if (!deleted)
	{
		return table->save();
	}

	return true;
}
