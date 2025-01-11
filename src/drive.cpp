#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "devices.h"


bool pressedClamp= false;
bool pressedRedirect= true;//redirects when false
//variable pressed ensures we can use the same button on controller  
//to toggle pistons either way: true is open, false is closed
void toggleClamp(){
  			pressedClamp = !pressedClamp;
			if(pressedClamp){											  						  
				Clamper.set_value(HIGH);							  
			}	
			else if(!pressedClamp){
				Clamper.set_value(LOW);
			}
}
void toggleRedirect(){
	  		pressedRedirect = !pressedRedirect;
			if(pressedRedirect){											  						  
				redirect1.set_value(HIGH);	
			}	
			else if(!pressedRedirect){
				redirect1.set_value(LOW);
			}
}
void drive(){
    int leftVal = controller.get_analog(ANALOG_LEFT_Y);
		int rightVal = controller.get_analog(ANALOG_RIGHT_Y);
		chassis.tank(leftVal, rightVal);
		mLefts.move(driveCurve.curve(leftVal));
		mRights.move(driveCurve.curve(rightVal));
}