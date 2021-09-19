#ifndef SORT_H
#define SORT_H

template <class T>
class Sorter
{
public:
	virtual void sort(T arr[], const int length, bool (*less)(const T, const T)) const = 0;
};

#endif // !SORT_H
