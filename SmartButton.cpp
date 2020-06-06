
#include <arduino.h>
#include <SmartButton.h>

Button::Button(int pin){
	buttonPin = pin;
	pinMode(buttonPin, INPUT_PULLUP);
	ac_click = 1, ac_doubleClick = 2, ac_longClick = 3, ac_UltralongClick = 4;
	doubleClick_CoolDown = 200, longClick_CoolDown = 400, UltralongClick_CoolDown = 1000;
	ON = 0; OFF = 1;
	state = OFF;
	event_Time = millis(); //evite des bug bisarre pendant qu'on presse le bouton
	click_Time = millis();
	lastClick_Time = click_Time;
	canActionClick = false; //determine si les conditions on été remplit pour renvoier un "click"
	AlreadyReturnLongClick = false;
	AlreadyReturnULTRALongClick = false;
	Action = 0;
}

void Button::setCooldown(int ms_doubleClick, int ms_LongClick, int ms_veryLongclick){
	doubleClick_CoolDown = ms_doubleClick,
	longClick_CoolDown = ms_LongClick,
	UltralongClick_CoolDown = ms_veryLongclick;
}

void Button::check(){
	val = digitalRead(buttonPin);
	Action = 0;
	if(val!=state and (millis()-event_Time)>20){
			state = val;
			event_Time = millis();
			if(state==ON){
				//button state ON
				canActionClick = true; //ca pourrait etre juste un click
				AlreadyReturnLongClick = false; //ou pas
				AlreadyReturnULTRALongClick = false; //ou vrm pas
				// actualise les timers
				lastClick_Time = click_Time;
				click_Time = millis();
			}else{
				//button state OFF
			}
			if(state==ON and (click_Time-lastClick_Time)<doubleClick_CoolDown){
				Action = ac_doubleClick;
				canActionClick = false;
			}
	}
	if(state==ON and (millis()-click_Time)>longClick_CoolDown and AlreadyReturnLongClick == false){
			Action = ac_longClick;
			AlreadyReturnLongClick = true;
			canActionClick = false;
	}
	if(state==ON and (millis()-click_Time)>UltralongClick_CoolDown and AlreadyReturnULTRALongClick == false){
			Action = ac_UltralongClick;
			AlreadyReturnULTRALongClick = true;
			canActionClick = false;
	}
	if(canActionClick and (millis()-click_Time)>doubleClick_CoolDown and state==OFF){
			//renvoie un click si condition préalablement remplie apres une attente de doubleClick_CoolDownms (au cas ou double click)
			Action = ac_click;
			canActionClick = false;
	}
}

bool Button::click(){
	if(ac_click==Action)return true;
	else return false;
	Action = 0;
}
bool Button::doubleClick(){
	if(ac_doubleClick==Action)return true;
	else return false;
	Action = 0;
}
bool Button::longClick(){
	if(ac_longClick==Action)return true;
	else return false;
	Action = 0;
}
bool Button::veryLongClick(){
	if(ac_UltralongClick==Action)return true;
	else return false;
	Action = 0;
}
