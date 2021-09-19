#ifndef MODEL_H
#define MODEL_H

#include "Singleton.h"
#include "View.h"

template <class T>
class View;

template <class B, class T>
class Singleton;

//T is class of actual realization
template <class T>
class Model : public Singleton<Model<T>, T>
{
	template <class B, class T>
	friend class Singleton;

public:

	virtual bool isCommand() const = 0;

	virtual void execute() = 0;

	virtual typename View<T>::Type getType() const = 0;

protected:

	View<T>* view;

};

#endif // !MODEL_H
