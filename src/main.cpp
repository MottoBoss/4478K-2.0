#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "devices.h"
#include "auton.h"
#include "actions.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/adi.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
//#include "pros/motors.h"
#include "pros/motors.hpp"
#include "drive.h"
#include "pros/rtos.hpp"
//#include <optional>
#include <iostream>
#include <string>
using namespace pros;
using namespace lemlib;





/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
	lcd::initialize();
	chassis.calibrate();
    imu.reset();
	lcd::set_text(1, "Press center button to select autonomous");
	lcd::register_btn1_cb(autonSelector); 
	redirect1.set_value(HIGH);
	Clamper.set_value(LOW);
	overclock.set_zero_position_all(40);
	Task dunkTask(startDunk, (void*)"PROS", TASK_PRIORITY_DEFAULT,
                TASK_STACK_DEPTH_DEFAULT,"controls dunk task" );
    dunkerSensor.reset_position();
    dunkerSensor.set_position(40);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	pros::lcd::register_btn1_cb(autonSelector);
    
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */




//FRONT OF THE ROBOT IS THE INTAKE



void autonomous() {
	controller.rumble("-");
	mLefts.tare_position();
	mRights.tare_position();
    release();
	switch (selection) {
	case 0:
		redRight();
		break;
	case 1:
		redLeft();
		break;
	case 2:
		blueLeft();
		break;
	case 3:
		blueRight();
		break;
	case 4:
		progSkills();
		break;
	case 5:
		redRush();
		break;
	case 6:
		blueRush();
		break;
	case 7:
		red4Ring();
		break;
	case 8:
		blue4Ring();
		break;
	}
	
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	bool slow = false; 
	mIntake.set_brake_mode(MotorBrake::coast);
	overclock.set_brake_mode(MotorBrake::hold);
	bool isLiftDown = true;
	overclock.tare_position();
	fourBar1.set_value(LOW);
    
    

	while (true) {
		lcd::print(1, "x: %f", chassis.getPose().x);    
   		lcd::print(2, "y : %f", chassis.getPose().y);
   		lcd::print(3, "theta: %f", chassis.getPose().theta);
		controller.set_text(0, 0, std :: to_string(mIntake.get_actual_velocity()));
		lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

		// Tank control scheme
		// Passes joystick values into tank drive
		delay(20); // Run for 20 ms then update
        drive();

		if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){ //handles clamp
			toggleClamp();
		}
		
		if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_DOWN)){ //raises lift when it is down
			isLiftDown  = !isLiftDown;
			if(isLiftDown){
				lift();
			} 
			else{ //lowers lift when it is up
				lower();
			} 
		}
		
		if(controller.get_digital(E_CONTROLLER_DIGITAL_R1)){    
			mIntake.move(127);
		} //move intake forward
		else if(controller.get_digital(E_CONTROLLER_DIGITAL_R2)){   
			mIntake.move(-127);
		}//move intake backward
		else{
			mIntake.brake();
		}    //stop intake

		if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
           dunk();
		}
		if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)){//emergency stop for dunker
			dunkItHoe = false;
		}

		if(controller.get_digital(E_CONTROLLER_DIGITAL_L2)){
			toggleRedirect();
		}	
		
		if(controller.get_digital(E_CONTROLLER_DIGITAL_L1)){
			dunkHold();
		}
        //controller.set_text(0, 0, "Positon: %f", (dunkerSensor.get_position()));
     
        //controller.set_text(0,0,"%d",dunkerSensor.get_position() );
	}
}