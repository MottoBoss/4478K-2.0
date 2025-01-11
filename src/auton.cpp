#include "devices.h"
#include "lemlib/chassis/chassis.hpp"
#include "liblvgl/llemu.hpp"
#include "actions.h"
#include "pros/llemu.hpp"

int selection = 0;
/*
 0 = RedRight Mogo
 1 = RedLeft Ring
 2 = BlueLeft Mogo
 3 = BlueRight Ring
 4 = Prog skills
 5 = Red Goal Rush
 6 = Blue Goal Rush
*/
void autonSelector(){
	if(selection <= 4){
		selection++;
	} else {
		selection = 0;
	}
	switch(selection){
	case 0:
		pros::lcd::set_text(2, "RedRight(MOGO Side)");
		break;
	case 1:
		pros::lcd::set_text(2, "RedLeft(Ring Side)");
		break;
	case 2:
		pros::lcd::set_text(2, "BlueLeft(MOGO side)");
		break;
	case 3:
		pros::lcd::set_text(2, "BlueRight(Ring Side)");
		break;
	case 4:
		pros::lcd::set_text(2, "Prog Skills");
		break;
	case 5:
		pros::lcd::set_text(2, "Red Goal Rush");
		break;
	case 6:
		pros::lcd::set_text(2, "Blue Goal Rush");
		break;
	}
}
void redRight(){ //mogo side
    chassis.setPose(-65.1,-5, 315);
	dunk();
    chassis.setPose(-65.1,-5, 315);
    delay(500); //score alliance stake
    overclock.move_absolute(10, 100);//redundancy to ensure arm comes back down
    chassis.moveToPose(-27, -21,305, 4000, {.forwards = false}); //move to mogo
    chassis.waitUntilDone();
    delay(75);
    grab();
    lcd::print(1, "x: %f", chassis.getPose().x);    
	lcd::print(2, "y : %f", chassis.getPose().y);
    lcd::print(3, "theta: %f", chassis.getPose().theta);
    delay(75);
    mIntake.move(127);
	chassis.setPose(-27,  -21, chassis.getPose().theta);
    chassis.moveToPoint(-21.6, -53.914, 3000);//pickup ring to put on Mogo
    chassis.waitUntilDone();
    release();
    chassis.moveToPose(-5, -46, 180, 2000, {.forwards = false}); //go to goal
    chassis.waitUntilDone();
    grab();
    chassis.moveToPose(-18, -1.98, 20, 3000); //touch bar
    chassis.waitUntilDone();
    lift();
}

void blueLeft(){ //mogo side
    chassis.setPose(-65.1,5, 225);
	dunk();
    chassis.setPose(-65.1,5, 225);
    delay(500); //score alliance stake
    overclock.move_absolute(10, 100);//redundancy to ensure arm comes back down
    chassis.moveToPose(-27, 21,235, 3500, {.forwards = false}); //move to mogo
    chassis.waitUntilDone();
    delay(75);
    grab();
    lcd::print(1, "x: %f", chassis.getPose().x);    
	lcd::print(2, "y : %f", chassis.getPose().y);
    lcd::print(3, "theta: %f", chassis.getPose().theta);
    delay(75);
    mIntake.move(127);
	chassis.setPose(-27,  21, chassis.getPose().theta);
    chassis.moveToPoint(-21.6, 53.914, 3000);//pickup ring to put on Mogo
    chassis.waitUntilDone();
    release();
    chassis.moveToPose(-5, 46, 180, 2000, {.forwards = false}); //go to goal
    chassis.waitUntilDone();
    grab();
    chassis.moveToPose(-18, -1.98, 160, 3000); //touch bar
    chassis.waitUntilDone();
    lift();
}


