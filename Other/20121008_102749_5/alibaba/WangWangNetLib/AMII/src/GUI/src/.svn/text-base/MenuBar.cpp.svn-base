#include "AMGui.h"

__GUI_BEGIN_NAMESPACE

AM_IMPLEMENT_DYNAMIC(MenuBar, Container)

void MenuBar::constructV( shared_ptr<Form> form )
{	
	Container::constructV();
	this->form = form;
	commands = new Vector<shared_ptr<Command> >;

	shared_ptr<LookAndFeel> lf = UIManager::getInstance()->getLookAndFeel();
	String str1(L"Menu"),str2(L"SoftButton"),str3(L"Menu");
	menuStyle = UIManager::getInstance()->getComponentStyle(str1);
	setUnSelectedStyle(UIManager::getInstance()->getComponentStyle(str2));
	shared_ptr<Image> icon;
	if(lf->getMenuIcons()->size() >2)
		icon = lf->getMenuIcons()->elementAt(2);

	menuCommand = new Command(UIManager::getInstance()->localize(str1, str3), icon);
	// use the slide transition by default
	if (lf->getDefaultMenuTransitionIn().get() != NULL || lf->getDefaultMenuTransitionOut().get() != NULL) {
		transitionIn = lf->getDefaultMenuTransitionIn();
		transitionOut = lf->getDefaultMenuTransitionOut();
	}
	//to do not support trans
	else {
		transitionIn = CommonTransitions::createSlide(CommonTransitions::SLIDE_VERTICAL, true, 300, true);
		transitionOut = CommonTransitions::createSlide(CommonTransitions::SLIDE_VERTICAL, false, 300, true);
	}
	menuCellRenderer = lf->getMenuRenderer();

	if (Display::getInstance()->getImplementation()->getSoftkeyCount() > 1) {
		if (Display::getInstance()->isThirdSoftButton()) {
			setLayout(new GridLayout(1, 3));
			soft = new Vector<shared_ptr<Button> >;
			soft->addElement(createSoftButton());
			soft->addElement(createSoftButton());
			soft->addElement(createSoftButton());
			main = (*soft)[0];
			main->setAlignment(Label::CENTER);
			left = (*soft)[1];
			right = (*soft)[2];
			if (form->isRTL()) {
				addComponent(right);
				addComponent(main);
				addComponent(left);
			} else {
				addComponent(left);
				addComponent(main);
				addComponent(right);
			}
			if (form->isReverseSoftButtons()) {
				shared_ptr<Button> b = (*soft)[1];
				(*soft)[1] = (*soft)[2];
				(*soft)[2] = b;
			}
		} else {
			// modified by jiajing for change to borderLayout
			//this.setLayout(new GridLayout(1, 2));
			this->setLayout(new BorderLayout());

			soft = new Vector<shared_ptr<Button> >;
			soft->addElement(createSoftButton());
			soft->addElement(createSoftButton());

			main = (*soft)[0];
			left = (*soft)[0];
			right = (*soft)[1];
			if (form->isRTL()) {
				//	addComponent(right);
				//	addComponent(left);
				this->addComponent(BorderLayout::WEST,right);
				this->addComponent(BorderLayout::EAST,left);
			} else {
				//	addComponent(left);
				//	addComponent(right);
				this->addComponent(BorderLayout::WEST,left);
				this->addComponent(BorderLayout::EAST,right);
				/*	this.addComponent(BorderLayout.WEST,right);
				this.addComponent(BorderLayout.EAST,left);*/
			}
			//end
			if (form->isReverseSoftButtons()) {
				shared_ptr<Button> b = (*soft)[0];
				(*soft)[0] = (*soft)[1];
				(*soft)[1] = b;
			}
		}
		// It doesn't make sense for softbuttons to have ... at the end
		for(int iter = 0 ; iter < soft->size() ; iter++) {
			(*soft)[iter]->setEndsWith3Points(false);
		}
	} else {
		// special case for touch screens we still want the 3 softbutton areas...
		if(Display::getInstance()->isThirdSoftButton()) {
			setLayout(new GridLayout(1, 3));
			soft = new Vector<shared_ptr<Button> >;
			soft->addElement(createSoftButton());
			soft->addElement(createSoftButton());
			soft->addElement(createSoftButton());
			main = (*soft)[0];
			main->setAlignment(Label::CENTER);
			left = (*soft)[1];
			right =(*soft)[2];
			addComponent(left);
			addComponent(main);
			addComponent(right);
			if (form->isReverseSoftButtons()) {
				shared_ptr<Button> b = (*soft)[1];
				(*soft)[1] = (*soft)[2];
				(*soft)[2] = b;
			}
		} else {
			soft = new Vector<shared_ptr<Button> >;
			soft->addElement(createSoftButton());
		}
	}
	if (left.get() != NULL) {
		if (form->isRTL()) {
			left->setAlignment(Label::RIGHT);
			right->setAlignment(Label::LEFT);
		} else {
			left->setAlignment(Label::LEFT);
			right->setAlignment(Label::RIGHT);
		}
	}
	softCommand = new VectorArray<shared_ptr<Command> >(soft->size());
}

