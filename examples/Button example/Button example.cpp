/*  exemple for the library smart button:
this library allow to simply detect button(s) actions.
this exemple show the action for one button but you can add other button and combine it.
*/

#include <arduino.h>
// include the library
#include <SmartButton.h>

//create an instance of the class on pin 10
Button MyButton = Button(10);

void setup() {
  Serial.begin(9600); // open a serial connection to your computer
  Serial.println("hello world");
  //optionnal: you can change the timer.
  //the timer are in this order: double click event, long click event, very long click event.
  MyButton.setCooldown(200, 500, 1000); //this are the default value
}

void loop(){
  //to check the button, you nead to call this function before the functions for the actions
	MyButton.check();

  //functions for the actions:
	if(MyButton.click()) Serial.println("click");  //if click event
	if(MyButton.doubleClick()) Serial.println("double Click"); //if double click event
	if(MyButton.longClick()) Serial.println("long Click"); //if long click event
	if(MyButton.veryLongClick()) Serial.println("very Long Click");  //if very long click event
}
