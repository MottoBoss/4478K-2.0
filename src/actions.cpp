#include "devices.h"
void grab(){
	Clamper.set_value(HIGH);
}
void release(){
	Clamper.set_value(LOW);
}
void intakeDist(){
	int i = 2;
	mIntake.move(127);
	while(i > 0){
		if(sDist.get_distance()*10 < 5 && sDist.get_object_velocity() > 0){ //5 is an estimate in cm. don't know where dist sensor will be
			mIntake.brake();
			i--;
		}
	}
}

void lift(){
	fourBar1.set_value(HIGH);

}
void lower(){
	fourBar1.set_value(LOW);
	
}
bool dunkItHoe = false;
void dunk(){
	dunkItHoe = true;
}
void startDunk(void* param){
	while(true){
		while(dunkItHoe){//task starts

			 // go to dunk it
				overclock.move(127);

			delay(200);
			while(dunkerSensor.get_angle() < 230 * 100 && overclock.get_actual_velocity() > 0){
				controller.rumble(".");
				delay(20);
			}

			 //bring it back
				overclock.move(-127);
				delay(200);
			while(dunkerSensor.get_angle() >50 * 100 && overclock.get_actual_velocity() > 1){
				delay(20);
			}
			overclock.brake();
			dunkItHoe = false;
	}
		
		delay(20);
	}
	delay(20);
	}
 

void intakeColorRed(){
	if(sOpt.get_hue() == 0){
		intakeDist();
	}
	else{
		mIntake.brake();
	}
	
}

void intakeColorBlue(){
	if(sOpt.get_hue() == 240){
		intakeDist();
	}
	else{
		mIntake.brake();
	}
}