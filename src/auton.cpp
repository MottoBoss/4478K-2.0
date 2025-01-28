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
    if(selection <= 7){
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
    case 7:
        pros::lcd::set_text(2, "Red 4 ring");
        break;
    case 8:
        pros::lcd::set_text(2, "Blue 4 ring");
        break;
    }
}
void redRight(){ //mogo side
    chassis.setPose(-65.1,-5, 270);
    chassis.turnToHeading(310, 500);
    chassis.waitUntilDone();
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
    chassis.setPose(-15,  -28, chassis.getPose().theta);
    chassis.moveToPoint(-28.6, -53.914, 3000);//pickup ring to put on Mogo
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
    chassis.setPose(-65.1,5, 270);
    chassis.turnToHeading(230, 500);
    chassis.waitUntilDone();
    dunk();
    chassis.setPose(-65.1,5, 225);
    delay(500); //score alliance stake
    overclock.move_absolute(10, 100);//redundancy to ensure arm comes back down
    chassis.moveToPose(-27, 24.5,235, 3500, {.forwards = false}); //move to mogo
    chassis.waitUntilDone();
    delay(75);
    grab();
    // lcd::print(1, "x: %f", chassis.getPose().x);    
    // lcd::print(2, "y : %f", chassis.getPose().y);
    // lcd::print(3, "theta: %f", chassis.getPose().theta);
    delay(75);
    mIntake.move(127); 
    chassis.setPose(-15,  28, chassis.getPose().theta);
    chassis.moveToPoint(-28.6, 53.914, 3000);//pickup ring to put on Mogo
    chassis.waitUntilDone();
    //release();
    chassis.moveToPose(-12, 46, 180, 2000, {.forwards = false}); //go to goal
    chassis.waitUntilDone();
    grab();
    chassis.moveToPose(-18, 1.98, 160, 3000); //touch bar
    chassis.waitUntilDone();
    lift();
}


void redLeft(){ //ring side
    chassis.setPose(-65.1,5, 270);
    chassis.turnToHeading(230, 500);
    chassis.waitUntilDone();
    dunk();
    chassis.setPose(-65.1,5, 225);
    delay(500); //score alliance stake
    overclock.move_absolute(10, 100);//redundancy to ensure arm comes back down
    chassis.moveToPose(-27, 24,235, 2800, {.forwards = false}); //move to mogo
    chassis.waitUntilDone();
    delay(75);
    grab();
    // lcd::print(1, "x: %f", chassis.getPose().x);    
    // lcd::print(2, "y : %f", chassis.getPose().y);
    // lcd::print(3, "theta: %f", chassis.getPose().theta);
    delay(75);
    mIntake.move(127);
    chassis.setPose(-15,  28, chassis.getPose().theta);
    chassis.moveToPoint(-22.6, 53.914, 3000);//pickup ring to put on Mogo
    chassis.waitUntilDone();
    chassis.moveToPose(-6, 52, 0, 2000); //go to middle ring #1
    chassis.moveToPoint(-15, 47, 1000); //preprare to rush ring#2
    chassis.moveToPose(-6, 52, 0, 2000);//rush ring #2
    chassis.moveToPose(-18, 1.98, 160, 3000); //touch bar
    chassis.waitUntilDone();
    lift();
}


