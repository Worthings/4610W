// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// gyroo                inertial      6               
// intake               motor         11              
// catapult             motor         20              
// leftwing             digital_out   A               
// intakepistonb        digital_out   B               
// rightwing            digital_out   H               
// Controller1          controller                    
// RotationRight        rotation      21              
// RotationLeft         rotation      18              
// Opticall             optical       7               
// backleft             motor         17              
// middleleft           motor         16              
// frontleft            motor         19              
// backright            motor         14              
// middleright          motor         13              
// frontright           motor         12              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// defining our functions 


void forwardPIDD(float setpoint) {
  float error = setpoint - backleft.position(degrees);
  float power;
  float i = 1;
  double kP = 0.11;
  while (abs(error) > i) {
    error = setpoint - backleft.position(degrees);
    power = error * kP;
    Brain.Screen.printAt(60, 15, "%f", backleft.position(degrees));
    setBase(power);
  }
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(60, 15, "%f", backleft.position(degrees));
  stopBase();
}

void autofire() {
  while (true) {
  if (Opticall.hue() < 105 && Opticall.hue() > 65) {
    catapult.spin(forward, 50, pct);
    Brain.Screen.print("Hue: %.2f", Opticall.hue());
    Brain.Screen.setCursor(2,2);
  }
  else {
    catapult.stop();
    Brain.Screen.print("Hue: %.2f", Opticall.hue());
    Brain.Screen.setCursor(2,2);
  }

}
  wait(10, msec);
  Brain.Screen.clearScreen();
}

void sensordisplays () {
  while (true) {
    Brain.Screen.printAt(15, 15, "%f", RotationRight.position(degrees));
    Brain.Screen.printAt(30, 30, "%f", RotationLeft.position(degrees));
    Brain.Screen.printAt(45, 45, "%f", gyroo.heading(degrees));
    Brain.Screen.printAt(60, 60, "Hue: %.2f", Opticall.hue());
    wait(10,msec);
    Brain.Screen.clearScreen();
  }
}

void clearmotors () {
  frontleft.resetPosition();
  frontright.resetPosition();
  backleft.resetPosition();
  backright.resetPosition();
  middleleft.resetPosition();
  middleright.resetPosition();
}

void clearall() {
  frontleft.resetPosition();
  frontright.resetPosition();
  backleft.resetPosition();
  backright.resetPosition();
  middleleft.resetPosition();
  middleright.resetPosition();
  gyroo.resetHeading();
  RotationLeft.resetPosition();
  RotationRight.resetPosition();
}

void setwings(int setpoint) {
  leftwing.set(setpoint);
  rightwing.set(setpoint);
}

void setintake(int setpoint) {
  intakepistonb.set(setpoint);
}

void setall(int setpoint) {
  leftwing.set(setpoint);
  rightwing.set(setpoint);
  intakepistonb.set(setpoint);
}

void pre() {
  clearall();
  // thread d(autofire);
  Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print("Calibrating sensors...");
  intakepistonb.set(false);
  gyroo.calibrate();
  wait(2.5, seconds);
  Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print("      We're live!       ");
  wait(3, seconds);
  Controller1.Screen.setCursor(2,2);
  Controller1.Screen.print("      Go Luca !!!       ");
}

void defensive() {
  clearall();
  clearall();
  // setintake(true);
  // intake.spin(forward, 100, pct);
  // wait(.3, seconds);
  // intake.stop();
  forwardPIDD(2100);
  // setintake(false);
  clearall();
  gyroo.setHeading(0,degrees);
  turnPID(90, 100, -1);
  clearmotors();
  forwardPIDD(200);
  clearmotors();
  forwardPIDD(-200);
  turnPID(-50, 100, -1);
}

void stockD() {
  clearall();
  turnPID(29, 100, -1);
  forwardPIDD(1220);
  intake.spin(reverse, 100, pct);
  wait(.3,sec);
  intake.stop();
  turnPID(27, 90, -1);
  wait(.1, sec);
  forwardPIDD(-100);
  clearall();
  setwings(true);
  clearmotors();
  turnPID(180, 75, -1);
  turnPID(360, 80, -1);
  wait(.01,sec);
  setwings(false);
  turnPID(440, 90, -1);
  clearmotors();
  forwardPIDD(-815);
  turnPID(445, 90, -1);
  forwardPIDD(-1630);
  Controller1.Screen.print("simple defensive COMPLETE!");
  // turnPID(, 100, -1);
  // wait(.1, sec) ;
  // clearall();
  // forwardPIDD(-1500);
}

