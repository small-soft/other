#include "AMGui.h"
__GUI_BEGIN_NAMESPACE

InputStream::InputStream()
{
}

int InputStream::read( shared_ptr<VectorArray<unsigned char> > b )
{
	return read(b, 0, b->size());
}

int InputStream::read( shared_ptr<VectorArray<unsigned char> > b, int off, int len )
{
	if (b.get() == NULL) 
	{
		//exception
	} 
	else
	{
		if (off < 0 || len < 0 || len > b->size() - off) 
		{
			//exception
		}
		else
		{
			if (len == 0) 
			{
				return 0;
			}
		}
	}

	int i;
	for (i = 0; i < len ; i++) 
	{
		int c = read();
		if (c == -1)
		{
			if ( i == 0 )
			{
				return -1;
			}
			else
			{
				break;
			}
		}
		(*b)[off + i] = (unsigned char)c;
	}

	return i;
}

long InputStream::skip( long n )
{
	long remaining = n;
	int nr;

	if (n <= 0) 
	{
		return 0;
	}

	while (remaining > 0) 
	{
		nr = read();
		if (nr < 0) 
		{
			break;
		}
		remaining--;
	}

	return n - remaining;
}

int InputStream::available()
{
	int nr;
	int available_count = 0;

	while (1) 
	{
		nr = read();
		if (nr < 0) 
		{
			break;
		}
		available_count++;
	}
	return available_count;
}

void InputStream::close()
{
}

void InputStream::mark( int readlimit )
{
}

void InputStream::reset()
{
}

bool InputStream::markSupported()
{
	return false;
}
__GUI_END_NAMESPACE
