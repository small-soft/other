/*
* AMSharePtr.h
*
*  Created on: 2010-2-1
*      Author: qinghua.liqh
*/
#ifndef _AM_SHARE_PTR_
#define _AM_SHARE_PTR_
//#include "AMWeakPtr.h"
//#include "AMEnable_shared_from_this.h"
#include "AMOS.h"
//shared_ptr的简单实现版本

template<class T> class shared_ptr;
template<class T> class weak_ptr;
template<class T> class enable_shared_from_this;

template<class T>
class shared_ptr
{
public:
    typedef T element_type;
    typedef T value_type;
    typedef T *pointer;
    typedef T &reference;
    typedef unsigned long size_type;

	shared_ptr(): px(0), pn(0) 
	{
	}

    shared_ptr(T* p) 
		: px(p)
    {
        try 
        { 
        	pn = new size_type(1); 
    		AMAssert(pn);
			sp_enable_shared_from_this(this,p,p);
        }
        catch (...) 
        { 
        	delete(p); 
        	throw; 
        }

    }
    shared_ptr(const shared_ptr<T>& r) throw()
		: px(r.px)
    {	
    	/*if(r.pn != 0 && *(r.pn) != 0)
    		++(*r.pn); */  

		increase(r.pn);
		pn = r.pn;
    }
	template<class Y>
	shared_ptr(const shared_ptr<Y>& r,T*p) throw()
		: px(p)
	{	
		/*if(r.pn != 0 && *(r.pn) != 0)
			++(*r.pn);   */
		increase(r.pn);
		pn = r.pn;
	}
	template<class Y>
	shared_ptr(const weak_ptr<Y>& r,T*p) throw()
		: px(p)
	{	
		/*if(r.pn != 0 && *(r.pn) != 0)
		++(*r.pn);   */
		increase(r.pn);
		pn = r.pn;
	}

    shared_ptr& operator= (const shared_ptr<T>& r) throw()
    {
        if(this == &r) 
        	return *this;
        
        dispose();
        px = r.px;
	/*	if(r.pn != 0 && *(r.pn) != 0)
			++(*r.pn);  */ 
		increase(r.pn);

        pn = r.pn;
        return *this;
    }

    bool operator!=(shared_ptr<T> const & r)
    {
        return (*this).get() != r.get();
    }
    
    template<typename Y> friend class shared_ptr;
    
    template<class Y>
    shared_ptr(const shared_ptr<Y>& r)
    {
        px = r.px;
	/*	if(r.pn != 0 && *(r.pn) != 0)
			++(*r.pn);   */
		increase(r.pn);

        pn = r.pn; // shared_count::op= doesn't throw
    }
    template<class Y>
    shared_ptr& operator= (const shared_ptr<Y>& r)
    {
        dispose();
        px = r.px;
	/*	if(r.pn != 0 && *(r.pn) != 0)
			++(*r.pn);   */
		increase(r.pn);
        pn = r.pn; // shared_count::op= doesn't throw
        return *this;
    }
    
	template<typename Y> friend class weak_ptr;
	
	template<class Y>
	shared_ptr(const weak_ptr<Y>& r) throw()
		: px(r.get())
	{	
		/*if(r.pn != 0 && *(r.pn) != 0)
			++(*r.pn);  */ 
		increase(r.pn);
		pn = r.pn;
	}
  /*  template<class Y>
    shared_ptr& operator=(const weak_ptr<Y>& r) throw()
    {
		px = r.px;
		pn = r.pn;
		*pn ++;
    }*/

    template<class Y>
    shared_ptr& operator= (Y* py)
    {
        if(this->px == py) 
        	return *this;
        
        dispose();
        
        try 
        {	
			
        	pn = new size_type(1); 
			AMAssert(pn);
			
		}
        catch (...) 
        { 
        	delete(py); 
        	throw; 
        }
        px=py;
		sp_enable_shared_from_this(this,py,py);
        return *this;
    }
    
    ~shared_ptr() { dispose(); }
    
    void reset(T* p=0)
    {
        if ( px == p ) 
        	return;
        
        if ( pn == 0 || (pn != 0 && --(*pn) == 0) )
        { 
        	delete(px); 
        }
        else
        { 
        	// allocate new reference
            // counter
            // fix: prevent leak if new throws
            try 
            { 
            	pn = new size_type(1);
    			AMAssert(pn);
            }
            catch (...) 
            {
                // undo effect of —*pn above to
                // meet effects guarantee
                
            	++(*pn);
            	
                delete(p);
                throw;
            } // catch
        } // allocate new reference counter
        
        *pn = 1;
        px = p;

		if( px == 0){
			delete pn;
			pn = 0;
		}
    } 

    reference operator*() const throw(){ return *px; }
    pointer operator->() const throw(){ return px; }
    pointer get() const throw(){ return px; }
    size_type use_count() const throw()//
    {
    	if(pn == 0)
    		return 0;
    	else
    		return *pn; 
    }
    
    bool unique() const throw()//
    {
    	if(pn == 0)
    		return false;
    	else
    		return (*pn == 1); 
    }
    
private:
    void dispose() throw()
    {	
		int p = int(px);
		if( p == 0x00283610){
			int i = 0;
			i ++;
		}
		if ( pn!= 0 && --*pn == 0)
        { 
			delete px; 
			px = 0;
			delete pn;
			pn = 0;
        }
    }
    void increase(size_type *pn)
	{	
		int p = int(px);
		if( p == 0x001a5500){
			int i = 0;
			i ++;
		}
		if(pn != 0 && *(pn) != 0)
			++(*pn);   
	}
    T * px; 		// contained pointer
    size_type* pn; 	// reference counter
}; // shared_ptr

//template<class T,class Y>
//inline void sp_enable_shared_from_this( shared_ptr<T> * ppx, enable_shared_from_this< Y > const * pe)
//{
//	if( pe != 0 )
//	{
//		pe->_internal_accept_owner(ppx,pe);
//	}
//}
template< class X, class Y, class T > inline void sp_enable_shared_from_this( shared_ptr<X> const * ppx, Y const * py, enable_shared_from_this< T > const * pe )
{
	if( pe != 0 )
	{
		pe->_internal_accept_owner( ppx, py);
	}
}

inline void sp_enable_shared_from_this( ... )
{
}

template<class T, class U>
inline bool operator==(shared_ptr<T> const & l, shared_ptr<U> const & r)
{
    return l.get() == r.get();
}

template<class T, class U>
inline bool operator!=(shared_ptr<T> const & l, shared_ptr<U> const & r)
{
    return l.get() != r.get();
}

template<class T, class U> shared_ptr<T> static_pointer_cast(shared_ptr<U> const & r)
{	
	T * p = static_cast<T*>(r.get());
	shared_ptr<T>ret(r,p);
	return ret;
}
template<class T, class U> shared_ptr<T> static_pointer_cast(weak_ptr<U> const & r)
{	
	T * p = static_cast<T*>(r.get());
	shared_ptr<T>ret(r,p);
	return ret;
}
template<class T, class U> shared_ptr<T> dynamic_pointer_cast(shared_ptr<U> const & r)
{
	T * p = dynamic_cast<T*>(r.get());
	shared_ptr<T>ret(r,p);
	return ret;
}

template<class T>
bool operator < (const shared_ptr<T> left, const shared_ptr<T> right)
{
	return ((*left)<(*right));
}

#endif //_AM_SHARE_PTR_

