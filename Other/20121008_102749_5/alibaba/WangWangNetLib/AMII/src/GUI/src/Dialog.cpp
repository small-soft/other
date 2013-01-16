#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

int Dialog::defaultDialogType = Dialog::TYPE_INFO;
bool Dialog::autoAdjustDialogSize = true;
bool Dialog::disableStaticDialogScrolling = false;
int Dialog::defaultDialogPosition = 0;
bool Dialog::commandsAsButtons = false;

AM_IMPLEMENT_DYNAMIC(Dialog, Form)

shared_ptr<Dialog> Dialog::newV( shared_ptr<String> dialogUIID, shared_ptr<String> dialogTitleUIID)
{
	shared_ptr<Dialog> dlg = new Dialog();
	dlg->constructV(dialogUIID, dialogTitleUIID);
	return dlg;
}

shared_ptr<Dialog> Dialog::newV( shared_ptr<String> title )
{
	shared_ptr<Dialog> dlg = new Dialog();
	dlg->constructV(title);
	return dlg;
}

shared_ptr<Dialog> Dialog::newV()
{
	shared_ptr<Dialog> dlg = new Dialog();
	dlg->constructV();
	return dlg;
}
Dialog::Dialog()
{
	disposed = false;
	menu = false;
	includeTitle = false;

	time = 0;
	dialogType = 0;
	top = -1;
	bottom = 0;
	left = 0;
	right = 0;
	position = 0;
	autoDispose = true;
	modal = true;
	disposeWhenPointerOutOfBounds = false;
	paintBG = false;
	preFormTint = false;
}

void Dialog::constructV( shared_ptr<String> dialogUIID, shared_ptr<String> dialogTitleUIID)
{	
	Form::constructV();
	this->dialogUIID = dialogUIID;
	this->dialogTitleUIID = dialogTitleUIID;
	getContentPane()->setUIID(dialogUIID);
	getTitleComponent()->setUIID(dialogTitleUIID);
	Form::getStyle()->setBgTransparency(0);

	shared_ptr<Image> bgImage;
	Form::getStyle()->setBgImage(bgImage);
	setSmoothScrolling(false);
	
	deregisterAnimated(this->shared_from_this());
}

void Dialog::constructV( shared_ptr<String> title )
{
	constructV();
	setTitle(title);
}

void Dialog::constructV()
{
	constructV(new String(L"Dialog"), new String(L"DialogTitle"));
}
Dialog::~Dialog(void)
{
}

bool Dialog::isPaintBG()
{
	return paintBG;
}
shared_ptr<Dialog> Dialog::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<Dialog>(cmp);
}
void Dialog::setPaintBG( bool b )
{
	paintBG = b;
}

bool Dialog::getPreFormTint()
{
	return preFormTint;
}

void Dialog::setPreFormTint( bool b )
{
	preFormTint = b;
}

shared_ptr<Rectangle> Dialog::getBGRect()
{
	return bgRect;
}

void Dialog::setBGRect( shared_ptr<Rectangle> r )
{
	bgRect = r;
}

void Dialog::setDialogStyle( shared_ptr<Style> style )
{
	getContentPane()->Component::setUnSelectedStyle(style);
}

shared_ptr<Style> Dialog::getDialogStyle()
{
	 return getContentPane()->getStyle();
}

void Dialog::initLaf( shared_ptr<LookAndFeel> laf )
{
	setTransitionOutAnimator(laf->getDefaultDialogTransitionOut());
	setTransitionInAnimator(laf->getDefaultDialogTransitionIn());
}

shared_ptr<Command> Dialog::show( int top, int bottom, int left, int right, bool includeTitle )
{
	//modified by qianjiajing  
	//return show(top, bottom, left, right, includeTitle, true); 
	return show(top, bottom, left, right, includeTitle, false);
	//end
}

shared_ptr<Command> Dialog::show( int top, int bottom, int left, int right, bool includeTitle, bool modal )
{
	this->top = top;
	this->bottom = bottom;
	if(isRTL()){
		this->left = right;
		this->right = left;            
	}else{
		this->left = left;
		this->right = right;
	}
	this->includeTitle = includeTitle;
	setDisposed(false);
	this->modal = modal;
	lastCommandPressed.reset();
	Form::showModal(this->top, this->bottom, this->left, this->right, includeTitle, modal, false);
	return lastCommandPressed;

}

bool Dialog::show( shared_ptr<String> title, shared_ptr<String> text, int type, shared_ptr<Image> icon, shared_ptr<String> okText, shared_ptr<String> cancelText )
{
	return show(title, text, type, icon, okText, cancelText, 0);
}

