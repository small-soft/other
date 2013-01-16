#include "AMGui.h"
__GUI_BEGIN_NAMESPACE

Resources::Resources()
{
}
Resources::Resources(shared_ptr<InputStream> input)
{
	openFile(input);
}
void Resources::clear()
{
	majorVersion = 0;
	minorVersion = 0;
	resourceTypes.clear();
	resources.clear();
	input.reset();
}
void Resources::startingEntry(String id, unsigned char magic)
{
}
void Resources::openFile(shared_ptr<InputStream> input)
{
	clear();
	this->input = dynamic_pointer_cast<DataInputStream>(input);

	int resourceCount = this->input->readShort();
	if (resourceCount < 0)
	{
		return;
	}

	for(int iter = 0 ; iter < resourceCount ; iter++) 
	{
		unsigned char magic = this->input->readByte();
		String id = *(this->input->readUTF());
		startingEntry(id, magic);

		switch(magic) 
		{
		case MAGIC_HEADER:
			readHeader();
			continue;
		case MAGIC_THEME:
			setResource(id, MAGIC_THEME, loadTheme(id, magic == MAGIC_THEME));
			continue;
		case MAGIC_IMAGE:
			setResource(id, magic, createImage());
			continue;
		case MAGIC_FONT:
			setResource(id, magic, loadFont(this->input, id, false));
			continue;
		case MAGIC_DATA:
			setResource(id, magic, createData());
			continue;
		case MAGIC_L10N:
			setResource(id, magic, loadL10N());
			continue;

			// legacy file support to be removed
		case MAGIC_IMAGE_LEGACY:
			setResource(id, MAGIC_IMAGE, createImage());
			continue;
		case MAGIC_INDEXED_IMAGE_LEGACY:
			setResource(id, MAGIC_IMAGE, createPackedImage8());
			continue;
		case MAGIC_THEME_LEGACY:
			setResource(id, MAGIC_THEME, loadTheme(id, magic == MAGIC_THEME));
			continue;
		case MAGIC_FONT_LEGACY:
			setResource(id, MAGIC_FONT, loadFont(this->input, id, false));
			continue;
		case MAGIC_INDEXED_FONT_LEGACY:
			setResource(id, MAGIC_FONT, loadFont(this->input, id, true));
			continue;
		case MAGIC_ANIMATION_LEGACY:
			//to-do
			//setResource(id, MAGIC_IMAGE, loadAnimation(this->input));
			continue;
		default:
			return;
		}
	}
}
void Resources::readHeader()
{
	int size = this->input->readShort();
	majorVersion = this->input->readShort();
	minorVersion = this->input->readShort();

	int dataLen = this->input->readShort();
	metaData = new VectorArray<String>(dataLen);
	for(int iter = 0 ; iter < dataLen; iter++) 
	{
		metaData->elementAt(iter) = *(this->input->readUTF());
	}
}
int Resources::getMinorVersion()
{
	return minorVersion;
}
int Resources::getMajorVersion()
{
	return majorVersion;
}
shared_ptr<VectorArray<String> > Resources::getMetaData()
{
	return metaData;
}
shared_ptr<VectorArray<String> > Resources::getResourceNames()
{
	int lenOfTypes = resourceTypes.size();
	shared_ptr<VectorArray<String> > arr = new VectorArray<String>(lenOfTypes);
	Enumeration<String> e = resourceTypes.keys();
	for(int iter = 0 ; iter < lenOfTypes ; iter++) 
	{
		(*arr)[iter] = e.nextElement();
	}
	return arr;
}
shared_ptr<VectorArray<String> > Resources::getDataResourceNames()
{
	return getResourceTypeNames(MAGIC_DATA);
}
void Resources::setResource(String id, unsigned char type, shared_ptr<Object> value)
{
	if(value.get() == NULL) 
	{
		resources.remove(id);
		resourceTypes.remove(id);
	} else 
	{
		resources.put(id, value);
		resourceTypes.put(id, type);
	}
}
shared_ptr<VectorArray<String> > Resources::getL10NResourceNames()
{
	return getResourceTypeNames(MAGIC_L10N);
}
shared_ptr<VectorArray<String> > Resources::getFontResourceNames()
{
	shared_ptr<Vector<String> > vec = new Vector<String>();
	Enumeration<String> e = resourceTypes.keys();
	while(e.hasMoreElements()) 
	{
		String c = e.nextElement();
		if(isFont(c)) 
		{
			vec->addElement(c);
		}
	}
	return toStringArray(vec);;
}
shared_ptr<VectorArray<String> > Resources::getThemeResourceNames()
{
	shared_ptr<Vector<String> > vec = new Vector<String>();
	Enumeration<String> e = resourceTypes.keys();
	while(e.hasMoreElements()) 
	{
		String c = e.nextElement();
		if(isTheme(c)) 
		{
			vec->addElement(c);
		}
	}
	return toStringArray(vec);;
}
shared_ptr<VectorArray<String> > Resources::getImageResourceNames()
{
	shared_ptr<Vector<String> > vec = new Vector<String>();
	Enumeration<String> e = resourceTypes.keys();
	while(e.hasMoreElements()) 
	{
		String c = e.nextElement();
		if(isImage(c)) 
		{
			vec->addElement(c);
		}
	}
	return toStringArray(vec);;
}
shared_ptr<VectorArray<String> > Resources::getAnimationResourceNames() 
{
	return getResourceTypeNames(MAGIC_ANIMATION_LEGACY);
}
unsigned char Resources::getResourceType(String name)
{
	return resourceTypes.get(name);
}
shared_ptr<VectorArray<String> > Resources::getResourceTypeNames(unsigned char b)
{
	shared_ptr<Vector<String> > vec = new Vector<String>();
	Enumeration<String> e = resourceTypes.keys();
	while(e.hasMoreElements()) 
	{
		String c = e.nextElement();
		if(resourceTypes.get(c) == b) 
		{
			vec->addElement(c);
		}
	}
	return toStringArray(vec);
}
shared_ptr<VectorArray<String> > Resources::toStringArray(shared_ptr<Vector<String> > v)
{
	shared_ptr<VectorArray<String> > s = new VectorArray<String>(v->size());
	for(int iter = 0 ; iter < s->size() ; iter++) 
	{
		(*s)[iter] = v->elementAt(iter);
	}
	return s;
}
bool Resources::isL10N(String name)
{
	unsigned char b = resourceTypes.get(name);
	return b == MAGIC_L10N;
}
bool Resources::isTheme(String name)
{
	unsigned char b = resourceTypes.get(name);
	return b == MAGIC_THEME_LEGACY || b == MAGIC_THEME;
}
bool Resources::isFont(String name)
{
	unsigned char b = resourceTypes.get(name);
	return b == MAGIC_FONT || b == MAGIC_FONT_LEGACY || b == MAGIC_INDEXED_FONT_LEGACY;
}
bool Resources::isAnimation(String name)
{
	unsigned char b = resourceTypes.get(name);
	return b == MAGIC_ANIMATION_LEGACY;
}
bool Resources::isData(String name)
{
	unsigned char b = resourceTypes.get(name);
	return b == MAGIC_DATA;
}
bool Resources::isImage(String name)
{
	unsigned char b = resourceTypes.get(name);
	return b == MAGIC_IMAGE_LEGACY || b == MAGIC_ANIMATION_LEGACY || b == MAGIC_INDEXED_IMAGE_LEGACY || b == MAGIC_IMAGE;
}
shared_ptr<Resources> Resources::open(String resource)
{
	shared_ptr<String> fileName = new String(resource);
	shared_ptr<InputStream> is = Display::getInstance()->getResourceAsStream(fileName);
	shared_ptr<Resources> r = new Resources(is);
	is->close();
	return r;
}
shared_ptr<Resources> Resources::open(shared_ptr<InputStream> resource)
{
	return new Resources(resource);
}
shared_ptr<Image> Resources::getImage(String id)
{
	shared_ptr<Object> obj = resources.get(id);
	shared_ptr<Image> img = dynamic_pointer_cast<Image>(obj);

	EncodedImage *eImg = dynamic_cast<EncodedImage *>(img.get());
	if (NULL != eImg)
	{
		shared_ptr<EncodedImage> eimg = dynamic_pointer_cast<EncodedImage>(img);
		img = eimg->getBMPImage();
	}
	return img;
}
shared_ptr<InputStream> Resources::getData(String id)
{
	shared_ptr<VectorArray<unsigned char> > vec = dynamic_pointer_cast<VectorArray<unsigned char> >(resources.get(id));
	return new ByteArrayInputStream(vec);
}
shared_ptr<Map< String, shared_ptr<Object> > > Resources::getL10N(String id, String locale)
{
	//to check
	shared_ptr<Object> obj = resources.get(id);
	shared_ptr<Map< String, shared_ptr< Map< String, shared_ptr<Object> > > > > l10n = 
							dynamic_pointer_cast<Map< String, shared_ptr< Map< String, shared_ptr<Object> > > > >(obj);
	
	return l10n->get(locale);
}
Enumeration<String> Resources::listL10NLocales(String id)
{
	//to check
	shared_ptr<Object> obj = resources.get(id);
	shared_ptr<Map<String, String> > l10n = dynamic_pointer_cast<Map<String, String> >(obj);
	return l10n->keys();
}
shared_ptr<Font> Resources::getFont(String id)
{
	shared_ptr<Object> obj = resources.get(id);
	shared_ptr<Font> font = dynamic_pointer_cast<Font>(obj);
	return font;
}
shared_ptr<Map<String, shared_ptr<Object> > > Resources::getTheme(String id)
{
	shared_ptr<Object> obj = resources.get(id);
	shared_ptr<Map<String, shared_ptr<Object> > > h = dynamic_pointer_cast<Map<String, shared_ptr<Object> > >(obj);

	// theme can be null in valid use cases such as the resource editor
	if(!h->isEmpty() && h->containsKey(L"uninitialized")) 
	{
		Enumeration<String> e = h->keys();
		while(e.hasMoreElements()) 
		{
			String key = e.nextElement();
			if(key.endsWith(L"font") || (key.endsWith((L"Image")) && !key.endsWith(L"scaledImage"))) 
			{
				shared_ptr<Object> value = h->get(key);
				if(value.get() == NULL) 
				{
					//exception
					//throw new IllegalArgumentException("Couldn't find resource: " + key);
					shared_ptr<Map<String, shared_ptr<Object> > > h;
					return h;
				}

				// the resource was not already loaded when we loaded the theme
				// it must be loaded now so we can resolve the temporary name
				String *str = dynamic_cast<String *>(value.get());
				if (NULL != str)
				{
					shared_ptr<Object> o = resources.get(*str);
					if(o.get() == NULL)
					{
						//exception
						//throw new IllegalArgumentException("Theme entry for " + key + " could not be found: " + value);
						shared_ptr<Map<String, shared_ptr<Object> > > h;
						return h;
					}

					h->put(key, o);
				}
			}
			// if this is a border we might need to do additional work for older versions
			// of LWUIT and for the case of an image border where the images might not have
			// been loaded yet when the border was created
			if(key.endsWith(L"order")) 
			{
				shared_ptr<Border> b = confirmBorder(h, key);
				if(majorVersion == 0 && minorVersion == 0) 
				{
					b->setPressedInstance(confirmBorder(h, key + L"Pressed"));
					b->setFocusedInstance(confirmBorder(h, key + L"Focused"));
					h->remove(key + L"Pressed");
					h->remove(key + L"Focused");
				}
				h->put(key, b);
			}
		}
		h->remove(L"uninitialized");
	}
	return h;
}
shared_ptr<Border> Resources::confirmBorder(shared_ptr<Map<String, shared_ptr<Object> > > h, String key)
{
	shared_ptr<Object> val = h->get(key);
	if(val.get() == NULL) 
	{
		//exception
		shared_ptr<Border> border;
		return border;
	}
	Border *b = dynamic_cast<Border *>(val.get());
	if (NULL == b)
	{
		shared_ptr<Vector<String> > value = dynamic_pointer_cast<Vector<String> >(val);
		if(value.get() == NULL) 
		{
			//exception
			//throw new IllegalArgumentException("Couldn't find resource: " + key);
			shared_ptr<Border> res;
			return res;
		}

		// the resource was not already loaded when we loaded the theme
		// it must be loaded now so we can resolve the temporary name
		shared_ptr<Border> imageBorder = createImageBorder(value);
		return imageBorder;
	}

	return dynamic_pointer_cast<Border>(val);
}
shared_ptr<Border> Resources::createImageBorder(shared_ptr<Vector<String> > value)
{
	int lenOfImages = value->size();
	shared_ptr<VectorArray<shared_ptr<Image> > > images = new VectorArray<shared_ptr<Image> >(lenOfImages);

	for(int iter = 0 ; iter < lenOfImages; iter++) 
	{
		shared_ptr<Object> obj = resources.get((*value)[iter]);
		shared_ptr<Image> img = dynamic_pointer_cast<Image>(obj);
		(*images)[iter] = img;
	}
	shared_ptr<Image> img = new Image();
	switch(lenOfImages)
	{
	case 2:
		return Border::createImageBorder((*images)[0], (*images)[1], img); 
	case 3:
		return Border::createImageBorder((*images)[0], (*images)[1], (*images)[2]); 
	case 8:
		return Border::createImageBorder((*images)[0], (*images)[1], (*images)[2],
			(*images)[3], (*images)[4], (*images)[5], (*images)[6], (*images)[7], img); 
	default:
		return Border::createImageBorder((*images)[0], (*images)[1], (*images)[2],
			(*images)[3], (*images)[4], (*images)[5], (*images)[6], (*images)[7], (*images)[8]); 
	}
}
shared_ptr<Object> Resources::getResourceObject(String res)
{
	return resources.get(res);
}
shared_ptr<Image> Resources::createImage()
{
	if(majorVersion == 0 && minorVersion == 0) 
	{
		int lenOfData = this->input->readInt();
		shared_ptr<VectorArray<unsigned char> > data = new VectorArray<unsigned char>(lenOfData);
		this->input->readFully(data, 0, lenOfData);
		return EncodedImage::create(data);
	}
	else 
	{
		int type = this->input->readByte() & 0xff;
		switch(type) 
		{
		// PNG file
		case 0xf1:

		// JPEG File
		case 0xf2:
			//byte[] data = new byte[input.readInt()];
			{
				int len = this->input->readInt();
				shared_ptr<VectorArray<unsigned char> > data = new VectorArray<unsigned char>(len);
				this->input->readFully(data, 0, len);
				return EncodedImage::create(data);
			}

		// Indexed image
		case 0xf3:
			return createPackedImage8();

		// animation
		case 0xf4:
			//to-do
			//return loadAnimation(input);

		// SVG
		case 0xf5:
			{
				int svgSize = this->input->readInt();
				if(Image::isSVGSupported()) 
				{
					//byte[] s = new byte[svgSize];
					shared_ptr<VectorArray<unsigned char> > s = new VectorArray<unsigned char>(svgSize);
					this->input->readFully(s, 0, svgSize);

					shared_ptr<String> baseURL = this->input->readUTF();
					bool animated = this->input->readBoolean();					
					this->input->readFloat();
					this->input->readFloat();
					
					//byte[] fallback = new byte[input.readInt()];
					int lenOfFallback = this->input->readInt();
					shared_ptr<VectorArray<unsigned char> > fallback = new VectorArray<unsigned char>(lenOfFallback);
					if(lenOfFallback > 0) 
					{
						this->input->readFully(fallback, 0, lenOfFallback);
					}

					return Image::createSVG(baseURL, animated, *s);
				} 
				else 
				{
					/*
					svgSize -= input.skip(svgSize);
					while(svgSize > 0) 
					{
						svgSize -= input.skip(svgSize);
					}
					*/
					svgSize -= this->input->skip(svgSize);
					while(svgSize > 0) 
					{
						svgSize -= this->input->skip(svgSize);
					}

					// read the base url, the animated property and screen ratios to skip them as well...
					this->input->readUTF();
					this->input->readBoolean();
					this->input->readFloat();
					this->input->readFloat();

					//byte[] fallback = new byte[input.readInt()];
					int lenOfFallback = this->input->readInt();
					shared_ptr<VectorArray<unsigned char> > fallback = new VectorArray<unsigned char>(lenOfFallback);
					this->input->readFully(fallback, 0, lenOfFallback);

					return EncodedImage::create(fallback);                      
				}
			}
			// Fail this is the wrong data type
		default:
			//exception
			//throw new IOException("Illegal type while creating image: " + Integer.toHexString(type));
			shared_ptr<Image> img;
			return img;
		}
	}
}
shared_ptr<VectorArray<unsigned char> > Resources::createData()
{
	//byte[] data = new byte[input.readInt()];
	int lenOfData = this->input->readInt();
	shared_ptr<VectorArray<unsigned char> > data = new VectorArray<unsigned char>(lenOfData);
	this->input->readFully(data, 0, lenOfData);
	return data;
}
shared_ptr<Font> Resources::loadFont(shared_ptr<DataInputStream> input, String id, bool packed)
{
	if(majorVersion == 0 && minorVersion == 0) 
	{
		shared_ptr<Image> bitmap;
		if(packed) 
		{
			bitmap = createPackedImage8();
		}
		else
		{
			bitmap = createImage();
		}

		int charCount = input->readShort();
		shared_ptr<VectorArray<int> > cutOffsets = new VectorArray<int>(charCount);
		shared_ptr<VectorArray<int> > charWidth = new VectorArray<int>(charCount);

		for(int iter = 0 ; iter < charCount ; iter++) 
		{
			(*cutOffsets)[iter] = input->readShort();
			(*charWidth)[iter] = input->readByte();
		}
		shared_ptr<String> strCharset = input->readUTF();
		shared_ptr<String> strID = new String(id);
		shared_ptr<Font> old = Font::getBitmapFont(strID);
		if(old.get() != NULL) 
		{
			return old;
		}
		return Font::createBitmapFont(strID, bitmap, cutOffsets, charWidth, strCharset);
	}

	// read a system font fallback
	int fallback = input->readByte() & 0xff;

	// do we have an emedded truetype font? Do we support embedded fonts?
	bool trueTypeIncluded = input->readBoolean();
	shared_ptr<Font> font;
	if(trueTypeIncluded) 
	{
		int size = input->readInt();
		if(Font::isTrueTypeFileSupported()) 
		{
			shared_ptr<InputStream> in = dynamic_pointer_cast<InputStream>(input);
			font = Font::createTrueTypeFont(in);
		} 
		else
		{
			while(size > 0) 
			{
				size -= input->skip(size);
			}
		}
	}

	bool lookupIncluded = input->readBoolean();
	if(lookupIncluded) 
	{
		shared_ptr<String> str = input->readUTF();
		if(font.get() == NULL && Font::isCreationByStringSupported()) 
		{
			font = Font::create(str);
		}
	}

	bool bitmapIncluded = input->readBoolean();
	if(bitmapIncluded) 
	{
		font = loadBitmapFont(input, id, font);
	}

	if(font.get() != NULL) 
	{
		return font;
	}
	return Font::createSystemFont(fallback & (Font::FACE_MONOSPACE | Font::FACE_PROPORTIONAL | Font::FACE_SYSTEM), fallback & (Font::STYLE_BOLD | Font::STYLE_ITALIC | Font::STYLE_PLAIN | Font::STYLE_UNDERLINED), fallback & (Font::SIZE_LARGE | Font::SIZE_MEDIUM| Font::SIZE_SMALL));
}
shared_ptr<Font> Resources::loadBitmapFont(shared_ptr<DataInputStream> input, String id, shared_ptr<Font> font )
{
	shared_ptr<Image> bitmap = createImage();

	int charCount = input->readShort();
	shared_ptr<VectorArray<int> > cutOffsets = new VectorArray<int>(charCount);
	shared_ptr<VectorArray<int> > charWidth = new VectorArray<int>(charCount);

	for(int iter = 0 ; iter < charCount ; iter++) 
	{
		(*cutOffsets)[iter] = input->readShort();
	}
	for(int iter = 0 ; iter < charCount ; iter++) 
	{
		(*charWidth)[iter] = input->readByte();
	}

	shared_ptr<String> strCharset = input->readUTF();
	input->readByte();

	if(font.get() == NULL) 
	{
		if(Font::isBitmapFontEnabled()) 
		{
			shared_ptr<String> strID = new String(id);
			shared_ptr<Font> old = Font::getBitmapFont(strID);
			if(old.get() != NULL) 
			{
				// Returning bitmap font from cache, to prevent collision with an
				// old resource file use Font.clearBitmapCache()
				return old;
			}
			return Font::createBitmapFont(strID, bitmap, cutOffsets, charWidth, strCharset);
		}
	}
	return font;
}

