#include "devices.h"

using namespace pros;
using namespace lemlib;
Controller controller(E_CONTROLLER_MASTER);
MotorGroup mLefts({-16, -20, 10}); // left motors forward (negitve)
MotorGroup mRights({1, -2, 3}); // right motors reverse (positve)
Motor mIntake(15, pros::MotorGearset::blue);
Motor overclock(-19, pros::MotorGearset::green);
Imu imu(4);
//Distance sDist(1);
//Optical sOpt(2);
adi::Port Clamper ('H', E_ADI_DIGITAL_OUT); //even different than PROS + EZTemplate or PROS + OkapiLib
adi::Port fourBar1 ('G', E_ADI_DIGITAL_OUT); //even different than PROS + EZTemplate or PROS + OkapiLib
adi::Port redirect1 ('F', E_ADI_DIGITAL_OUT); //even different than PROS + EZTemplate or PROS + OkapiLib

Rotation dunkerSensor(9);
// drivetrain settings
Drivetrain drivetrain(&mLefts, // left motor group
                              &mRights, // right motor group
                              11.25, // 11.25 inch track width
                              Omniwheel::NEW_275, // using new 2.75" omnis
                              450, // drivetrain rpm is 450
                              2 // horizontal drift is 2 (for now)
);

OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);


// lateral PID controller
ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
ExpoDriveCurve throttleCurve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
ExpoDriveCurve steerCurve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);
ExpoDriveCurve driveCurve(5, 12, 1.03);

// create the chassis
Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors, // odometry sensors
						&throttleCurve, 
						&steerCurve
);

