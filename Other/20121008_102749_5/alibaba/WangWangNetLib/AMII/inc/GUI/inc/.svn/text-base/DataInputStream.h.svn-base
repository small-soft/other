#ifndef _DATAINPUTSTREAM_H_
#define _DATAINPUTSTREAM_H_

#include "inc\InputStream.h"
#include "inc\Config.h"
__GUI_BEGIN_NAMESPACE

class DataInputStream :	public InputStream
{
public:
	DataInputStream::DataInputStream(AMFILE *file);
	virtual ~DataInputStream();

	static shared_ptr<InputStream> getInputStreamFromFile( char *fileName );

public:
	virtual int read();
	virtual void close();

public:
	shared_ptr<String> readUTF();
	short readShort();
	unsigned char readByte();
	int readInt();
	void readFully(shared_ptr<VectorArray<unsigned char> > b);
	void readFully(shared_ptr<VectorArray<unsigned char> > b, int off, int len);
	bool readBoolean();
	float readFloat();
	int readUnsignedShort();

private:
	AMFILE *mFile;
};
__GUI_END_NAMESPACE

#endif
