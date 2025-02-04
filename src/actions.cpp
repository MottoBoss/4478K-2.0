#include "actions.h"
#include "devices.h"
//#include "pros/llemu.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
bool driveDunk= false;
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
			while(dunkerSensor.get_angle() < 230 * 100 && overclock.get_actual_velocity() > 0){ //stops dunk if stuck or reaches target
				controller.rumble(".");
				delay(20);
			}

			//bring it back
			overclock.move(-127);
			delay(500);
			while(dunkerSensor.get_position() >50 * 100 && overclock.get_actual_velocity() > 1){//stops dunk if stuck or reaches target
				delay(20);
				controller.rumble(".");
			}
			overclock.move(0);
			overclock.brake();
			//lcd::print(4, "DONE: %d, %d", dunkerSensor.get_angle(), overclock.get_actual_velocity());
			dunkItHoe = false;
			
		}
		delay(20);
	}

	delay(20);
}

void dunkHold(void* param){
	overclock.set_brake_mode(MotorBrake::hold); 
while(1){
	
	
	if(driveDunk){ //activates when held
		
		
		overclock.move(127); //start dunk
		while(driveDunk){
			delay(20);
			lcd::print(4, "REALLY DUNKING: %i, %d", dunkerSensor.get_position(), overclock.get_brake_mode());
			if(dunkerSensor.get_position() > 15000){ //check if motor got stuck
				overclock.brake(); //stop motor becasue it stuck
				overclock.move(0);
			}
			
		}
	}
	else{ //activates when button is not held
		if(dunkerSensor.get_position() > 20 * 100){ //only run if not at down position
			overclock.move(-90); //bring dunker back
				while(!driveDunk){
					lcd::print(4, "Coming back: %i, %d", dunkerSensor.get_position(), overclock.get_brake_mode());
					delay(20);
					if(dunkerSensor.get_position() < 2 * 100 && overclock.get_actual_velocity() < 1){//check if motor got stuck
						overclock.brake(); //stop motor becasue it stuck
						
					}
				}
			}
		}
	}
	
	
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