MenuBar::~MenuBar( void )
{

}
shared_ptr<MenuBar> MenuBar::shared_from_this()
{
	shared_ptr<Component> cmp = Component::shared_from_this();
	return dynamic_pointer_cast<MenuBar>(cmp);
}

void MenuBar::addDirectCommand( shared_ptr<Command> cmd )
{
	directCommand = cmd;
	updateCommands();
}

shared_ptr<Command> MenuBar::getDirectCommand()
{
	return directCommand;
}

void MenuBar::updateCommands()
{
	if (soft->size() > 1) {
		shared_ptr<Image> image;
		(*soft)[0]->setText(new String(L""));
		(*soft)[1]->setText(new String(L""));
		(*soft)[0]->setIcon(image);
		(*soft)[1]->setIcon(image);
		int commandSize = commands->size();
		if (soft->size() > 2) {
			(*soft)[2]->setText(new String(L""));
			if (commandSize > 2) {
				if (commandSize > 3) {
					(*softCommand)[2] = menuCommand;
				} else {
					(*softCommand)[2] =  commands->elementAt(commands->size() - 3);
				}
				(*soft)[2]->setText((*softCommand)[2]->getCommandName());
				(*soft)[2]->setIcon((*softCommand)[2]->getIcon());
			} else {
				(*softCommand)[2].reset();
			}
		}
		if (commandSize > 0) {
			// modified by jiajing
			if (directCommand.get() != NULL) {
				(*softCommand)[0] = directCommand;
			} else
				(*softCommand)[0] = commands->elementAt(commands->size() - 1);
			// end 
			//softCommand[0] = (Command) commands.elementAt(commands.size() - 1);
			(*soft)[0]->setText((*softCommand)[0]->getCommandName());
			(*soft)[0]->setIcon((*softCommand)[0]->getIcon());
			if (commandSize > 1) {
				if (soft->size() == 2 && commandSize > 2) {
					(*softCommand)[1] = menuCommand;
				} else {
					(*softCommand)[1] =  commands->elementAt(commands->size() - 2);
				}
				// modified by jiajing
				if (soft->size() == 2 && commandSize > 1
					&& directCommand.get() != NULL)
					(*softCommand)[1] = menuCommand;
				//end
				(*soft)[1]->setText((*softCommand)[1]->getCommandName());
				(*soft)[1]->setIcon((*softCommand)[1]->getIcon());
			} else {
				(*softCommand)[1].reset();
			}
		} else {
			(*softCommand)[0].reset();
			(*softCommand)[1].reset();
		}

		// we need to add the menu bar to an already visible form
		if (commandSize == 1) {
			if (form->isVisible()) {
				form->revalidate();
			}
		}
		Component::repaint();
	}

}

void MenuBar::actionPerformed( shared_ptr<ActionEvent> evt )
{
	if (evt->isConsumed()) {
		return;
	}
	shared_ptr<Object> src = evt->getSource();
	if (commandList.get() == NULL) {
		//weak
		shared_ptr<Button> source = dynamic_pointer_cast<Button>(src);
		for (int iter = 0; iter < soft->size(); iter++) {
			if (source == (*soft)[iter]) {
				if ((*softCommand)[iter] == menuCommand) {
					showMenu();
					return;
				}
				if ((*softCommand)[iter].get()!= NULL) {
					shared_ptr<ActionEvent> e = new ActionEvent((*softCommand)[iter]);
					(*softCommand)[iter]->actionPerformed(e);
					if (!e->isConsumed()) {
						form->actionCommandImpl((*softCommand)[iter]);
					}
				}
				return;
			}
		}
	} else {
		// the list for the menu sent the event
		Button* btn = dynamic_cast<Button *>(src.get());
		if (btn != NULL) {
			for (int iter = 0; iter < soft->size(); iter++) {
				if (src == (*soft)[iter]) {
					shared_ptr<Container> parent = commandList->getParent();
					while (parent.get() != NULL) {
						Dialog* dlg = dynamic_cast<Dialog*>(parent.get());
						if (dlg != NULL) {
							dlg->actionCommand((*softCommand)[iter]);
							return;
						}
						parent = parent->getParent();
					}
				}
			}
		}
		shared_ptr<Command> c = form->getComponentSelectedCommand(commandList);
		shared_ptr<Container> parent = commandList->getParent();
		while (parent.get() != NULL) {
			Dialog* dlg = dynamic_cast<Dialog*>(parent.get());
			if (dlg != NULL) {
				dlg->actionCommand(c);
				return;
			}
			parent = parent->getParent();
		}
	}


}

