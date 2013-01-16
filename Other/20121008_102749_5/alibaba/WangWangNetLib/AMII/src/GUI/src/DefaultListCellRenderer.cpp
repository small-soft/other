#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(DefaultListCellRenderer, Label)

bool DefaultListCellRenderer::showNumbersDefault = true;
DefaultListCellRenderer::DefaultListCellRenderer(bool showNumbers)
{
	setCellRenderer(true);
	setEndsWith3Points(false);
	this->showNumbers = showNumbers;
	focusComponent = Label::newV();
	shared_ptr<String> id = new String(L"ListRendererFocus");
	focusComponent->setUIID(id);
	focusComponent->setFocus(true);
	id = new String(L"ListRenderer");
	setUIID(id);
}


DefaultListCellRenderer::~DefaultListCellRenderer(void)
{
}

void DefaultListCellRenderer::refreshTheme()
{
	Label::refreshTheme();
	focusComponent->refreshTheme();
}

shared_ptr<Component> DefaultListCellRenderer::getListCellRendererComponent( shared_ptr<List> list, shared_ptr<Object> value, int index, bool isSelected )
{
	setFocus(isSelected);
//	shared_ptr<String> text =  dynamic_pointer_cast<String>(value);
	if(showNumbers/*&& text.get() != NULL*/ ) {	

	/*	shared_ptr<Map<String,shared_ptr<void>>> t =  UIManager::getInstance()->getResourceBundle();
		if(t.get() != NULL && value.get() != NULL) {
			shared_ptr<Object> o = t.get(value->toString());
			if(o.get() != NULL) {
				text = (String)o;
			}
		}*/
		shared_ptr<String> text = dynamic_pointer_cast<String>(value);
		if (text.get() == NULL)
		{
			text = value->toString();
		}		
		shared_ptr<String> str;// = value->toString() ;
		if(isRTL()){
			String title = *text+ L" ." + System::getString(index +1);
			str = new String(title);
		}else{
			String title = System::getString(index +1)+ L". " + *text;
			str = new String(title);
		}
		setText(str);
	} else {
		if(value.get() != NULL) {
			setText(value->toString());
		} else {
			shared_ptr<String> strNull = new String(L"NULL");
			setText(strNull);
		}
	}

	shared_ptr<Command> cmd = dynamic_pointer_cast<Command>(value);
	if(cmd.get() != NULL) 
	{
		setIcon(cmd->getIcon());
	}
	return this->shared_from_this();

}

shared_ptr<Component> DefaultListCellRenderer::getListFocusComponent( shared_ptr<List> list )
{
	  return focusComponent;
}

void DefaultListCellRenderer::repaint()
{

}

bool DefaultListCellRenderer::isShowNumbers()
{
	return showNumbers;
}

void DefaultListCellRenderer::setShowNumbers( bool showNumbers )
{
	  this->showNumbers = showNumbers;
}

int DefaultListCellRenderer::getSelectionTransparency()
{
	 return focusComponent->getUnselectedStyle()->getBgTransparency() & 0xff;
}

void DefaultListCellRenderer::setSelectionTransparency( int selectionTransparency )
{
	 focusComponent->getUnselectedStyle()->setBgTransparency(selectionTransparency);
}

void DefaultListCellRenderer::setShowNumbersDefault( bool def )
{
	 showNumbersDefault = def;
}

bool DefaultListCellRenderer::isShowNumbersDefault()
{
	 return showNumbersDefault;
}
__GUI_END_NAMESPACE
