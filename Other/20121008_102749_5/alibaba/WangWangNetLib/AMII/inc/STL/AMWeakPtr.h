/*
* AMWeakPtr.h
*
*  Created on: 2010-3-10
*      Author: jiajing_qian
*/
#ifndef _AM_WEAK_PTR_
#define _AM_WEAK_PTR_
//weak_ptr的简单实现版本
#include "AMSharePtr.h"

template<class T>
class weak_ptr
{
public:	
	typedef T element_type;
	typedef T value_type;
	typedef T * pointer;
	typedef T& reference;
	typedef unsigned long size_type;
	
	weak_ptr(): px(0), pn(0)
	{
	}
	
	weak_ptr(const weak_ptr& r) throw()
		: px(r.px),pn(r.pn)
	{
	}
	//template<class T> class shared_ptr;
	//weak_ptr(const shared_ptr<T>& r) throw()
	//	: px(r.px),pn(r.pn)
	//{
	//}
	weak_ptr& operator= (const weak_ptr& r) throw()
	{
		if(this == &r) 
			return *this;

		px = r.px;
		pn = r.pn;
		return *this;
	}
	/*weak_ptr& operator= (const shared_ptr<T>& r) throw()
	{
		px = r.px;
		pn = r.pn;
		return *this;
	}*/
	template<class Y>
	weak_ptr(const weak_ptr<Y>& r)
		:px(r.px),pn(r.pn)
	{

	}
	
	template<class Y>
	weak_ptr& operator= (const weak_ptr<Y>& r)
	{
		if(px == r.px) 
			return *this;

		px=r.px;
		pn = r.pn;
		return *this;
	}
	template<class Y>
	weak_ptr(const shared_ptr<Y>  & r)
		:px(r.px),pn(r.pn)
	{

	}

	template<class Y>
	weak_ptr & operator=(const shared_ptr<Y>  & r) // never throws
	{
		px = r.px;
		pn = r.pn;
		return *this;
	}


	reference operator*() const throw(){ return *px; }
	pointer operator->() const throw(){ return px; }
	pointer get() const throw(){ return px; }
	size_type use_count() const throw()
	{ return *pn; }
	bool expired() const // never throws
	{	
		if(pn != 0)
			return *pn == 0;
		else 
			return true;
	}
	bool unique() const throw()
	{ return 0; }
	
private:
	template<class Y> friend class shared_ptr;
	T * px; // contained pointer
public:
	size_type* pn; // reference counter
}; // weak_ptr


template<typename A,typename B>
inline bool operator==(weak_ptr<A> const & l, weak_ptr<B> const & r)
{
	return l.get() == r.get();
}
template<typename A,typename B>
inline bool operator!=(weak_ptr<A> const & l, weak_ptr<B> const & r)
{
	return l.get() != r.get();
}
#endif //_AM_SHARE_PTR_