bool Dialog::show( shared_ptr<String> title, shared_ptr<String> text, int type, shared_ptr<Image> icon, shared_ptr<String> okText, shared_ptr<String> cancelText, long timeout )
{
	 shared_ptr<Vector<shared_ptr<Command> > > cmds = new  Vector<shared_ptr<Command> >;
	shared_ptr<Command> okCommand = new Command(okText);
	if (cancelText.get() != NULL) {
		cmds->addElement(new Command(cancelText));
		cmds->addElement(okCommand);

	} else {
		cmds->addElement(okCommand);
	}
	return show(title, text, okCommand, cmds, type, icon, timeout) == okCommand;

}

shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<String> text,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout )
{
	shared_ptr<Command> cmd;
	return show(title, text, cmd, cmds, type, icon, timeout);
}

shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<String> text, shared_ptr<Command> defaultCommand,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout )
{
	shared_ptr<Transition> t;
	return show(title, text, defaultCommand, cmds, type, icon, timeout, t);
}

shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<String> text,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition )
{
	shared_ptr<Command> cmd;
	return show(title, text, cmd, cmds, type, icon, timeout, transition);
}

bool Dialog::show( shared_ptr<String> title, shared_ptr<String> text, shared_ptr<String> okText, shared_ptr<String> cancelText )
{
	shared_ptr<Image> icon;
	return show(title, text, defaultDialogType, icon, okText, cancelText);
}

shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<Component> body,  shared_ptr<Vector<shared_ptr<Command> > > cmds )
{
	shared_ptr<Image> icon;
	return show(title, body, cmds, defaultDialogType, icon);
}

shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<Component> body,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon )
{
	return show(title, body, cmds, type, icon, 0);
}

shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<Component> body,  shared_ptr<Vector<shared_ptr<Command> > > cmds, const int type, shared_ptr<Image> icon, long timeout )
{
	shared_ptr<Transition> t;
	return show(title, body, cmds, type, icon, timeout, t);
}

shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<Component> body,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition )
{
	shared_ptr<Command> cmd;
	return show(title, body, cmd, cmds, type, icon, timeout, transition);
}

shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<Component> body, shared_ptr<Command> defaultCommand,  shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition )
{
	shared_ptr<Dialog> dialog = Dialog::newV(title);
	dialog->dialogType = type;
	dialog->setTransitionInAnimator(transition);
	dialog->setTransitionOutAnimator(transition);
	dialog->lastCommandPressed.reset();
	dialog->setLayout(new BorderLayout());
	if(cmds.get() != NULL) {
		if(commandsAsButtons) {
			shared_ptr<Container> buttonArea = Container::newV();
			dialog->addComponent(BorderLayout::SOUTH, buttonArea);
			if(cmds->size() > 0) {
				for( int iter = 0 ; iter < cmds->size() ; iter++) {
					shared_ptr<Component> button = Button::newV(cmds->elementAt(iter));
					buttonArea->addComponent(button);
				}
				buttonArea->getComponentAt(0)->requestFocus();
			}
		} else {
			for( int iter = 0 ; iter < cmds->size() ; iter++) {
				dialog->addCommand(cmds->elementAt(iter));
			}
		}

		// for the special case of one command map it to the back button
		if(cmds->size() == 1) {
			dialog->setBackCommand(cmds->elementAt(0));
		} else {
			// map two commands to fire and back
			if(cmds->size() == 2 && defaultCommand.get() == NULL) {
				defaultCommand = cmds->elementAt(0);
				dialog->setBackCommand(cmds->elementAt(1));
			}
		}
	}
	dialog->addComponent(BorderLayout::CENTER, body);
	if (icon.get() != NULL) {
		dialog->addComponent(BorderLayout::EAST, Label::newV(icon));
	}
	if (timeout != 0) {
		dialog->setTimeout(timeout);
	}
	if(body->isScrollable() || disableStaticDialogScrolling){
		dialog->setScrollable(false);
	}
	dialog->show();
	return dialog->lastCommandPressed;

}

void Dialog::show()
{
	 showImpl(false);
}
shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<String> text, shared_ptr<Command> defaultCommand, shared_ptr<Vector<shared_ptr<Command> > > cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition )
{
	shared_ptr<Command> cmd;
	return cmd;
}
//shared_ptr<Command> Dialog::show( shared_ptr<string> title, shared_ptr<string> text, shared_ptr<Command> defaultCommand,  shared_ptr<Vector<shared_ptr<Command>>> cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition )

