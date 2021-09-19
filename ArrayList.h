#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template <class T>
class ArrayList
{
	T* m_arr;				//dynamic
	int m_capacity;
	int m_size;
	bool immutable;

public:
	ArrayList() : ArrayList(4) {}
	ArrayList(int capacity)
		: m_capacity(capacity), m_size(0),
		immutable(false)
	{
		if (m_capacity < 2) m_capacity = 2;

		m_arr = new T[m_capacity]();
	}

	void add(T elem)
	{
		if (!immutable)
		{
			extendSize(1);

			m_arr[m_size - 1] = elem;
		}
	}

	int size() const { return m_size; }

	T get(int index) const
	{
		if (!(0 <= index && index < m_size)) return (T)0;

		return m_arr[index];
	}

	bool empty() const
	{
		return m_size == 0;
	}

	//returns removed element or 0 if index is out of bounds
	T remove(int index)
	{
		if (!immutable)
		{
			if (!(0 <= index && index < m_size)) return (T)0;

			T t = T();
			T removed = m_arr[index];
			m_arr[index] = t;

			for (int i = index; i < m_size - 1; ++i)
			{
				m_arr[i] = m_arr[i + 1];
				m_arr[i + 1] = t;
			}

			--m_size;

			return removed;
		}
		else
		{
			return (T)0;
		}
	}

	void makeImmutable()
	{
		immutable = true;
	}

	bool isImmutable() const
	{
		return immutable;
	}

	T* toArray(int& size) const
	{
		size = m_size;
		T* arr = new T[size];

		for (int i = 0; i < size; i++)
		{
			arr[i] = m_arr[i];
		}

		return arr;
	}

private:

	void extendSize(int extension)
	{
		if (m_size + extension >= m_capacity)
		{
			m_capacity = (m_size + extension) * 3 / 2;

			T* newArr = new T[m_capacity]();

			for (int i = 0; i < m_size; i++)
			{
				newArr[i] = m_arr[i];
			}

			delete[] m_arr;

			m_arr = newArr;
		}
		
		m_size += extension;
	}
};

#endif // !ARRAYLIST_H