void blueRight(){ //ring side
    chassis.setPose(-65.1,-5, 270);
    chassis.turnToHeading(310, 1000);
    chassis.waitUntilDone();
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
    chassis.setPose(-15,  -28, chassis.getPose().theta);
    mIntake.move(127);
    chassis.moveToPoint(-28.6, -53.914, 3000);//pickup ring to put on Mogo
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
    mIntake.move(280); //score on alliance stake
    delay(500);
    chassis.moveToPoint(-60.241, 1.705, 1000);
    chassis.waitUntilDone();
    release();
    chassis.moveToPose(-46.897, 19.678, 160, 3000, {.forwards = false}); //go to goal
    chassis.waitUntilDone();
    delay(100);
    grab();
    mIntake.move(127);
    chassis.moveToPoint(-22.593, 28.722, 1500);//pick up first ring
    chassis.moveToPose(-20.912, 49.303, 270, 3000); //go to 2nd ring
    chassis.moveToPose(-39.912, 49.953, 270, 2000); //pick up 2nd ring
    chassis.moveToPoint(-58.972, 49.622, 2000); //3rd & 4th ring
    chassis.moveToPose(-58.257, 64.489, 325, 1000, {.forwards = false});//drop 1st goal into corner
    chassis.waitUntilDone();
    controller.clear();
    lcd::print(1, "θ:%f, x: %f, y: %f", chassis.getPose().theta, chassis.getPose().x, chassis.getPose().y);
    release();
    chassis.setPose(-49, 55.000, chassis.getPose().theta);
    delay(100);
    lcd::print(2, "θ: %f, x: %f, y: %f", chassis.getPose().theta, chassis.getPose().x, chassis.getPose().y);
     
    //go towards 2ng Mogo
   // chassis.moveToPoint(-55.674, -0.515, 2000, {.forwards = false});
    chassis.moveToPoint(-32, 41 , 500);
    chassis.moveToPose(-47.5, -16.713, 0, 3500, {.forwards=false});
    chassis.waitUntilDone();
    chassis.setPose(-47.5,-28.713,0);
    delay(500);
    grab(); //grab 2nd mogo
    delay(100);
    chassis.moveToPoint(-16.593, -23.595, 2000); //1st ring
    chassis.moveToPoint(-16.593, -47, 1000);
    chassis.moveToPose(-39.936, -48.9,270,   2000);//2nd ring
    chassis.moveToPose(-60, -48.9,270,  4000); //3rd & 4th ring
    chassis.waitUntilDone();
    chassis.setPose(-62.8, -46.8, 270);
    chassis.moveToPose(-61.957, -63.014,40, 4000, {.forwards = false}); //drop off 2nd mogo in corner
    chassis.waitUntilDone();
    release(); 
    printf("time %i",c::millis()/1000);
    chassis.setPose(-62.5, -62.5, 40);
    delay(200);
    chassis.moveToPoint(30.113, -57.276, 5000);//pick up ring
    delay(2000);
    mIntake.brake();
    chassis.moveToPose(44, -0.5, 180, 5000, {.forwards=false});
    chassis.waitUntilDone();
    chassis.setPose(47, -0.5, 180);
    grab();
    mIntake.move(127);
    delay(2000); //score ring
    release();
    //start pushing in goals
    chassis.moveToPoint(56.773, 15, 1000);
    chassis.moveToPoint(63.363, 66.554, 2000);
    chassis.moveToPoint(66.271,-16.632, 5000 );
    chassis.moveToPose(67.165, -64.562, -45, 5000);//push in last goal
    release();
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
void blue4Ring(){

}
void red4Ring(){
    chassis.setPose(-51, 23, 90);
    /*
    while (1){
    lcd::print(1, "x: %f", chassis.getPose().x);    
    lcd::print(2, "y : %f", chassis.getPose().y);
    lcd::print(3, "theta: %f", chassis.getPose().theta);
    delay(200);
    pros::lcd::clear_line(1);
    pros::lcd::clear_line(2);
    pros::lcd::clear_line(3);
    delay(200);
    //lcd::clear();
    }
    */
    chassis.moveToPoint(-70, 22.5, 3000, {.forwards = false});
    grab();
    chassis.waitUntilDone();
    chassis.turnToHeading(195, 3000);
    mIntake.move(127);
    chassis.moveToPose(-78.28, -2.62, 197, 3000);
    chassis.moveToPoint(-92.3, -6.1, 3000);
    chassis.moveToPoint(-93.1, 2.4, 3000);
    chassis.moveToPose(-90, 25, 360, 3000);
    mIntake.brake();
    lift();
}