shared_ptr<Map<String, shared_ptr<Object> > > Resources::loadTheme( String id, bool newerVersion )
{
	shared_ptr<Map<String, shared_ptr<Object> > > theme = new Map<String, shared_ptr<Object> >();

	shared_ptr<String> str = new String(id);
	shared_ptr<Object> obj = dynamic_pointer_cast<Object>(str);
	theme->put(L"name", obj);
	
	// marks the theme as uninitialized so we can finish "wiring" cached resources
	shared_ptr<String> strTrue = new String(L"TRUE");
	obj = dynamic_pointer_cast<Object>(strTrue);
	theme->put(L"uninitialized", obj);//to check

	int size = this->input->readShort();
	for(int iter = 0 ; iter < size ; iter++) 
	{
		String key = *(this->input->readUTF());

		// if this is a simple numeric value
		if(key.endsWith(L"Color")) 
		{
			int num = this->input->readInt();

			//trans dec to hex
			shared_ptr<Vector<unsigned char> > hexStr = new Vector<unsigned char>();
			char mapchar[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

			unsigned char ch;
			int count = 0;

			ch = mapchar[num % 16];
			num /= 16;
			hexStr->addElement(ch);

			while (num)
			{
				ch = mapchar[num % 16];
				num /= 16;
				hexStr->insertElementAt(ch, 0);
			}

			obj = dynamic_pointer_cast<Object>(hexStr);
			theme->put(key, obj);
			continue;
		} 

		// if this is a short numeric value for transparency
		if(key.endsWith(L"ransparency")) 
		{
			unsigned char b = (this->input->readByte() & 0xff);
			shared_ptr<Vector<unsigned char> > vec= new Vector<unsigned char>();
			vec->addElement(b);
			obj = dynamic_pointer_cast<Object>(vec);
			theme->put(key, obj);
			continue;
		} 

		// if this is a padding or margin then we will have the 4 values as bytes
		if(key.endsWith(L"adding") || key.endsWith(L"argin")) 
		{
			//to check (unsigned char => GUI_CHAR)
			unsigned char p1 = this->input->readByte() & 0xff;
			unsigned char p2 = this->input->readByte() & 0xff;
			unsigned char p3 = this->input->readByte() & 0xff;
			unsigned char p4 = this->input->readByte() & 0xff;
			shared_ptr<Vector<unsigned char> > vec= new Vector<unsigned char>();
			vec->addElement(p1);
			vec->addElement(p2);
			vec->addElement(p3);
			vec->addElement(p4);
			obj = dynamic_pointer_cast<Object>(vec);			
			theme->put(key, obj);
			continue;
		}

		// border
		if(key.endsWith(L"order")) 
		{
			if(majorVersion == 0 && minorVersion == 0) 
			{
				theme->put(key, createBorder(input, newerVersion));

				if(newerVersion) 
				{
					if(this->input->readBoolean()) 
					{
						theme->put(key + L"Pressed", createBorder(input, true));
					}
					if(this->input->readBoolean()) 
					{
						theme->put(key + L"Focused", createBorder(input, true));
					}
				}
			} 
			else
			{
				int borderType = this->input->readShort() & 0xffff;
				shared_ptr<Object> b = createBorder(input, borderType);
				theme->put(key, b);
			}
			continue;
		}

		// if this is a font
		if(key.endsWith(L"ont")) 
		{
			shared_ptr<Font> f;

			// is this a new font?
			if(this->input->readBoolean()) 
			{
				shared_ptr<String> fontId = this->input->readUTF();
				shared_ptr<Object> obj = resources.get(*fontId);
				f = dynamic_pointer_cast<Font>(obj);

				// if the font is not yet loaded
				if(f.get() == NULL) 
				{
					obj = dynamic_pointer_cast<Object>(fontId);
					theme->put(key, obj);
					continue;
				}
			} 
			else
			{
				f = Font::createSystemFont(this->input->readByte(), this->input->readByte(), this->input->readByte());
			}
			obj = dynamic_pointer_cast<Object>(f);
			theme->put(key, obj);
			continue;
		} 

		// the background property
		if(key.endsWith(L"ackground")) 
		{
			unsigned char type = this->input->readByte() & 0xff;
			int pos = key.indexOf(L'.');
			if(pos > -1) 
			{
				key = key.substr(0, pos);
			} 
			else 
			{
				key = L"";
			}
			shared_ptr<Vector<unsigned char> > vec= new Vector<unsigned char>();
			vec->addElement(type);
			obj = dynamic_pointer_cast<Object>(vec);
			theme->put(key + Style::BACKGROUND_TYPE, obj);

			switch(type) 
			{
			// Scaled Image
			case 0xF1:
			// Tiled Both Image
			case 0xF4:
				// the image name coupled with the type
				{
					shared_ptr<String> name = this->input->readUTF();
					obj = dynamic_pointer_cast<Object>(name);
					theme->put(key + Style::BG_IMAGE, obj);
					break;
				}

			// Aligned Image
			case 0xF5:
			// Tiled Vertically Image
			case 0xF2:
			// Tiled Horizontally Image
			case 0xF3:
				{
					// the image name coupled with the type and with alignment information
					shared_ptr<String> imageName = this->input->readUTF();
					obj = dynamic_pointer_cast<Object>(imageName);
					theme->put(key + Style::BG_IMAGE, obj);

					unsigned char align = this->input->readByte();
					shared_ptr<Vector<unsigned char> > vec= new Vector<unsigned char>();
					vec->addElement(align);
					obj = dynamic_pointer_cast<Object>(vec);
					theme->put(key + Style::BACKGROUND_ALIGNMENT, obj);
	
					break;
				}

			// Horizontal Linear Gradient
			case 0xF6:
			// Vertical Linear Gradient
			case 0xF7:
				{
					shared_ptr<Vector<float> > vec = new Vector<float>();
					vec->addElement((float)this->input->readInt());
					vec->addElement((float)this->input->readInt());
					vec->addElement(0.5f);
					vec->addElement(0.5f);
					vec->addElement(1.0f);
					obj = dynamic_pointer_cast<Object>(vec);
					theme->put(key + Style::BACKGROUND_GRADIENT, obj);
					break;
				}

			// Radial Gradient
			case 0xF8:
				{
					int c1  = this->input->readInt();
					int c2 = this->input->readInt();
					float f1 = this->input->readFloat();
					float f2 = this->input->readFloat();
					float radialSize = 1.0f;
					if(minorVersion > 1) 
					{
						radialSize = this->input->readFloat();
					}
					shared_ptr<Vector<float> > vec = new Vector<float>();
					vec->addElement((float)c1);
					vec->addElement((float)c2);
					vec->addElement(f1);
					vec->addElement(f2);
					vec->addElement(radialSize);
					obj = dynamic_pointer_cast<Object>(vec);
					theme->put(key + Style::BACKGROUND_GRADIENT, obj);
					break;
				}
			}
			continue;
		}

		// if this is a background image bgImage
		if(key.endsWith(L"bgImage")) 
		{
			shared_ptr<String> imgStr = this->input->readUTF();
			shared_ptr<Object> obj = resources.get(*imgStr);
			shared_ptr<Image> i = dynamic_pointer_cast<Image>(obj);

			// if the font is not yet loaded
			if(i.get() == NULL) 
			{
				obj = dynamic_pointer_cast<Object>(imgStr);
				theme->put(key, obj);
				continue;
			}
			obj = dynamic_pointer_cast<Object>(i);
			theme->put(key, obj);
			continue;
		} 

		if(key.endsWith(L"scaledImage")) 
		{
			if(this->input->readBoolean())
			{
				shared_ptr<String> strT = new String(L"true");
				obj = dynamic_pointer_cast<Object>(strT);
				theme->put(key, obj);
			} 
			else
			{
				shared_ptr<String> strF = new String(L"false");
				obj = dynamic_pointer_cast<Object>(strF);
				theme->put(key, obj);
			}
			continue;
		}

		if(key.endsWith(Style::BACKGROUND_TYPE) || key.endsWith(Style::BACKGROUND_ALIGNMENT)) 
		{
			unsigned char b = this->input->readByte();
			shared_ptr<Vector<unsigned char> > vec= new Vector<unsigned char>();
			vec->addElement(b);
			obj = dynamic_pointer_cast<Object>(vec);
			theme->put(key, obj);
			continue;
		}

		if(key.endsWith(Style::BACKGROUND_GRADIENT)) 
		{
			if(minorVersion < 2) 
			{	
				shared_ptr<Vector<float> > vector = new Vector<float>();
				vector->addElement((float)this->input->readInt());
				vector->addElement((float)this->input->readInt());
				vector->addElement(this->input->readFloat());
				vector->addElement(this->input->readFloat());
				obj = dynamic_pointer_cast<Object>(vector);
				theme->put(key, obj);
			}
			else 
			{
				shared_ptr<Vector<float> > vector = new Vector<float>();
				vector->addElement((float)this->input->readInt());
				vector->addElement((float)this->input->readInt());
				vector->addElement(this->input->readFloat());
				vector->addElement(this->input->readFloat());
				vector->addElement(this->input->readFloat());
				obj = dynamic_pointer_cast<Object>(vector);
				theme->put(key, obj);
			}
			continue;
		}
		//exception
		// thow an exception no idea what this is
		//throw new IOException("Error while trying to read theme property: " + key);
	}
	return theme;
}

shared_ptr<Object> Resources::createBorder(shared_ptr<DataInputStream> input, int type )
{
	switch(type) 
	{
	// empty border
	case 0xff01:
		return dynamic_pointer_cast<Object>(Border::getEmpty());

	// Line border
	case 0xff02:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createLineBorder(this->input->readByte()));
		} 
		else 
		{
			return dynamic_pointer_cast<Object>(Border::createLineBorder(this->input->readByte(), input->readInt()));
		}

	// Rounded border
	case 0xff03:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createRoundBorder(this->input->readByte(), this->input->readByte()));
		} 
		else
		{
			return dynamic_pointer_cast<Object>(Border::createRoundBorder(this->input->readByte(), this->input->readByte(), input->readInt()));
		}

	// Etched Lowered border
	case 0xff04:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createEtchedLowered());
		}
		else 
		{
			return dynamic_pointer_cast<Object>(Border::createEtchedLowered(this->input->readInt(), this->input->readInt()));
		}

	// Etched raised border
	case 0xff05:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createEtchedRaised());
		} 
		else 
		{
			return dynamic_pointer_cast<Object>(Border::createEtchedRaised(this->input->readInt(), this->input->readInt()));
		}

	// Bevel raised
	case 0xff07:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createBevelRaised());
		}
		else 
		{
			return dynamic_pointer_cast<Object>(Border::createBevelRaised(this->input->readInt(), this->input->readInt(), this->input->readInt(), this->input->readInt()));
		}

	// Bevel lowered
	case 0xff06:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createBevelLowered());
		} 
		else
		{
			return dynamic_pointer_cast<Object>(Border::createBevelLowered(this->input->readInt(), this->input->readInt(), this->input->readInt(), this->input->readInt()));
		}

	// Image border
	case 0xff08:
		{
			//Object[] imageBorder = readImageBorder(input);
			shared_ptr<VectorArray<String> > img = readImageBorder(input);
			shared_ptr<Object> imageBorder = dynamic_pointer_cast<Object>(img);
			return imageBorder;
		}
	}
	shared_ptr<Object> obj;
	return obj;
}

