#include "AMGui.h"
__GUI_BEGIN_NAMESPACE

ByteArrayInputStream::ByteArrayInputStream( shared_ptr<VectorArray<unsigned char> > buf )
{
	this->buf = new VectorArray<unsigned char>(buf->size());
	memcpy(this->buf->getDataAddress(), buf->getDataAddress(), buf->size() * sizeof(unsigned));
	this->count = buf->size();
	this->pos = 0;
	this->mark_pos = 0;
}

ByteArrayInputStream::ByteArrayInputStream( shared_ptr<VectorArray<unsigned char> > buf, int off, int len )
{
	this->buf = new VectorArray<unsigned char>(buf->size());
	memcpy(this->buf->getDataAddress(), buf->getDataAddress(), buf->size() * sizeof(unsigned));
	this->count = (((len + off) > buf->size()) ? buf->size() : len + off);
	this->pos = off;
	this->mark_pos = off;
}

int ByteArrayInputStream::read()
{
	int reslut = -1;
	if (pos >= count)
	{
		AMAssert(0);
	}
	else
	{
		reslut = (*buf)[pos++];
	}
	return reslut;
}

int ByteArrayInputStream::read( shared_ptr<VectorArray<unsigned char> > b, int off, int len )
{
	if (pos >= count || b.get() == NULL || off < 0 || len < 0 || (len > b->size() - off) )
	{
		return -1;
	}
	else
	{
		int k = (len > (count - pos)) ? (count - pos) : len;
		memset(b->getDataAddress(), 0, off * sizeof(unsigned char));
		memcpy(b->getDataAddress() + off, buf->getDataAddress() + pos, k * sizeof(unsigned char));
		pos += k;
		return k;
	}
}

long ByteArrayInputStream::skip( long n )
{
	int k = (n > (count - pos)) ? (count - pos) : n;
	if (k < 0)
	{
		return 0;
	}
	pos += k;
	return k;
}

int ByteArrayInputStream::available()
{
	return (count - pos);
}

void ByteArrayInputStream::close()
{
	if (buf != NULL)
	{
		delete []buf;
		buf = NULL;
	}
}

void ByteArrayInputStream::mark( int readlimit )
{
	mark_pos = pos;
}

void ByteArrayInputStream::reset()
{
	pos = mark_pos;
}

bool ByteArrayInputStream::markSupported()
{
	return true;
}

ByteArrayInputStream::~ByteArrayInputStream()
{
	close();
}
__GUI_END_NAMESPACE