void redLeft(){ //ring side
    chassis.setPose(-65.1,5, 225);
	dunk();
    chassis.setPose(-65.1,5, 225);
    delay(500); //score alliance stake
    overclock.move_absolute(10, 100);//redundancy to ensure arm comes back down
    chassis.moveToPose(-27, 21,235, 3500, {.forwards = false}); //move to mogo
    chassis.waitUntilDone();
    delay(75);
    grab();
    lcd::print(1, "x: %f", chassis.getPose().x);    
	lcd::print(2, "y : %f", chassis.getPose().y);
    lcd::print(3, "theta: %f", chassis.getPose().theta);
    delay(75);
    mIntake.move(127);
	chassis.setPose(-27,  21, chassis.getPose().theta);
    chassis.moveToPoint(-21.6, 53.914, 3000);//pickup ring to put on Mogo
    chassis.waitUntilDone();
    chassis.moveToPose(-5, 52, 0, 1500); //go to middle ring #1
    chassis.moveToPoint(-15, 47, 1000); //preprare to rush ring#2
    chassis.moveToPose(-5, 52, 0, 2000);//rush ring #2
    chassis.moveToPose(-18, 1.98, 160, 3000); //touch bar
    chassis.waitUntilDone();
    lift();
}


void blueRight(){ //ring side
    chassis.setPose(-65.1,-5, 315);
	dunk();
    chassis.setPose(-65.1,-5, 315);
    delay(500); //score alliance stake
    overclock.move_absolute(10, 100);//redundancy to ensure arm comes back down
    chassis.moveToPose(-27, -21,305, 3500, {.forwards = false}); //move to mogo
    chassis.waitUntilDone();
    delay(75);
    grab();
    lcd::print(1, "x: %f", chassis.getPose().x);    
	lcd::print(2, "y : %f", chassis.getPose().y);
    lcd::print(3, "theta: %f", chassis.getPose().theta);
    delay(75);
	chassis.setPose(-27,  -21, chassis.getPose().theta);
    mIntake.move(127);
    chassis.moveToPoint(-21.6, -53.914, 3000);//pickup ring to put on Mogo
    chassis.waitUntilDone();
    chassis.moveToPose(-5, -52, 0, 1500); //go to middle ring #1
    chassis.moveToPoint(-15, -47, 1000); //preprare to rush ring#2
    chassis.moveToPose(-5, -52, 0, 2000);//rush ring #2
    chassis.moveToPose(-18, -1.98, 20, 3000); //touch bar
    chassis.waitUntilDone();
    lift();
}