shared_ptr<Button> MenuBar::createSoftButton()
{
	shared_ptr<Button> b = Button::newV();
	shared_ptr<ActionListener> l = static_pointer_cast<ActionListener>(this->shared_from_this());
	b->addActionListener(l);
	b->setFocusPainted(false);
	b->setFocusable(false);
	updateSoftButtonStyle(b);
	return b;

}

void MenuBar::updateSoftButtonStyle( shared_ptr<Button> b )
{
	shared_ptr<Style> unselectStyle = getUnselectedStyle();
	shared_ptr<Style> s = new Style(*unselectStyle);
	b->setUnSelectedStyle(s);
	b->setPressedStyle(s);
	shared_ptr<Image> image;
	s->setBgImage(image);
	shared_ptr<Border> border;
	s->setBorder(border);
	s->setBackgroundType(Style::BACKGROUND_IMAGE_SCALED);
	if(soft.get()!= NULL && soft->size() > 1){
		s->setMargin(topMargin, bottomMargin, 2, 2);
	}else {
		s->setMargin(0, 0, 0, 0);
		s->setPadding(0, 0, 0, 0);
	}
	
	s->setBgTransparency(0);
}

void MenuBar::setUnSelectedStyle( shared_ptr<Style> style )
{
	if (this->unSelectedStyle.get() != NULL) {
		this->unSelectedStyle->removeStyleListener(this->shared_from_this());
	}
	this->unSelectedStyle = style;
	this->unSelectedStyle->addStyleListener(this->shared_from_this());
	if (this->unSelectedStyle->getBgPainter().get() == NULL) {
		this->unSelectedStyle->setBgPainter(new BGPainter(this->shared_from_this()));
	}
	setShouldCalcPreferredSize(true);
	checkAnimation();

}

void MenuBar::setTransitions( shared_ptr<Transition> transitionIn, shared_ptr<Transition> transitionOut )
{
	this->transitionIn = transitionIn;
	this->transitionOut = transitionOut;
}
shared_ptr<Dimension> MenuBar::calcPreferredSize()
{
	if (soft->size() > 1) {
		shared_ptr<Dimension> d = Container::calcPreferredSize();
		if (((*soft)[0])->getText().get() == NULL || *((*soft)[0]->getText()) == L""
			&& ((*soft)[1]->getText().get() == NULL || *((*soft)[1]->getText()) == (L"")) && (*soft)[0]->getIcon().get() == NULL
			&& (*soft)[1]->getIcon().get() == NULL) 
		{
				d->setHeight(0);
		}
		return d;
	}
	return Container::calcPreferredSize();

}

shared_ptr<Vector<shared_ptr<Button> > > MenuBar::getSoftButtons()
{
	return soft;
}

shared_ptr<String> MenuBar::getUIID()
{
	return new String(L"SoftButton");
}

void MenuBar::addCommand( shared_ptr<Command> cmd )
{
	// prevent duplicate commands which might happen in some edge cases
	// with the select command
	if (commands->contains(cmd)) {
		return;
	}
	// special case for default commands which are placed at the end and
	// aren't overriden later
	if (soft->size() > 2 && cmd == form->getDefaultCommand()) {
		commands->addElement(cmd);
	} else {
		commands->insertElementAt(cmd, 0);
	}
	updateCommands();

}

void MenuBar::addCommand( shared_ptr<Command> cmd, int index )
{
	// prevent duplicate commands which might happen in some edge cases
	// with the select command
	if (commands->contains(cmd)) {
		return;
	}
	commands->insertElementAt(cmd, index);
	updateCommands();

}
shared_ptr<Command> MenuBar::getCommand( int index )
{
	return  commands->elementAt(index);
}

int MenuBar::getCommandCount()
{	
	return commands->size();
}

void MenuBar::removeAllCommands()
{
	commands->removeAllElements();
	directCommand.reset(); // add by jiajing
	updateCommands();

}	

void MenuBar::removeCommand( shared_ptr<Command> cmd )
{
	commands->removeElement(cmd);
	updateCommands();
}

void MenuBar::setMenuCellRenderer( shared_ptr<ListCellRenderer> menuCellRenderer )
{
		this->menuCellRenderer = menuCellRenderer;
}

shared_ptr<Style> MenuBar::getMenuStyle()
{
	return menuStyle;
}

void MenuBar::keyPressed( int keyCode )
{
	if (commands->size() > 0) {
		if (keyCode == Form::leftSK) {
			if (left.get() != NULL) {
				left->pressed();
			}
		} else {
			// it might be a back command or the fire...
			if ((keyCode == Form::rightSK || keyCode == Form::rightSK2)) {
				if (right.get() != NULL) {
					right->pressed();
				}
			} else {
				if (Display::getInstance()->getGameAction(keyCode) == Display::GAME_FIRE) {
					main->pressed();
				}
			}
		}
	}

}

