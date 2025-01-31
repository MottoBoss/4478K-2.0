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
			while(dunkerSensor.get_angle() >50 * 100 && overclock.get_actual_velocity() > 1){//stops dunk if stuck or reaches target
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
while(1){
	
	delay(20);
	if(driveDunk){
		lcd::print(4, "DONE: %d, %d", dunkerSensor.get_angle(), overclock.get_actual_velocity());
		overclock.move(127);
	
	}
	else{
		if(dunkerSensor.get_angle() > 20 * 100){ //only run if not at down position
		lcd::print(4, "AHHHHHH: %d, %d", dunkerSensor.get_angle(), overclock.get_actual_velocity());
		overclock.move(-127);
		delay(50);
			while(dunkerSensor.get_angle() > 20 * 100 && overclock.get_actual_velocity() > 1){//stops dunk if stuck or reaches target
				delay(20);
			}
			overclock.move(0);
			overclock.brake();
			lcd::print(4, "No way this i srunning: %d, %d", dunkerSensor.get_angle(), overclock.get_actual_velocity());
		
			}
		else{
			overclock.move(0);
			overclock.brake();
			lcd::print(4, "No way this i srunning: %d, %d", dunkerSensor.get_angle(), overclock.get_actual_velocity());
		
		}
	}
	
	
}
}
void dunkReturn(){
	overclock.move(-127);
	delay(500);
	while(dunkerSensor.get_angle() >50 * 100 && overclock.get_actual_velocity() > 1){//stops dunk if stuck or reaches target
		delay(20);
		controller.rumble(".");
	}
	overclock.move(0);
	overclock.brake();
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