void progSkills(){
    controller.set_text(1, 1, "running skills");
    mLefts.tare_position();
    mRights.tare_position();
    chassis.setPose(-64.241, -0.705, 90);
    mIntake.move(280);
    delay(200);
    chassis.moveToPoint(-64.241, 1.705, 1000);
   
    chassis.moveToPose(-46.897, 19.678, 160, 3000, {.forwards = false}); //go to goal
    chassis.waitUntilDone();
    delay(100);
    grab();
    chassis.moveToPoint(-22.593, 28.722, 2000);//pick up first ring
    chassis.moveToPose(-25.912, 49.993, 270, 3000); //go to 2nd ring
    chassis.moveToPose(-39.912, 49.653, 270, 750); //pick up 2nd ring
    chassis.waitUntilDone();
    delay(2000);
    chassis.moveToPoint(-58.972, 49.622, 2000); //3rd & 4th ring
    chassis.moveToPose(-58.257, 64.489, 325, 1000, {.forwards = false});//drop 1st goal into corner
    chassis.waitUntilDone();
    controller.clear();
    controller.set_text(1, 1, std:: to_string(chassis.getPose().theta));
    release();
    delay(100);
     //start of auton that just pushes goal
    mLefts.tare_position();
    mRights.tare_position();
    chassis.setPose(-62.9, 60.675, chassis.getPose().theta);
    delay(50);
    chassis.moveToPoint(17.138, 45.25, 2000,{.forwards = true});    
    chassis.moveToPoint(50.564, 18,  2500); //get behind 2nd goal
    chassis.moveToPoint((67.5), 65, 2500);
    chassis.moveToPoint(61, 57, 2500, {.forwards = false});
    chassis.moveToPoint(59, 4, 4000);
    chassis.moveToPose(90.864, -59.77, 85, 3900); //score 3rd goal
    chassis.moveToPoint(56, -47, 2500, {.forwards = false});
    chassis.moveToPose(-19.793, -30.913, 320, 4000);
    chassis.moveToPose(-39, -12, 200, 4000);
    chassis.moveToPoint(-64.088, -74.139,2000);//score 4th goal
    chassis.moveToPoint(-64, -53, 2500, {.forwards = false});
    chassis.moveToPoint(-22, -22, 1000);
    mIntake.brake();
    //start to go to second goal
    /*
    chassis.moveToPose(-47.175,-18.129,270, 3500);
    grab();*/
    //end of good auton to start push goal auton
    /*
   
    */
    /*
    //code to finish for good auton skills
    //go towards 2ng Mogo
    chassis.moveToPoint(-55.674, -0.515, 2000, {.forwards = false});
    chassis.moveToPose(-59.864, -19.983, 30, 1000, {.forwards=false});
    chassis.waitUntilDone();
    delay(1000);
    grab();
    delay(100);
    chassis.moveToPoint(-22.593, -24.395, 2000); //1st ring
    chassis.moveToPose(-35.936, -49.326,270,  2000);//2nd ring
    chassis.moveToPoint(-63.351, -49.136, 1000); //3rd & 4th ring
    chassis.moveToPose(-65.057, -63.814,45, 1000, {.forwards = false}); //drop off 2nd mogo in corner
    chassis.waitUntilDone();
    release();
    */
    /* old "20pt" skills
    chassis.setPose(-53, 0, 90);
    mIntake.move(127);
    chassis.moveToPose(-40.375, 13.262, 45, 1000);
    chassis.moveToPose(-76.7, 66.2, 320, 2500); //score 1st goal
    chassis.moveToPoint(17.138, 37.25, 2000);
    chassis.moveToPoint(56.564, 18,  1300); //get behind 2nd goal
    chassis.moveToPoint((67.5), 65, 2500);
    chassis.moveToPoint(59, 57, 2500, {.forwards = false});
    chassis.moveToPoint(49, 4, 4000);
    chassis.moveToPose(88.864, -59.77, 85, 4000); //score 3rd goal
    chassis.moveToPoint(56, -47, 2500, {.forwards = false});
    chassis.moveToPose(-19.793, -30.913, 320, 4000);
    chassis.moveToPose(-43, -15, 200, 4000);
    chassis.moveToPoint(-64.088, -74.139,2000);//score 4th goal
    chassis.moveToPoint(-64, -53, 2500, {.forwards = false});
    chassis.moveToPoint(-22, -22, 1000);
    mIntake.brake();*/
}
void redRush(){
    chassis.setPose(-55.5, -64.1, 90);
    chassis.moveToPose(-5, -50, 55, 2000, {.forwards= true, .lead = 0.7,.minSpeed = 100,.earlyExitRange = 8});//get to mogo 
    delay(1950);
    overclock.move(127);
    chassis.moveToPoint(-18, -60, 800, {.forwards= false, .minSpeed = 127});//bring mogo back to our side
    chassis.waitUntilDone();
    dunk();// dunking to bring the dunker back in position
    mIntake.move(127);
    chassis.turnToPoint(-27, -38, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-27, -38, 2000);
    delay(1000);
    mIntake.brake();
    chassis.turnToHeading(200, 1000);
    chassis.moveToPose(-23.7, -29, 180, 2000, {.forwards = false});//get to mogo
    chassis.waitUntilDone();
    grab();
    mIntake.move(127);
    chassis.moveToPose(-18, -1.98, 20, 3000, {.forwards = false}); //touch bar
    chassis.waitUntilDone();
    lift();
}
void blueRush(){
    chassis.setPose(-55.5, 64.1, 90);
    chassis.moveToPose(-5, 50, 125, 2000, {.forwards= true, .lead = 0.7,.minSpeed = 100,.earlyExitRange = 8});//get to mogo 
    delay(1950);
    overclock.move(127);
    chassis.moveToPoint(-18, 60, 800, {.forwards= false, .minSpeed = 127});//bring mogo back to our side
    chassis.waitUntilDone();
    dunk();// dunking to bring the dunker back in position
    mIntake.move(127);
    chassis.turnToPoint(-27, 38, 1000);
    chassis.waitUntilDone();
    chassis.moveToPoint(-27, 38, 2000);
    delay(1000);
    mIntake.brake();
    chassis.turnToHeading(340, 1000);
    chassis.moveToPose(-23.7, 29, 0, 2000, {.forwards = false});//get to mogo
    chassis.waitUntilDone();
    grab();
    mIntake.move(127);
    chassis.moveToPose(-18, 1.98, 160, 3000, {.forwards = false}); //touch bar
    chassis.waitUntilDone();
    lift();
}