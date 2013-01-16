#ifndef __GUI_VECTOR_H__
#define __GUI_VECTOR_H__

#include "inc/Object.h"
#include "inc/Config.h"

__GUI_BEGIN_NAMESPACE

/************************************************************************/
/* template Vector                                                      */
/************************************************************************/
template<typename T>
class Vector : public vector<T>, public Object
{
private:
	void setSize(int newSize);
public:	
	void addElement(T elem);
	
	bool isEmpty();

	bool contains(T elem);
	int indexOf(T elem, int index = 0);
	int lastIndexOf(T elem);
	int lastIndexOf(T elem, int index);
	int size();
	T &elementAt(int index);
	T &firstElement();
	T &lastElement();

	void setElementAt(T elem, int index);
	void removeElementAt(int index);
	void insertElementAt(T elem, int index);
	bool removeElement(T elem);
	void removeAllElements();

	void copyInto(T *arr);
	void ensureCapacity(int minCapacity);

	bool operator<(Vector<T>& right)
	{
		return (this->firstElement() < right.firstElement());
	}

	virtual ~Vector() {}
};

template<typename T>
void Vector<T>::addElement(T elem)
{
	push_back(elem);
}
template<typename T>
int Vector<T>::size()
{
	return (int)vector<T>::size();
}
template<typename T>
void Vector<T>:: setSize(int newSize)
{
	vector<T>::resize(newSize);
}

template<typename T>
bool Vector<T>:: isEmpty()
{
	return vector<T>::empty();
}

template<typename T>
bool Vector<T>::contains(T elem)
{
	typename vector<T>::iterator iter;
	for (iter = vector<T>::begin(); iter != vector<T>::end(); ++iter)
	{
		if (*iter == elem)
		{
			return true;
		}
	}

	return false;
}

template<typename T>
int Vector<T>:: indexOf(T elem, int index)
{
	int  count= -1;
	typename vector<T>::iterator iter;
	for (iter = vector<T>::begin(); iter != vector<T>::end(); ++iter)
	{
		count++;

		if (*iter == elem && count >= index)
		{
			return count;
		}
	}
	return count;
	/*int size = (int)vector<T>::size();
	for(int i = index ; i < size ; i ++)
	{	
		T temp = elementAt(i);
		if(temp == elem)
		{	
			count = i;
			break;
		}
	}
	return count;*/
}

template<typename T>
int Vector<T>:: lastIndexOf(T elem)
{
	return lastIndexOf(elem, size());
}

template<typename T>
int Vector<T>:: lastIndexOf(T elem, int index)
{
	int count = size();
	typename vector<T>::reverse_iterator iter;
	for (iter = vector<T>::rbegin(); iter != vector<T>::rend(); ++iter)
	{
		count--;

		if (*iter == elem && count <= index)
		{
			return count;
		}
	}

	return -1;
}

template<typename T>
T& Vector<T>:: elementAt(int index)
{
	return vector<T>::at(index);
}

template<typename T>
T& Vector<T>:: firstElement()
{
	return vector<T>::front();
}

template<typename T>
T& Vector<T>:: lastElement()
{
	return vector<T>::back();
}

template<typename T>
void Vector<T>:: setElementAt(T elem, int index)
{
	vector<T>::at(index) = elem;
}

template<typename T>
void Vector<T>:: removeElementAt(int index)
{
	vector<T>::erase(vector<T>::begin() + index);
}

template<typename T>
void Vector<T>:: insertElementAt(T elem, int index)
{
	vector<T>::insert(vector<T>::begin() + index, elem);
}

template<typename T>
bool Vector<T>:: removeElement(T elem)
{
	typename vector<T>::iterator iter;
	for (iter = vector<T>::begin(); iter != vector<T>::end(); ++iter)
	{
		if (*iter == elem)
		{
			iter = vector<T>::erase(iter);
			return true;
		}
	}
	return false;
}

template<typename T>
void Vector<T>:: removeAllElements()
{
	vector<T>::clear();
}

template<typename T>
void Vector<T>:: copyInto(T *arr)
{
	typename vector<T>::iterator iter;
	int index = 0;
	for (iter = vector<T>::begin(); iter != vector<T>::end(); ++iter)
	{
		arr[index++] = *iter;
	}
}

template<typename T>
void Vector<T>:: ensureCapacity(int minCapacity)
{
	vector<T>::resize(minCapacity);
}

/************************************************************************/
/* template class VectorArray                                           */
/************************************************************************/
template<typename T>
class VectorArray : public Object
{
public:
	VectorArray(int newSize = 0);
	VectorArray(VectorArray<T>& rhs);
	virtual ~VectorArray();

public:
	int size();
	T* getDataAddress();
	T &elementAt(int index);
	T& operator [] (int index) const;
	bool operator<(VectorArray<T>& right);
	VectorArray<T> &operator = (VectorArray<T>& rhs);

private:
	T* m_data;
	int length;
};

template<typename T>
VectorArray<T> & VectorArray<T>::operator=( VectorArray<T>& rhs )
{
	if ( this == &rhs)
		return *this;

	if(m_data != NULL)
	{
		delete []m_data;
		m_data = NULL;
	}

	this->m_data = new T[rhs.size()];
	this->length = rhs.size();
	memcpy(this->m_data, rhs.m_data, this->length * sizeof(T));
	return *this;
}
template<typename T>
VectorArray<T>::VectorArray( VectorArray<T>& rhs )
{
// 	if(this->m_data != NULL)
// 	{
// 		delete []this->m_data;
// 	}

	this->m_data = new T[rhs.size()];
	this->length = rhs.size();
	memcpy(this->m_data, rhs.m_data, this->length * sizeof(T));
}
template<typename T>
T& VectorArray<T>::elementAt( int index )
{
	if (index < 0 || index > length)
	{
		//exception
	}
	return m_data[index];
}
template<typename T>
bool VectorArray<T>::operator<( VectorArray<T>& right )
{
	return *(this->m_data) < *(right.m_data);
}

template<typename T>
VectorArray<T>::VectorArray( int newSize /*= 0*/ )
{
	m_data = new T[newSize];
	length = newSize;
}

template<typename T>
ali_gui::VectorArray<T>::~VectorArray()
{
	if (m_data != NULL)
	{
		delete []m_data;
		m_data = NULL;
	}
}

template<typename T>
int VectorArray<T>::size()
{
	return length;
}

template<typename T>
T& VectorArray<T>::operator[]( int index ) const
{
	if (index < 0 || index > length)
	{
		//exception
	}
	return m_data[index];
}

template<typename T>
T* VectorArray<T>::getDataAddress()
{
	return m_data;
}
__GUI_END_NAMESPACE

#endif
