#ifndef VIEW_H
#define VIEW_H

#include "Singleton.h"

template <class B, class T>
class Singleton;

//T is class of actual realization
template <class T>
class View : public Singleton<View<T>, T>
{
	template <class B, class T>
	friend class Singleton;

public:

	void begin();

	void end();

	bool isCommand(int command) const;				//delegate to model

	virtual void showCorrectCommands() const = 0;

	void setController(class Controller*);

	enum class Type
	{
		MAIN,
		CREATE,
		TABLE,
		DEPENDENCY,
	};

	virtual Type getType() const = 0;

protected:

	void askForCommand() const;

	void reaskCommand() const;

	bool active;
	class Controller* controller;
	class String* outputPath;
};

#endif // !VIEW_H