//shared_ptr<Command> Dialog::show( shared_ptr<String> title, shared_ptr<String> text, shared_ptr<Command> defaultCommand,  shared_ptr<Vector<shared_ptr<Command>>> cmds, int type, shared_ptr<Image> icon, long timeout, shared_ptr<Transition> transition )
//
//{
//	Hashtable h =  UIManager::getInstance()->getResourceBundle();
//	if(h != NULL && text != NULL) {
//		void* o = h->get(text);
//		if(o != NULL) {
//			text = (shared_ptr<String>)o;
//		}
//	} 
//	TextArea t = new TextArea(text, 3, 30);
//	t.setUnselectedStyle(UIManager.getInstance().getComponentStyle("DialogBody"));
//	t.setSelectedStyle(UIManager.getInstance().getComponentSelectedStyle("DialogBody"));
//	t.setEditable(false);
//	return show(title, t, defaultCommand, cmds, type, icon, timeout, transition);
//
//}
void Dialog::setTimeout( long time )
{

	this->time = System::currentTimeMillis() + time;
	Form::registerAnimatedInternal(this->shared_from_this());
}

void Dialog::sizeChangedInternal( int w, int h )
{
	if(autoAdjustDialogSize) {
		// if the dialog is packed we can scale it far more accurately based on intention
		if(position >= 0) {
			shared_ptr<Component> contentPane = getContentPane();
			shared_ptr<Component> title = getTitleComponent();

			shared_ptr<Style> contentPaneStyle = contentPane->getStyle();
			shared_ptr<Style> titleStyle = title->getStyle();

			int menuHeight = 0;
			if(getSoftButtonCount() > 1) {
				shared_ptr<Component> menuBar = getSoftButton(0)->getParent();
				shared_ptr<Style> menuStyle = menuBar->getStyle();
				menuHeight = menuBar->getPreferredH() + menuStyle->getMargin(false, TOP) + menuStyle->getMargin(false, BOTTOM);
			}
			int prefHeight = contentPane->getPreferredH() + contentPaneStyle->getMargin(false, TOP) + contentPaneStyle->getMargin(false, BOTTOM);
			int prefWidth = contentPane->getPreferredW() + contentPaneStyle->getMargin(isRTL(), LEFT) + contentPaneStyle->getMargin(isRTL(), RIGHT);
			prefWidth = min(prefWidth, w);
			h = h - menuHeight - title->getPreferredH() - titleStyle->getMargin(false, TOP) - titleStyle->getMargin(false, BOTTOM);
			int topBottom =max(0, (h - prefHeight) / 2);
			int leftRight =max(0, (w - prefWidth) / 2);
			int top = topBottom, bottom = topBottom;
			int left = leftRight, right = leftRight;

			if(position ==BorderLayout::EAST) {
				left = max(0, w - prefWidth);
				right = 0;
			} else {
				if(position ==BorderLayout::WEST) {
					right = 0;
					left = max(0, w - prefWidth);
				} else {
					if(position ==BorderLayout::NORTH) {
						top = 0;
						bottom = max(0, h - prefHeight);
					} else {
						if(position ==BorderLayout::SOUTH) {
							top = max(0, h - prefHeight);
							bottom = 0;
						}
					}
				}
			}

			shared_ptr<Style> contentStyle = getDialogStyle();
			if (includeTitle) {
				titleStyle->setMargin(Component::TOP, top, true);
				titleStyle->setMargin(Component::BOTTOM, 0, true);
				titleStyle->setMargin(Component::LEFT, left, true);
				titleStyle->setMargin(Component::RIGHT, right, true);

				contentStyle->setMargin(Component::TOP, 0, true);
				contentStyle->setMargin(Component::BOTTOM, bottom, true);
				contentStyle->setMargin(Component::LEFT, left, true);
				contentStyle->setMargin(Component::RIGHT, right, true);
			} else {
				titleStyle->setMargin(Component::TOP, 0, true);
				titleStyle->setMargin(Component::BOTTOM, 0, true);
				titleStyle->setMargin(Component::LEFT, 0, true);
				titleStyle->setMargin(Component::RIGHT, 0, true);

				contentStyle->setMargin(Component::TOP, top, true);
				contentStyle->setMargin(Component::BOTTOM, bottom, true);
				contentStyle->setMargin(Component::LEFT, left, true);
				contentStyle->setMargin(Component::RIGHT, right, true);
			}
		} else {
			int oldW = getWidth();
			int oldH = getHeight();
			if(oldW != w || oldH != h) {

				float ratioW = ((float)w) / ((float)oldW);
				float ratioH = ((float)h) / ((float)oldH);

				shared_ptr<Style> s = getDialogStyle();

				s->setMargin(TOP, (int)(s->getMargin(false, TOP) * ratioH));
				s->setMargin(BOTTOM, (int)(s->getMargin(false, BOTTOM) * ratioH));
				s->setMargin(LEFT, (int)(s->getMargin(isRTL(), LEFT) * ratioW));
				s->setMargin(RIGHT, (int)(s->getMargin(isRTL(), RIGHT) * ratioW));

				shared_ptr<Style> titleStyle = getTitleStyle();
				titleStyle->setMargin(TOP, (int)(titleStyle->getMargin(false, TOP) * ratioH));
				titleStyle->setMargin(LEFT, (int)(titleStyle->getMargin(isRTL(), LEFT) * ratioW));
				titleStyle->setMargin(RIGHT, (int)(titleStyle->getMargin(isRTL(), RIGHT) * ratioW));
			}
		}
	}

	top = -1;
	bottom = -1;
	left = -1;
	right = -1;
	position = NULL;
	Form::sizeChangedInternal(w, h);
	shared_ptr<Form> frm = getPreviousForm();
	if(frm.get() != NULL){
		frm->sizeChangedInternal(w, h);
	}        

}