void stockO() {
  clearall();
  turnPID(-29, 100, -1);
  forwardPIDD(-1320);
  intake.spin(reverse, 100, pct);
  wait(.3,sec);
  intake.stop();
  turnPID(-27, 90, -1);
  wait(.1, sec);
  forwardPIDD(-100);
  clearall();
  setwings(true);
  clearmotors();
  turnPID(-180, 75, -1);
  turnPID(-360, 80, -1);
  wait(.01,sec);
  setwings(false);
  turnPID(-440, 90, -1);
  clearmotors();
  forwardPIDD(815);
  turnPID(-445, 90, -1);
  forwardPIDD(-1630);
  Controller1.Screen.print("simple offensive COMPLETE!");
  // turnPID(, 100, -1);
  // wait(.1, sec) ;
  // clearall();
  // forwardPIDD(-1500);
}

void offensive() {
  // begin route
    // setintake(true);
    // intake.spin(forward, 100, pct);
    // wait(.2, seconds);
    // intake.stop();
    // wait(.1, seconds);
  // turn to net
  turnPID(-50, 15, -1);
  clearall();
  // score
  forwardPIDD(850);
  // setintake(false);
  forwardPIDD(1050);
  clearmotors();
  wait(.2,seconds);
  //go back for bar
  forwardPIDD(-600);
  clearall();
  turnPID(45, 15, -1);
  clearall();
  //get back bar triball
  // setintake(false);
  intake.spin(forward, 100, pct);
  forwardPIDD(150);
  clearall();
  //turn and get *black* bar triball
  turnPID(93, 10, -1);
  forwardPIDD(-1400);
  clearall();
  wait(0.1,seconds);
  turnPID(-92, 15, -1);
  clearmotors();
  wait(0.3, seconds);
  forwardPIDD(150);
  wait(0.2, seconds);
  //collect it
  // intake.stop();
  clearmotors();
  turnPID(-100, 15, -1);
  forwardPIDD(-1400);
  turnPID(0, 30, -1);
  clearmotors();
  // setintake(true);
  intake.spin(reverse, 90, pct);
  forwardPIDD(350);
  wait(.1, seconds);
  clearmotors();
  forwardPIDD(-900);
  turnPID(0, 30, -1);
  forwardPIDD(-900);
}

void skills() {
  catapult.spin(reverse, 100, pct);
  wait(45, sec);
  turnPID(-5, 80, -1);
  wait(.1, sec);
  forwardPIDD(2500);
  wait(.1, sec);
  turnPID(180, 90, -1);
  wait(.1, sec);
  turnPID(150, 90, -1);
  setwings(true);
  forwardPIDD(500);
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  pre();
  thread a(sensordisplays);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

// This is the defensive
// defensive();

// This is the skills
// skills();

void autonomous(void) {
  // defensive();
  stockD();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // intakepistonb.set(true);
  catapult.setStopping(hold);
  stopBase();
  while (true) {
      float movement = (Controller1.Axis3.position()) + (Controller1.Axis1.position());
      float movement1 = (Controller1.Axis3.position()) - (Controller1.Axis1.position());
      frontleft.spin(forward, movement, pct);
      frontright.spin(forward, movement1, pct);
      //back dt
      backleft.spin(forward, movement, pct);
      backright.spin(forward, movement1, pct);
      // ------------
      middleleft.spin(forward, movement, pct);
      middleright.spin(forward, movement1, pct);
      // ------------
    if (Controller1.ButtonR2.pressing()) {
      (intake.spin(reverse, 90, pct));
    } else if (Controller1.ButtonR1.pressing()) {
      (intake.spin(forward, 90, pct));
    } else {
      intake.stop();
    }
    if (Controller1.ButtonY.pressing()) {
      (catapult.spin(reverse, 90, pct));
    } else if (Controller1.ButtonB.pressing()) {
      (catapult.spin(forward, 90, pct));
    } else {
      catapult.stop();
    }

    //pnue intake
    if (Controller1.ButtonLeft.pressing()) {
        intakepistonb.set(true);
    } else if (Controller1.ButtonDown.pressing()) {
        intakepistonb.set(false);
    }
  
    //pnue wings
    // all at once
    if (Controller1.ButtonUp.pressing()) {
        leftwing.set(true);
        rightwing.set(true);
    } else if (Controller1.ButtonLeft.pressing()) {
        leftwing.set(false);
        rightwing.set(false);
    }
  }

  while (1) {

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

// Main will set up the competition functions and callbacks.

int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}