shared_ptr<Object> Resources::createBorder( shared_ptr<DataInputStream> input, bool newerVersion )
{
	int type = input->readByte();
	switch(type) 
	{
	case BORDER_TYPE_EMPTY:
		return dynamic_pointer_cast<Object>(Border::getEmpty());
	case BORDER_TYPE_LINE:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createLineBorder(input->readByte()));
		}
		else
		{
			return dynamic_pointer_cast<Object>(Border::createLineBorder(this->input->readByte(), input->readInt()));
		}
	case BORDER_TYPE_ROUNDED:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createRoundBorder(this->input->readByte(), this->input->readByte()));
		}
		else
		{
			return dynamic_pointer_cast<Object>(Border::createRoundBorder(this->input->readByte(), this->input->readByte(), this->input->readInt()));
		}
	case BORDER_TYPE_ETCHED_LOWERED:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createEtchedLowered());
		}
		else
		{
			return dynamic_pointer_cast<Object>(Border::createEtchedLowered(this->input->readInt(), this->input->readInt()));
		}
	case BORDER_TYPE_ETCHED_RAISED:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createEtchedRaised());
		}
		else
		{
			return dynamic_pointer_cast<Object>(Border::createEtchedRaised(this->input->readInt(), this->input->readInt()));
		}
	case BORDER_TYPE_BEVEL_RAISED:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createBevelRaised());
		}
		else
		{
			return dynamic_pointer_cast<Object>(Border::createBevelRaised(this->input->readInt(), this->input->readInt(), this->input->readInt(), this->input->readInt()));
		}
	case BORDER_TYPE_BEVEL_LOWERED:
		// use theme colors?
		if(input->readBoolean()) 
		{
			return dynamic_pointer_cast<Object>(Border::createBevelLowered());
		}
		else
		{
			return dynamic_pointer_cast<Object>(Border::createBevelLowered(this->input->readInt(), this->input->readInt(), this->input->readInt(), this->input->readInt()));
		}
	case BORDER_TYPE_IMAGE:
		{
			//Object[] imageBorder = readImageBorder(input);
			shared_ptr<VectorArray<String> > img = readImageBorder(input);
			shared_ptr<Object> imageBorder = dynamic_pointer_cast<Object>(img);

			if(!newerVersion) 
			{
				// legacy issue...
				input->readBoolean();
			}

			return imageBorder;
		}
	}
	shared_ptr<Object> obj;
	return obj;
}

