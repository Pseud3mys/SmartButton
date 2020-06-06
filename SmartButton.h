#ifndef checkButton_h
#define checkButton_h

#include "Arduino.h"
#include "SmartButton.h"

class Button
{
public:
	Button(int pin);
	void setCooldown(int ms_doubleClick, int ms_LongClick, int ms_veryLongclick);
	void check();
	bool click();
	bool doubleClick();
	bool longClick();
	bool veryLongClick();
private:
	int buttonPin;
	int ac_click, ac_doubleClick, ac_longClick, ac_UltralongClick;
	int doubleClick_CoolDown, longClick_CoolDown, UltralongClick_CoolDown;
	int ON; int OFF;
	int val;
	int state;
	long event_Time; //evite des bug bisarre pendant qu'on presse le bouton
	long click_Time;
	long lastClick_Time;
	bool canActionClick; //determine si les conditions on été remplit pour renvoier un "click"
	bool AlreadyReturnLongClick;
	bool AlreadyReturnULTRALongClick;
	int Action;
};

#endif
