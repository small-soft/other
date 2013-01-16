/*
 * AMWindow.h
 *
 *  Created on: 2010-2-8
 *      Author: qing.chen
 */

#ifndef AMWINDOW_H_
#define AMWINDOW_H_

#include <coecntrl.h>

class AMWindow : public CCoeControl
	{
public:
	void ActivateGc() const;
	
	RWindow& Window() const;
	
	void DeactivateGc() const;
	};

#endif /* AMWINDOW_H_ */
