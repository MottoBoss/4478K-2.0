#ifndef ACTIONS_H
#define ACTIONS_H
 void intakeDist();
 void intakeColor();
 void grab();
 void release();
 void lift();
 void lower();
 void dunk();
 void returnDunk();
 void startDunk(void* param);
 extern bool dunkItHoe;
 extern bool driveDunk;
 void dunkHold(void* param);
#endif