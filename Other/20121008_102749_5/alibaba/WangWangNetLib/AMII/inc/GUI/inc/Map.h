#ifndef __GUI_MAP_H__
#define __GUI_MAP_H__

#include "inc/Vector.h"
#include "inc/Object.h"
__GUI_BEGIN_NAMESPACE
template<typename T>
class Enumeration : public Object
{
private:
	Vector<T> vec;
	size_t iter;

public:
	Enumeration();
	Enumeration(Vector<T> vec);
	bool hasMoreElements();
	T nextElement();

	Enumeration<T> operator=(const Vector<T> &vec);
};

template<typename T>
Enumeration<T>::Enumeration()
{
	vec.reserve(0);
	iter = 0;
}
template<typename T>
Enumeration<T>::Enumeration(Vector<T> vec)
{
	this->vec = vec;
	iter = 0;
}
template<typename T>
Enumeration<T> Enumeration<T>::operator = (const Vector<T> &vec)
{
	this->vec = vec;
	iter = 0;
}
template<typename T>
bool Enumeration<T>::hasMoreElements()
{
	if (iter < (size_t)vec.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}
template<typename T>
T Enumeration<T>::nextElement()
{
	T t = vec[iter];
	iter++;
	return t;
}



template<typename T, typename N>
class Map : public map<T, N>, public Object
{
public:
	Enumeration<T> keys();
	Enumeration<N> elements();
	bool isEmpty();
	bool contains(N value);
	bool containsKey(T key);
	N get(T key);
	N put(T key, N value);
	N remove(T key);

	virtual ~Map() {}
};

template<typename T, typename N>
Enumeration<T> Map<T, N>::keys()
{
	Vector<T> vec;
	typename map<T, N>::iterator iter;
	for (iter = map<T, N>::begin(); iter != map<T, N>::end(); ++iter)
	{
		vec.addElement(iter->first);
	}
	Enumeration<T> e(vec);
	return e;
}
template<typename T, typename N>
Enumeration<N> Map<T, N>::elements()
{
	Vector<N> vec;
	typename map<T, N>::iterator iter;
	for (iter = map<T, N>::begin(); iter != map<T, N>::end(); ++iter)
	{
		vec.addElement(iter->second);
	}
	Enumeration<N> e(vec);
	return e;
}
template<typename T, typename N>
bool Map<T, N>::isEmpty()
{
	return map<T, N>::empty();
}

template<typename T, typename N>
bool Map<T, N>::containsKey(T key)
{
	typename map<T, N>::iterator iter;
	for (iter = map<T, N>::begin(); iter != map<T, N>::end(); ++iter)
	{
		if (iter->first == key)
		{
			return true;
		}
	}

	return false;
}

template<typename T, typename N>
bool Map<T, N>::contains(N value)
{
	typename map<T, N>::iterator iter;
	for (iter = map<T, N>::begin(); iter != map<T, N>::end(); ++iter)
	{
		if (iter->second == value)
		{
			return true;
		}
	}

	return false;
}

template<typename T, typename N>
N Map<T, N>::put(T key, N value)
{

	//insert(make_pair<T,N>(key, value));
	//return value;
	
	

	pair<iterator, bool> res;
	res = insert(make_pair(key, value));
	if (res.second == true)
	{
		return N();
	}
	else
	{
		N tmp = (res.first)->second;
		(res.first)->second = value;
		return tmp;
	}

}

template<typename T, typename N>
N Map<T, N>::get(T key)
{
	typename map<T,N>::iterator iter;
	for (iter = map<T,N>::begin(); iter != map<T,N>::end(); ++iter)
	{
		if (iter->first == key)
		{
			N ret= iter->second;
			return ret;
		}
	}

	return N();
}

template<typename T, typename N>
N Map<T, N>::remove(T key)
{
	typename map<T,N>::iterator iter;
	for (iter = map<T,N>::begin(); iter != map<T,N>::end(); ++iter)
	{
		if (iter->first == key)
		{
			N res = iter->second;
			erase(key);
			return res;
		}
	}
	return N();
}
__GUI_END_NAMESPACE

#endif
