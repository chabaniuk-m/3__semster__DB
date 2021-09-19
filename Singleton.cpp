#include "Singleton.h"


template <class B, class T>
T* Singleton<B, T>::obj = nullptr;

template<class B, class T>
B* Singleton<B, T>::getObj()
{
	return obj ? obj : (obj = new T());
}