void Dialog::onShow()
{
	if (dialogType > 0) {
		Display::getInstance()->playDialogSound(dialogType);
	}
}

void Dialog::showBack()
{
	showImpl(true);
}

void Dialog::showImpl( bool reverse )
{
	// this behavior allows a use case where dialogs of various sizes are layered
	// one on top of the other
	setDisposed(false);
	if(top > -1) {
		show(top, bottom, left, right, includeTitle, modal);
	} else {
		if(modal) {
			if(defaultDialogPosition > 0) {
				Form::showModal(reverse);
			} else {
				showPacked(defaultDialogPosition, true);
			}
		} else {
			showModeless();
		}
	}

}

void Dialog::showModeless()
{
	// this behavior allows a use case where dialogs of various sizes are layered 
	// one on top of the other
	modal = false;
	setDisposed(false);
	if(top > -1) {
		show(top, bottom, left, right, includeTitle, false);
	} else {
		if(defaultDialogPosition > 0) {
			Form::showDialog(false, false);
		} else {
			showPacked(defaultDialogPosition, false);
		}
	}
}

shared_ptr<Command> Dialog::showPacked(int position, bool modal )
{
	this->position = position;
	int height = Display::getInstance()->getDisplayHeight();
	int width = Display::getInstance()->getDisplayWidth();
	if(top > -1){
		refreshTheme();
	}
	shared_ptr<Component> contentPane = getContentPane();
	shared_ptr<Component> title = getTitleComponent();

	shared_ptr<Style> contentPaneStyle = contentPane->getStyle();
	shared_ptr<Style> titleStyle = title->getStyle();

	int menuHeight = 0;
	if(getSoftButtonCount() > 1) {
		shared_ptr<Component> menuBar = getSoftButton(0)->getParent();
		shared_ptr<Style> menuStyle = menuBar->getStyle();
		menuHeight = menuBar->getPreferredH() + menuStyle->getMargin(false, TOP) + menuStyle->getMargin(false, BOTTOM);
	}
	int prefHeight = contentPane->getPreferredH() + contentPaneStyle->getMargin(false, TOP) + contentPaneStyle->getMargin(false, BOTTOM);
	int prefWidth = contentPane->getPreferredW() + contentPaneStyle->getMargin(isRTL(), LEFT) + contentPaneStyle->getMargin(isRTL(), RIGHT);
	prefWidth = min(prefWidth, width);
	height = height - menuHeight - title->getPreferredH() - titleStyle->getMargin(false, TOP) - titleStyle->getMargin(false, BOTTOM);
	int topBottom = max(0, (height - prefHeight) / 2);
	int leftRight = max(0, (width - prefWidth) / 2);

	if(position == (BorderLayout::CENTER)) {
		show(topBottom, topBottom, leftRight, leftRight, true, modal);
		return lastCommandPressed;
	} 
	if(position == (BorderLayout::EAST)) {
		show(topBottom, topBottom, max(0, width - prefWidth), 0, true, modal);
		return lastCommandPressed;
	} 
	if(position == (BorderLayout::WEST)) {
		show(topBottom, topBottom, 0, max(0, width - prefWidth), true, modal);
		return lastCommandPressed;
	} 
	if(position == (BorderLayout::NORTH)) {
		show(0, max(0, height - prefHeight), leftRight, leftRight, true, modal);
		return lastCommandPressed;
	} 
	if(position == (BorderLayout::SOUTH)) {
		show(max(0, height - prefHeight), 0, leftRight, leftRight, true, modal);
		return lastCommandPressed;
	} 
	shared_ptr<Command> cmd;
	return cmd;
//	throw new IllegalArgumentException("Unknown position: " + position);

}

