#include "AMGui.h"
#include "AMFS.h"
#include "AMAssert.h"
#include "math.h"

__GUI_BEGIN_NAMESPACE

DataInputStream::DataInputStream(AMFILE *file)
{
	mFile = file;
}

DataInputStream::~DataInputStream()
{
	close();
}

shared_ptr<InputStream> DataInputStream::getInputStreamFromFile( char *fileName )
{
	shared_ptr<InputStream> instream;

	AMFILE *file = AMFopen(fileName, "rb");
	if (file != NULL)
	{
		instream = new DataInputStream(file);
	}
	else
	{
		AMAssert(file);
	}

	return instream;
}

int DataInputStream::read()
{
	int c = AMFgetc(mFile);
	if (c == AME_ARG_AINVALID)
	{
		AMAssert(0);
		return 0;
		//c = -1;
	}
	else
	{
		return c;
	}
}

void DataInputStream::close()
{
	if(mFile != NULL)
	{
		AMFclose(mFile);	
		mFile = NULL;
	}
}

shared_ptr<String> DataInputStream::readUTF()
{
	//to-do
	int utfLen = readUnsignedShort();
	if (utfLen == 0)
	{
		return new String(L"");
	}

	shared_ptr<VectorArray<unsigned char> > array = new VectorArray<unsigned char>(utfLen);
	InputStream::read(array);

	unsigned char *bytearr = new unsigned char[utfLen + 1];
	char *chararr = new char[utfLen + 1];
	int index;
	for (index = 0; index < utfLen; ++index)
	{
		bytearr[index] = (*array)[index];
	}
	bytearr[index] = '\0';

	int c, char2, char3;
	int count = 0;
	int chararr_count=0;

	while (count < utfLen)
	{
		c = (int)bytearr[count] & 0xff;
		if (c > 127)
		{
			break;
		}
		count++;
		chararr[chararr_count++] = (char)c;
	}

	while (count < utfLen)
	{
		c = (int) bytearr[count] & 0xff;
		switch (c >> 4)
		{
		case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7:
			/* 0xxxxxxx */
			{
				count++;
				chararr[chararr_count++] = (char)c;
				break;
			}
		case 12: case 13:
			/* 110xxxxx   10xxxxxx */
			{
				count += 2;
				if (count > utfLen)
				{
					//exception
				}
				char2 = (int) bytearr[count - 1];
				if ((char2 & 0xC0) != 0x80)
				{
					//exception
				}
				chararr[chararr_count++]=(char)(((c & 0x1F) << 6) | (char2 & 0x3F));  
				break;
			}
		case 14:
			/* 1110xxxx  10xxxxxx  10xxxxxx */
			{
				count += 3;
				if (count > utfLen)
				{
					//exception
				}
				char2 = (int) bytearr[count - 2];
				char3 = (int) bytearr[count - 1];
				if (((char2 & 0xC0) != 0x80) || ((char3 & 0xC0) != 0x80))
				{
					//exception
				}
				chararr[chararr_count++] = (char)(((c & 0x0F) << 12) | ((char2 & 0x3F) << 6) | (char3 & 0x3F));
				break;
			}
		default:
			/* 10xxxxxx,  1111xxxx */
			{
				//exception
			}
		}

	}
	chararr[chararr_count] = '\0';

	int lenOfstrUni = AMAnsiToUnicode(chararr, -1, NULL, 0);
	shared_ptr<GUI_CHAR> strUni = new GUI_CHAR[lenOfstrUni];
	AMAnsiToUnicode(chararr, -1, strUni.get(), lenOfstrUni);
	delete []bytearr;
	delete []chararr;
	
	shared_ptr<String> resString = new String(strUni.get());
	return resString;
}

short DataInputStream::readShort()
{
	//exception
	int a = read();
	int b = read();
	return (short)((a << 8) | (b & 0xff));
}

unsigned char DataInputStream::readByte()
{
	return read();
}

int DataInputStream::readInt()
{
	int a = read();
	int b = read();
	int c = read();
	int d = read();
	return (((a & 0xff) << 24) | ((b & 0xff) << 16) | ((c & 0xff) << 8) | (d & 0xff));
}

void DataInputStream::readFully( shared_ptr<VectorArray<unsigned char> > b )
{
	int len = b->size();
	readFully(b, 0, len);
}

void DataInputStream::readFully( shared_ptr<VectorArray<unsigned char> > b, int off, int len )
{
	InputStream::read(b, off, len);
}

bool DataInputStream::readBoolean()
{
	int a = read();
	return !(a == 0);
}

float DataInputStream::readFloat()
{
	int bits = readInt();
	int s = ((bits >> 31) == 0) ? 1 : -1;
	int e = ((bits >> 23) & 0xff);
	int m = (e == 0) ? (bits & 0x7fffff) << 1 : (bits & 0x7fffff) | 0x800000;
	return (float)(s * m * pow((double)2.0, (int)e - 150));
}

int DataInputStream::readUnsignedShort()
{
	int a = read();
	int b = read();
	return (((a & 0xff) << 8) | (b & 0xff));
}
__GUI_END_NAMESPACE