void MenuBar::keyReleased( int keyCode )
{
	if (commands->size() > 0) {
		if (Display::getInstance()->getImplementation()->getSoftkeyCount() < 2
			&& keyCode == Form::leftSK) {
				shared_ptr<List> l = dynamic_pointer_cast<List>(commandList);
				if (l.get() != NULL) {
					shared_ptr<Container> parent = l->getParent();
					while (parent.get() != NULL) {
						Dialog* dlg = dynamic_cast<Dialog*>(parent.get());
						if (dlg != NULL && dlg->isMenu()) {
								return;
						}
						parent = parent->getParent();
					}
				}
				showMenu();
				return;
		} else {
			if (keyCode == Form::leftSK) {
				if (left.get() != NULL) {
					left->released();
				}
				return;
			} else {
				// it might be a back command...
				if ((keyCode == Form::rightSK || keyCode == Form::rightSK2)) {
					if (right.get() != NULL) {
						right->released();
					}
					return;
				} else {
					if (Display::getInstance()->getGameAction(keyCode) == Display::GAME_FIRE) {
						main->released();
						return;
					}
				}
			}
		}
	}

	// allows a back/clear command to occur regardless of whether the
	// command was added to the form
	shared_ptr<Command> c;
	if (keyCode == Form::backSK) {
		// the back command should be invoked
		c = form->getBackCommand();
	} else {
		if (keyCode == Form::clearSK || keyCode == Form::backspaceSK) {
			c = form->getClearCommand();
		}
	}
	if (c.get() !=NULL ) {
		shared_ptr<ActionEvent> ev = new ActionEvent(c, keyCode);
		c->actionPerformed(ev);
		if (!ev->isConsumed()) {
			form->actionCommandImpl(c);
		}
	}

}

void MenuBar::refreshTheme()
{
	Container::refreshTheme();
	String id(L"Menu");
	if (menuStyle->isModified()) {
		menuStyle->merge(UIManager::getInstance()->getComponentStyle(
			id));
	} else {
		menuStyle = UIManager::getInstance()->getComponentStyle(id);
	}
	if (menuCellRenderer.get() != NULL) {
		shared_ptr<List> tmp = List::newV();
		tmp->setListCellRenderer(menuCellRenderer);
		tmp->refreshTheme();
	}
	for (int iter = 0; iter < soft->size(); iter++) {
		updateSoftButtonStyle((*soft)[iter]);
	}

	revalidate();

}

void MenuBar::showMenu()
{
	shared_ptr<MenuDialog> d = MenuDialog::newV();
	d->setDisposeWhenPointerOutOfBounds(true);
	shared_ptr<Style> style = new Style(*menuStyle);
	d->setDialogStyle(style);
	shared_ptr<Style> btnStyle = new Style(*(form->getSoftButtonStyle()));
	d->setSoftButtonStyle(btnStyle);

	menuStyle->removeStyleListener(d->getContentPane());

	d->setTransitionInAnimator(transitionIn);
	d->setTransitionOutAnimator(transitionOut);
	d->setLayout(new BorderLayout());
	d->setScrollable(false);
	d->getMenuBar()->setCommandList(form->createCommandComponent(commands));

	if (menuCellRenderer.get() != NULL){
		List *list = dynamic_cast<List*>(d->getMenuBar()->getCommandList().get());
		if(list != NULL) 
			list->setListCellRenderer(menuCellRenderer);
	}
	d->getContentPane()->getStyle()->setMargin(0, 0, 0, 0);
	d->addComponent(BorderLayout::CENTER, d->getMenuBar()->getCommandList());
	if (Display::getInstance()->isThirdSoftButton()) {
		d->addCommand(form->getSelectMenuItem());
		d->addCommand(form->getCancelMenuItem());
	} else {
		d->addCommand(form->getCancelMenuItem());
		if(soft->size() > 1) {
			d->addCommand(form->getSelectMenuItem());
		}
	}
	d->setClearCommand(form->getCancelMenuItem());
	d->setBackCommand(form->getCancelMenuItem());

	form->showMenuDialog(d);
}

shared_ptr<MenuBar> MenuBar::newV( shared_ptr<Form> form )
{
	shared_ptr<MenuBar> menu = new MenuBar();
	menu->constructV(form);
	return menu;
}

MenuBar::MenuBar()
{
	
}

void MenuBar::setCommandList( shared_ptr<Component> commandList )
{
	this->commandList = commandList;
}

shared_ptr<Component> MenuBar::getCommandList()
{
	return commandList;
}



__GUI_END_NAMESPACE