void Dialog::dispose()
{

	setDisposed(true);

	// the dispose parent method might send us back to the form while the command
	// within the dialog might be directing us to another form causing a "blip"
	//delete by jiajing
	/* if(!menu)*/ {
		Form::dispose();
	}

}

shared_ptr<Command> Dialog::showDialog()
{
	lastCommandPressed.reset();
	show();
	return lastCommandPressed;

}

void Dialog::actionCommand( shared_ptr<Command> cmd )
{
	// this is important... In a case of nested dialogs based on commands/events a command might be
	// blocked by a different dialog, so when that dialog is disposed (as a result of a command) going
	// back to this dialog will block that command from proceeding and it can be fired again later
	// E.g.:
	// Dialog A has a command which triggers dialog B on top.
	// User presses Cancel in dialog B
	// Dialog A is shown as a result of dialog B dispose method
	// Cancel command event firing is blocked since the dialog B dispose method is now blocking on dialog A show()...
	// When dialog A is disposed using the OK command the OK command is sent correctly and causes dispose
	// EDT is released which also releases the Cancel for dialog B to keep processing...
	// Cancel for dialog B proceeds in the event chain reaching this method....
	// lastCommandPressed can be overrwritten if this check isn't made!!!
	if(!autoDispose || lastCommandPressed.get() == NULL) {
		lastCommandPressed = cmd;
	}
	if(menu || (autoDispose && cmd->isDisposesDialog())) {
		dispose();
	}

}

bool Dialog::animate()
{
	isTimedOut();
	return false;
}

bool Dialog::isTimedOut()
{
	if (time != 0 && System::currentTimeMillis() >= time) {
		time = 0;
		dispose();
		deregisterAnimatedInternal(this->shared_from_this());
		return true;
	}
	return false;

}

bool Dialog::isMenu()
{
	return menu;
}

void Dialog::setMenu( bool menu )
{
  this->menu = menu;
}

void Dialog::addSelectCommand()
{
	if (!menu) {
		Form::addSelectCommand(getSelectCommandText());
	}
}

bool Dialog::isDisposed()
{
	return disposed || isTimedOut();
}

void Dialog::setDisposed( bool disposed )
{
  this->disposed = disposed;
}

bool Dialog::isAutoDispose()
{
	return autoDispose;
}

void Dialog::setAutoDispose( bool autoDispose )
{
     this->autoDispose = autoDispose;
}

void Dialog::setDefaultDialogPosition( int p )
{
	 defaultDialogPosition = p;
}

int Dialog::getDefaultDialogPosition()
{
 return defaultDialogPosition;
}

int Dialog::getDialogType()
{
 return dialogType;
}

void Dialog::setDialogType( int dialogType )
{
 this->dialogType = dialogType;
}

void Dialog::setDefaultDialogType( int d )
{
 defaultDialogType = d;
}

int Dialog::getDefaultDialogType()
{
 return defaultDialogType;
}

void Dialog::setAutoAdjustDialogSize( bool a )
{
autoAdjustDialogSize = a;
}

void Dialog::setDisableStaticDialogScrolling( bool d )
{
disableStaticDialogScrolling = d;
}

bool Dialog::isDisableStaticDialogScrolling()
{
return disableStaticDialogScrolling;
}

void Dialog::setCommandsAsButtons( bool c )
{
commandsAsButtons = c;
}

bool Dialog::isCommandsAsButtons()
{
  return commandsAsButtons;
}

void Dialog::setDisposeWhenPointerOutOfBounds( bool disposeWhenPointerOutOfBounds )
{
  this->disposeWhenPointerOutOfBounds = disposeWhenPointerOutOfBounds;
}

void Dialog::pointerReleased( int x, int y )
{
	Form::pointerReleased(x, y);
	if(disposeWhenPointerOutOfBounds &&
		!getTitleComponent()->Component::contains(x, y) && 
		!getContentPane()->Component::contains(x, y) && 
		!getMenuBar()->Component::contains(x, y)){
			dispose();
	}
}
__GUI_END_NAMESPACE
