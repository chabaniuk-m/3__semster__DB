#ifndef SINGLETON_H
#define SINGLETON_H

//type T - without pointer
//type B - base class for class T
template <class B, class T>
class Singleton
{
	static T* obj;

public:

	static B* getObj();

};

#endif // !SINGLETON_H