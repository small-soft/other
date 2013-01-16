#ifndef _BYTEARRAYINPUTSTREAM_H_
#define _BYTEARRAYINPUTSTREAM_H_

#include "inc\InputStream.h"
#include "inc\Config.h"
__GUI_BEGIN_NAMESPACE

class InputStream;

class ByteArrayInputStream : public InputStream
{
private:
	VectorArray<unsigned char> *buf;
	int pos;
	int mark_pos;
	int count;

public:
	ByteArrayInputStream(shared_ptr<VectorArray<unsigned char> > buf);
	ByteArrayInputStream(shared_ptr<VectorArray<unsigned char> > buf, int off, int len);
	virtual ~ByteArrayInputStream();
public:
	virtual int read();
	virtual int read(shared_ptr<VectorArray<unsigned char> > b, int off, int len);
	virtual long skip(long n);
	virtual int available();
	virtual void close();
	virtual void mark(int readlimit);
	virtual void reset();
	virtual bool markSupported();
};

__GUI_END_NAMESPACE

#endif
