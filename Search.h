#ifndef SEARCH_H
#define SEARCH_H

template <class T>
class Searcher
{
public:
	virtual int search(T arr[], const int length, T x) const = 0;
};

#endif // !SEARCH_H
