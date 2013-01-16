/*
* AMEnable_shared_from_this.h
*
*  Created on: 2010-3-10
*      Author: jiajing_qian
*/
#ifndef _AM_enable_shared_from_this
#define _AM_enable_shared_from_this
//enable_shared_from_this的简单实现版本
#include "AMWeakPtr.h"
#include "AMSharePtr.h"

template<class T> class shared_ptr;
template<class T> class weak_ptr;
template<class T> class enable_shared_from_this;

template<class T>
class enable_shared_from_this
{
protected:
	enable_shared_from_this()
	{}

	enable_shared_from_this(enable_shared_from_this const &)
	{}

	enable_shared_from_this & operator=(enable_shared_from_this const &)
	{  return *this;  }

	~enable_shared_from_this()
	{}

public:
	shared_ptr<T> shared_from_this()
	{
		shared_ptr<T> p = weak_this_;
		AMAssert( p.get() == weak_this_.get() );
		return p;
	}

	 shared_ptr<T const> shared_from_this() const
	{
		shared_ptr<T const> p = weak_this_;
		AMAssert( p.get() == weak_this_.get() );
		return p;
	}
public: // actually private, but avoids compiler template friendship issues

	// Note: invoked automatically by shared_ptr; do not call
	template<class X, class Y> void _internal_accept_owner( shared_ptr<X> const * ppx,Y * py) const
	{
		if( weak_this_.expired() )
		{
			weak_this_ = *ppx;
		}
	}	
private:
	mutable weak_ptr<T> weak_this_;
	
};
#endif