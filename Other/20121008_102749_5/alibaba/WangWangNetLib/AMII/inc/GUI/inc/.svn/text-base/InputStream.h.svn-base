#ifndef _INPUTSTREAM_H_
#define _INPUTSTREAM_H_

#include "inc\Config.h"
__GUI_BEGIN_NAMESPACE

class InputStream
{
public:
	InputStream();
	virtual ~InputStream() {}
public:
	virtual int read() = 0;
	virtual void close();
	
	virtual int read(shared_ptr<VectorArray<unsigned char> > b);
	virtual int read(shared_ptr<VectorArray<unsigned char> > b, int off, int len);
	virtual long skip(long n);
	virtual int available();
	virtual void mark(int readlimit);
	virtual void reset();
	virtual bool markSupported();
};
__GUI_END_NAMESPACE

#endif
