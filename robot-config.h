using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial gyroo;
extern motor intake;
extern motor catapult;
extern digital_out leftwing;
extern digital_out intakepistonb;
extern digital_out rightwing;
extern controller Controller1;
extern rotation RotationRight;
extern rotation RotationLeft;
extern optical Opticall;
extern motor backleft;
extern motor middleleft;
extern motor frontleft;
extern motor backright;
extern motor middleright;
extern motor frontright;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );