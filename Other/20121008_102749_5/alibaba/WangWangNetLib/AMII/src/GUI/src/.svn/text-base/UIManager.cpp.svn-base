#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

shared_ptr<UIManager> UIManager::instance;
bool UIManager::accessible = true;
UIManager::UIManager()
{	
	shared_ptr<DefaultLookAndFeel> temp = new DefaultLookAndFeel();
	current = temp;
	styles = new Map<String,shared_ptr<Style> >;
	selectedStyles = new Map<String,shared_ptr<Style> >;
	themeProps = new Map<String,shared_ptr<Object> >;
	defaultStyle = new Style();
	defaultSelectedStyle = new Style();
	imageCache = new Map<String,shared_ptr<Image> >;
	resetThemeProps();
}
UIManager::~UIManager()
{
	
}
void UIManager::deinitialize()
{
	instance.reset();
}
shared_ptr<UIManager> UIManager::getInstance()
{
	if(instance.get() == NULL)
	{
		instance = new UIManager();
	}
	 return instance;
}

shared_ptr<LookAndFeel> UIManager::getLookAndFeel()
{
	 return current;
}

void UIManager::setLookAndFeel( shared_ptr<LookAndFeel> plaf )
{
	current->uninstall();
	current = plaf;
}

void UIManager::setComponentStyle(const String& id, shared_ptr<Style> style )
{	
	String strID(id);
	if(strID.size() == 0){
		//if no id return the default style
		String nullString(L"");
		strID = nullString;
	} else {
		strID = (strID + L".");
	}
	styles->put(strID, style);
}

void UIManager::setComponentSelectedStyle( const String& id, shared_ptr<Style> style )
{	
	String strID(id);
	if(strID.size() == 0){
		//if no id return the default style
		String nullString(L"");
		strID = nullString;
	} else {
		strID = (strID + L".");
	}
	selectedStyles->put(strID, style);
}

shared_ptr<Style> UIManager::getComponentStyle( const String& id )
{
	 String str = L"";
	 return getComponentStyleImpl(id, false, str);
}

shared_ptr<Style> UIManager::getComponentSelectedStyle( const String& id )
{
	String str =L"sel#";
	return getComponentStyleImpl(id, true, str);
}

shared_ptr<Style> UIManager::getComponentCustomStyle( const String& id, const String& type )
{
	 String str(L"#");
	 String tmpStr = type + str;
		 
	 return getComponentStyleImpl(id, false, tmpStr);
}

shared_ptr<Style> UIManager::getComponentStyleImpl( const String& id, bool selected, const String& prefix )
{
	shared_ptr<Style> style;
	String strID(id);

	if(/*strID == NULL ||*/strID.length() == 0){
		//if no id return the default style
		String nullString(L"");
		strID = nullString;
	}else{
		strID = (strID + L".");
	}

	if(selected) {
		style = selectedStyles->get(strID);

		if(style.get() == NULL){
			style = createStyle(strID, prefix, true);
			selectedStyles->put(strID, style);
		}
	} else {
		if(((String)prefix).size() == 0) {
			style = styles->get(strID);

			if(style.get() == NULL) {
				style = createStyle(strID, prefix, false);
				styles->put(strID, style);
			}
		} else {
			return createStyle(strID, prefix, false);
		}
	}

	shared_ptr<Style> ret = new Style(*style);
	return ret;

}

shared_ptr<String> UIManager::getThemeName()
{
	shared_ptr<String> str;
	if(themeProps.get() != NULL){
		str = new String(L"name");
		themeProps->get(*str);
	//	str = *(String*)(p.get());
	}
	return str;
}

void UIManager::resetThemeProps()
{
	themeProps = new Map<String,shared_ptr<Object> >;
	themeProps->put(L"Button.border", Border::getDefaultBorder());
	themeProps->put(L"TouchCommand.border", Border::getDefaultBorder());

	// default pressed border for button
	themeProps->put(L"Button.press#border", Border::getDefaultBorder()->createPressedVersion());
	themeProps->put(L"Button.press#padding", transToVec("4,4,4,4"));
	themeProps->put(L"TouchCommand.press#border", Border::getDefaultBorder()->createPressedVersion());
	themeProps->put(L"TouchCommand.press#padding", transToVec("6,6,6,6"));

	themeProps->put(L"TextArea.border", Border::getDefaultBorder());
	themeProps->put(L"TextField.border", Border::getDefaultBorder());
	themeProps->put(L"ComboBox.border", Border::getDefaultBorder());
	themeProps->put(L"ComboBoxPopup.border", Border::getDefaultBorder());
	themeProps->put(L"Title.margin", (transToVec("0,0,0,0")));
	themeProps->put(L"CommandList.margin", (transToVec("0,0,0,0")));
	themeProps->put(L"CommandList.padding", (transToVec("0,0,0,0")));
	themeProps->put(L"CommandList.transparency", transToVec("0"));
	themeProps->put(L"ComboBoxList.margin", (transToVec("0,0,0,0")));
	themeProps->put(L"ComboBoxList.padding", (transToVec("0,0,0,0")));
	themeProps->put(L"ComboBoxList.transparency", transToVec("0"));
	themeProps->put(L"TableCell.transparency", transToVec("0"));
	themeProps->put(L"TableHeader.transparency", transToVec("0"));
	themeProps->put(L"Menu.padding", (transToVec("0,0,0,0")));
	themeProps->put(L"Command.margin", (transToVec("0,0,0,0")));
	themeProps->put(L"ComboBoxItem.margin", (transToVec("0,0,0,0")));
	themeProps->put(L"Container.transparency", transToVec("0"));
	themeProps->put(L"ContentPane.transparency", transToVec("0"));
	themeProps->put(L"List.transparency", transToVec("0"));
	themeProps->put(L"List.margin", (transToVec("0,0,0,0")));
	themeProps->put(L"SoftButton.transparency", transToVec("255"));
	themeProps->put(L"SoftButton.margin", transToVec("0,0,0,0"));
	themeProps->put(L"SoftButton.padding", transToVec("2,2,2,2"));
	themeProps->put(L"Button.padding", transToVec("4,4,4,4"));
	themeProps->put(L"TouchCommand.padding", transToVec("6,6,6,6"));
	themeProps->put(L"TouchCommand.margin", transToVec("0,0,0,0"));
	themeProps->put(L"Container.margin", transToVec("0,0,0,0"));
	themeProps->put(L"Container.padding", transToVec("0,0,0,0"));
	themeProps->put(L"ContentPane.margin", transToVec("0,0,0,0"));
	themeProps->put(L"ContentPane.padding", transToVec("0,0,0,0"));
	themeProps->put(L"Title.transparency", transToVec("255"));
	themeProps->put(L"TabbedPane.margin", transToVec("0,0,0,0"));
	themeProps->put(L"TabbedPane.padding", transToVec("0,0,0,0"));
	themeProps->put(L"TabbedPane.transparency", transToVec("0"));
	themeProps->put(L"ScrollThumb.padding", transToVec("0,0,0,0"));
	themeProps->put(L"ScrollThumb.margin", transToVec("0,0,0,0"));
	themeProps->put(L"ScrollThumb.bgColor", transToVec("0"));
	themeProps->put(L"Scroll.margin", transToVec("0,0,0,0"));
	themeProps->put(L"Scroll.padding", transToVec("1,1,1,1"));
	themeProps->put(L"HorizontalScrollThumb.padding", transToVec("0,0,0,0"));
	themeProps->put(L"HorizontalScrollThumb.bgColor", transToVec("0"));
	themeProps->put(L"HorizontalScrollThumb.margin", transToVec("0,0,0,0"));
	themeProps->put(L"HorizontalScroll.margin", transToVec("0,0,0,0"));
	themeProps->put(L"HorizontalScroll.padding", transToVec("1,1,1,1"));
	themeProps->put(L"Form.padding", transToVec("0,0,0,0"));
	themeProps->put(L"Form.margin", transToVec("0,0,0,0"));
	themeProps->put(L"ListRenderer.transparency", transToVec("0"));
	themeProps->put(L"Command.transparency", transToVec("0"));
	themeProps->put(L"ComboBoxItem.transparency", transToVec("0"));
	themeProps->put(L"CalendarSelectedDay.border", Border::getDefaultBorder());

	themeProps->put(L"Command.sel#transparency", transToVec("0"));
	themeProps->put(L"ComboBoxItem.sel#transparency", transToVec("0"));
	themeProps->put(L"ListRenderer.sel#transparency", transToVec("100"));
	themeProps->put(L"Button.sel#border", Border::getDefaultBorder());
	themeProps->put(L"TouchCommand.sel#border", Border::getDefaultBorder());
	themeProps->put(L"TextArea.sel#border", Border::getDefaultBorder());
	themeProps->put(L"TextField.sel#border", Border::getDefaultBorder());
	themeProps->put(L"ComboBox.sel#border", Border::getDefaultBorder());
	themeProps->put(L"ComboBoxPopup.sel#border", Border::getDefaultBorder());
	themeProps->put(L"Title.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"CommandList.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"CommandList.sel#padding", transToVec("0,0,0,0"));
	themeProps->put(L"CommandList.sel#transparency", transToVec("0"));
	themeProps->put(L"Menu.sel#padding", transToVec("0,0,0,0"));
	themeProps->put(L"Command.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"ComboBoxItem.sel#margin", transToVec("0,0,0,0"));


	themeProps->put(L"Container.sel#transparency", transToVec("0"));
	themeProps->put(L"ContentPane.sel#transparency", transToVec("0"));
	themeProps->put(L"List.sel#transparency", transToVec("0"));
	themeProps->put(L"SoftButton.sel#transparency", transToVec("255"));
	themeProps->put(L"List.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"SoftButton.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"SoftButton.sel#padding", transToVec("2,2,2,2"));
	themeProps->put(L"Button.sel#padding", transToVec("4,4,4,4"));
	themeProps->put(L"TouchCommand.sel#padding", transToVec("6,6,6,6"));
	themeProps->put(L"TouchCommand.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"Container.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"Container.sel#padding", transToVec("0,0,0,0"));
	themeProps->put(L"ContentPane.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"ContentPane.sel#padding", transToVec("0,0,0,0"));
	themeProps->put(L"Title.sel#transparency", transToVec("255"));
	themeProps->put(L"TabbedPane.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"TabbedPane.sel#padding", transToVec("0,0,0,0"));
	themeProps->put(L"Form.sel#padding", transToVec("0,0,0,0"));
	themeProps->put(L"Form.sel#margin", transToVec("0,0,0,0"));
	themeProps->put(L"sel#transparency", transToVec("255"));
	themeProps->put(L"TableCell.sel#transparency", transToVec("0"));
	themeProps->put(L"TableHeader.sel#transparency", transToVec("0"));

}

void UIManager::setThemeProps( shared_ptr<Map<String,shared_ptr<Object> > > themeProps )
{
	if(accessible) {
		setThemePropsImpl(themeProps);
	}

}

void UIManager::addThemeProps( shared_ptr<Map<String,shared_ptr<Object> > > themeProps )
{
	if(accessible) {
		buildTheme(themeProps);
	}
}

void UIManager::setThemePropsImpl( shared_ptr<Map<String,shared_ptr<Object> > > themeProps )
{
	resetThemeProps();
	styles->clear();
	selectedStyles->clear();
	imageCache->clear();
	if(&*themelisteners != NULL){
		themelisteners->fireActionEvent(new ActionEvent(themeProps));
	}
	buildTheme(themeProps);
	current->refreshTheme();

}

void UIManager::buildTheme( shared_ptr<Map<String,shared_ptr<Object> > > themeProps )
{
	Enumeration<String> e = themeProps->keys();
	while(e.hasMoreElements()) 
	{
		String key = e.nextElement();
		this->themeProps->put(key, themeProps->get(key));
	}
	//this->themeProps = themeProps;
	// necessary to clear up the style so we don't get resedue from the previous UI
	defaultStyle = new Style();

	//create's the default style
	String str = L"";
	defaultStyle = createStyle(str, str, false);
	defaultSelectedStyle = new Style(*defaultStyle);
	String strSel = L"sel#";
	defaultSelectedStyle = createStyle(str, strSel, true);    

}

shared_ptr<Style> UIManager::createStyle( const String& id, const String& prefix, bool selected )
{
	shared_ptr<Style> style;
	String originalId = id;
	String strID = id;
	if(selected) {
		style = new Style(*defaultSelectedStyle);
	} else {
		style = new Style(*defaultStyle);
	}
	if (((String)prefix).size() > 0) {
		strID += prefix;
	}
	if(themeProps.get() != NULL){

		shared_ptr<Vector<unsigned char> > bgColor;
		shared_ptr<Vector<unsigned char> > fgColor;
		shared_ptr<Object> border;

		bgColor = dynamic_pointer_cast<Vector<unsigned char> >(themeProps->get(strID + Style::BG_COLOR));
		fgColor = dynamic_pointer_cast<Vector<unsigned char> >(themeProps->get(strID + Style::FG_COLOR));
		border = themeProps->get(strID + Style::BORDER);

		shared_ptr<Image> bgImage = dynamic_pointer_cast<Image>(themeProps->get(strID + Style::BG_IMAGE));
		shared_ptr<Vector<unsigned char> > transperency = dynamic_pointer_cast<Vector<unsigned char> >(themeProps->get(strID + Style::TRANSPARENCY));
		shared_ptr<Vector<unsigned char> > margin = dynamic_pointer_cast<Vector<unsigned char> >(themeProps->get(strID + Style::MARGIN));
		shared_ptr<Vector<unsigned char> > padding = dynamic_pointer_cast<Vector<unsigned char> >(themeProps->get(strID + Style::PADDING));
		shared_ptr<Object> font = themeProps->get(strID + Style::FONT);


		shared_ptr<Vector<unsigned char> > backgroundType = dynamic_pointer_cast<Vector<unsigned char> >(themeProps->get(strID + Style::BACKGROUND_TYPE));
		shared_ptr<Vector<unsigned char> > backgroundAlignment = dynamic_pointer_cast<Vector<unsigned char> >(themeProps->get(strID + Style::BACKGROUND_ALIGNMENT));
		shared_ptr<Vector<float> > backgroundGradient = dynamic_pointer_cast<Vector<float> >(themeProps->get(strID + Style::BACKGROUND_GRADIENT));
		if(bgColor.get() != NULL)
		{
			int len = bgColor->size();
			AMChar *tmpArray = new AMChar[len + 1];
			int index;
			for (index = 0; index < len; ++index)
			{
				tmpArray[index] = bgColor->elementAt(index);
			}
			tmpArray[index] = '\0';
			int colo = AMcstol(tmpArray, 0, 16);
			style->setBgColor(colo);
			delete []tmpArray;
		}

		if(fgColor.get() != NULL)
		{
			int len = fgColor->size();
			AMChar *tmpArray = new AMChar[len + 1];
			int index;
			for (index = 0; index < len; ++index)
			{
				tmpArray[index] = fgColor->elementAt(index);
			}
			tmpArray[index] = '\0';
			style->setFgColor(AMcstol(tmpArray, 0, 16));
			delete []tmpArray;
		}

		if(transperency.get() != NULL)
		{
			/*int len = transperency->size();
			AMChar *tmpArray = new AMChar[len + 1];
			int index;
			for (index = 0; index < len; ++index)
			{
				tmpArray[index] = transperency->elementAt(index);
			}
			tmpArray[index] = '\0';*/
			if(transperency->size() > 0)
				style->setBgTransparency((*transperency)[0]);
			//delete []tmpArray;
		} 
		else
		{
			if(selected) 
			{
				transperency = dynamic_pointer_cast<Vector<unsigned char> >(themeProps->get(originalId + Style::TRANSPARENCY));

				if(transperency.get() != NULL)
				{
					int len = transperency->size();
					AMChar *tmpArray = new AMChar[len + 1];
					int index;
					for (index = 0; index < len; ++index)
					{
						tmpArray[index] = transperency->elementAt(index);
					}
					tmpArray[index] = '\0';
					style->setBgTransparency((int)AMcstol(tmpArray, 0, 16));
					delete []tmpArray;
				}
			}
		}

		if(margin.get() != NULL)
		{
			style->setMargin((*margin)[0], (*margin)[1], (*margin)[2], (*margin)[3]);
		} 

		if(padding.get() != NULL)
		{
			style->setPadding((*padding)[0] , (*padding)[1], (*padding)[2], (*padding)[3]);
		}

		if(backgroundType.get() != NULL) 
		{
			style->setBackgroundType((*backgroundType)[0]);
		}

		if(backgroundAlignment != NULL) 
		{
			style->setBackgroundAlignment((*backgroundAlignment)[0]);
		}

		if(backgroundGradient.get() != NULL) 
		{
			if(backgroundGradient->size() < 5) 
			{
				backgroundGradient->addElement(1.0f);
			}
			style->setBackgroundGradient(backgroundGradient);
		}

		if(bgImage.get() != NULL)
		{
			shared_ptr<Image> im;
			//weak point
			shared_ptr<String> bgImageStr = dynamic_pointer_cast<String>(bgImage);
			if(bgImageStr.get() != NULL)
			{
					if(imageCache->containsKey(*bgImageStr)) 
					{
						im = imageCache->get(*bgImageStr);
					}
					else
					{ 
						if(bgImageStr->indexOf('/') == 0) 
						{
							im = Image::createImage(bgImageStr);
						} 
						else
						{
							im = parseImage(*bgImageStr);
						}
						imageCache->put(*bgImageStr, im);
					}
					themeProps->put(strID + Style::BG_IMAGE, im);
			}
			else
			{
				im = dynamic_pointer_cast<Image>(bgImage);
			}

			// this code should not excute in the resource editor!
			if(strID.indexOf(L"Form") != -1)
			{
				if((im->getWidth() != Display::getInstance()->getDisplayWidth() || 
					im->getHeight() != Display::getInstance()->getDisplayHeight())
					&& style->getBackgroundType() == Style::BACKGROUND_IMAGE_SCALED && accessible) 
				{
						im->scale(Display::getInstance()->getDisplayWidth(), Display::getInstance()->getDisplayHeight());
				}
			}
			style->setBgImage(im);
		}

		if(font.get() != NULL)
		{
			String* str = static_cast<String*> (font.get());
			if(str != NULL)
			{
				style->setFont(parseFont(*str));
			}
			else
			{
				style->setFont(dynamic_pointer_cast<Font>(font));
			}
		}

		style->setBorder(dynamic_pointer_cast<Border>(border));
		style->resetModifiedFlag();
	} 

	return style;

}


shared_ptr<Image> UIManager::parseImage( const String& value )
{
	int index = 0;

	shared_ptr<VectorArray<unsigned char> > imageData = new VectorArray<unsigned char>(((String)value).length()/2 +1);
	while(index < ((String)value).length())
	{
		String byteStr = ((String)value).substr(index, index + 2);
		
		(*imageData)[index/2] = (unsigned char)AMWcstol((const AMWChar*)byteStr.toCharArray(),0,16);

		index += 2;
	}

	shared_ptr<ByteArrayInputStream> in = new ByteArrayInputStream(imageData);
	shared_ptr<Image> image = Image::createImageFromStream(in);
	return image;

}

shared_ptr<Font> UIManager::parseFont( const String& fontStr )
{
	shared_ptr<Font> font;
	if(((String)fontStr).indexOf(L"System") == 0){
		int face = 0;
		int style = 0;
		int size = 0;
		String faceStr, styleStr, sizeStr;
		String sysFont = ((String)fontStr).substr(((String)fontStr).indexOf(L"{") + 1, ((String)fontStr).indexOf(L"}"));
		faceStr = sysFont.substr(0, sysFont.indexOf(L";"));
		sysFont = sysFont.substr(sysFont.indexOf(L";") + 1, sysFont.length());
		styleStr = sysFont.substr(0, sysFont.indexOf(L";"));
		sizeStr = sysFont.substr(sysFont.indexOf(L";") + 1, sysFont.length());

		if(faceStr.indexOf(L"FACE_SYSTEM") != -1){
			face = Font::FACE_SYSTEM;
		}else if(faceStr.indexOf(L"FACE_MONOSPACE") != -1){
			face = Font::FACE_MONOSPACE;
		}else if(faceStr.indexOf(L"FACE_PROPORTIONAL") != -1){
			face = Font::FACE_PROPORTIONAL;
		}

		if(styleStr.indexOf(L"STYLE_PLAIN")  != -1){
			style = Font::STYLE_PLAIN;
		}else{
			if(styleStr.indexOf(L"STYLE_BOLD") != -1){
				style = Font::STYLE_BOLD;
			}
			if(styleStr.indexOf(L"STYLE_ITALIC")  != -1){
				style = style | Font::STYLE_ITALIC;
			}
			if(styleStr.indexOf(L"STYLE_UNDERLINED") != -1){
				style = style | Font::STYLE_UNDERLINED;
			}
		}

		if(sizeStr.indexOf(L"SIZE_SMALL") != -1){
			size = Font::SIZE_SMALL;
		}else if(sizeStr.indexOf(L"SIZE_MEDIUM") != -1){
			size = Font::SIZE_MEDIUM;
		}else if(sizeStr.indexOf(L"SIZE_LARGE") != -1){
			size = Font::SIZE_LARGE;
		}

		font =  Font::createSystemFont(face, style, size);            
	} else {
		// to check just for go through
		font = Font::getDefaultFont();
		//if(fontStr.toLowerCase().startsWith(L"bitmap")) {
		//	try {
		//		String bitmapFont = fontStr.substring(fontStr.indexOf("{") + 1, fontStr.indexOf("}"));
		//		String nameStr;
		//		nameStr = bitmapFont.substring(0, bitmapFont.length());


		//		if(nameStr.toLowerCase().startsWith("highcontrast")) {
		//			nameStr = nameStr.substring(nameStr.indexOf(";") + 1, nameStr.length());
		//			com.sun.lwuit.Font f = com.sun.lwuit.Font.getBitmapFont(nameStr);
		//			f.addContrast((byte)30);
		//			return f;
		//		}

		//		return com.sun.lwuit.Font.getBitmapFont(nameStr);
		//	} catch (Exception ex) {
		//		// illegal argument exception?
		//		ex.printStackTrace();
		//	}
		//}
	}
	// illegal argument?
	return font;

}

shared_ptr<Map<String,shared_ptr<Object> > > UIManager::getResourceBundle()
{
	return resourceBundle;
}

void UIManager::setResourceBundle( shared_ptr<Map<String,shared_ptr<Object> > > resourceBundle )
{
	this->resourceBundle = resourceBundle;
}

shared_ptr<String> UIManager::localize( const String& key, const String& defaultValue )
{
	shared_ptr<String>  ret = new String(defaultValue) ;
	if(&*resourceBundle != NULL) {
		shared_ptr<Object> o = resourceBundle->get(key);
		if(o.get() != NULL) {
			ret = dynamic_pointer_cast<String>(o);
		}
	}
	return ret;
}
shared_ptr<String> UIManager::localize(GUI_CHAR* key, GUI_CHAR* defaultValue){
	String str(key);
	shared_ptr<String>  ret = new String(defaultValue) ;
	if(resourceBundle.get() != NULL) {
		shared_ptr<Object> o = resourceBundle->get(str);
		if(o.get() != NULL) {
			ret = dynamic_pointer_cast<String>(o);
		}
	}
	return ret;

}
void UIManager::addThemeRefreshListener( shared_ptr<ActionListener> l )
{
	if (themelisteners.get() == NULL) {
		themelisteners = new EventDispatcher<ActionListener>();
	}
	themelisteners->addListener(l);
}

void UIManager::removeThemeRefreshListener( shared_ptr<ActionListener> l )
{
	if (&*themelisteners == NULL) {
		return;
	}
	themelisteners->removeListener(l);
}

shared_ptr<Vector<unsigned char> > UIManager::transToVec( const char *str )
{
	shared_ptr<Vector<unsigned char> > retVal = new Vector<unsigned char>();
	int len = AMStrlen(str);
	for (int i = 0; i < len; )
	{
		int j;
		for (j = i; j < len; ++j)
		{
			if (str[j] == ',')
			{
				break;
			}
		}

		
			int tmplen = j - i;
			char *tmp = new char[tmplen + 1];
			memset(tmp, 0, sizeof(char) * (tmplen + 1));
			AMStrncpy(tmp, str + i, tmplen);
			tmp[tmplen] = '\0';
			int result = atoi(tmp);
			delete []tmp;
			retVal->addElement(result);
		
		i = j + 1;

	}
	return retVal;
}

__GUI_END_NAMESPACE