shared_ptr<VectorArray<String> > Resources::readImageBorder( shared_ptr<DataInputStream> input )
{
	// Read number of images can be 2, 3, 8 or 9
	int size = input->readByte();
	shared_ptr<VectorArray<String> > imageBorder = new VectorArray<String>(size);

	for(int iter = 0 ; iter < size ; iter++) 
	{
		(*imageBorder)[iter] = *(input->readUTF());
	}
	return imageBorder;
}

shared_ptr<Map<String, shared_ptr<Map<String, shared_ptr<Object> > > > > Resources::loadL10N()
{
	shared_ptr<Map<String, shared_ptr<Map<String, shared_ptr<Object> > > > > l10n = new Map<String, shared_ptr<Map<String, shared_ptr<Object> > > >();

	int keys = this->input->readShort();
	int languages = this->input->readShort();
	shared_ptr<VectorArray<String> > keyArray = new VectorArray<String>(keys);
	for(int iter = 0 ; iter < keys ; iter++) 
	{
		(*keyArray)[iter] = *(this->input->readUTF());
	}
	for(int iter = 0 ; iter < languages ; iter++) 
	{     
		shared_ptr<Map<String, shared_ptr<Object> > > currentLanguage = new Map<String, shared_ptr<Object> >();
		String lang =  *(this->input->readUTF());
		l10n->put(lang, currentLanguage);
		for(int valueIter =  0 ; valueIter < keys ; valueIter++) 
		{
			shared_ptr<String> inputStr = this->input->readUTF();
			currentLanguage->put((*keyArray)[valueIter],  inputStr);
		}
	}
	return l10n;
}

shared_ptr<Image> Resources::createPackedImage8()
{
	// read the length of the palette;
	int size =  this->input->readByte() & 0xff;

	// 0 means the last bit overflowed, there is no sense for 0 sized palette
	if(size == 0) 
	{
		size = 256;
	}
	shared_ptr<VectorArray<int> > palette = new VectorArray<int>(size);

	for(int iter = 0 ; iter < palette->size() ; iter++) 
	{
		(*palette)[iter] =  this->input->readInt();
	}
	int width =  this->input->readShort();
	int height =  this->input->readShort();

	shared_ptr<VectorArray<unsigned char> > data = new VectorArray<unsigned char>(width * height);
	this->input->readFully(data, 0, data->size());
	return Image::createIndexed(width, height, palette, data);
}
__GUI_END_NAMESPACE
