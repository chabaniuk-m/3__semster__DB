#ifndef STACK_H
#define STACK_H

template <class T>
class Stack
{
	template <class T>
	class Node
	{
	public:

		T data;
		int numberOfLine = 0;
		Node<T>* next;

		Node(T d, Node<T>* n = nullptr)
			: data(d), next(n) {}

		~Node()
		{
			delete next;
		}
	};

	Node<T>* top;

public:

	Stack() : top(nullptr) {}

	void push(T data)
	{
		top = new Node<T>(data, top);
	}

	T pop()
	{
		if (top == nullptr) return (T)0;

		T res = top->data;

		Node<T>* node = top;
		top = top->next;
		node->next = nullptr;

		delete node;

		return res;
	}

	T peek() const
	{
		if (top == nullptr) return (T)0;

		return top->data;
	}

	bool empty() const
	{
		return top == nullptr;
	}
};
#endif // !STACK_H
