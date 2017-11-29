/** FirstLook, a Raspberry Pi Wars robot
 * 
 * 
 * Parts list:
 *   1off Teensy 3.2
 *   3off AS5048A encoder
 *   3off ZTW Spider 30A Opto Small ESC
 *   2off Turnigy XK2445-4700kv & 47:1 25mm gearbox
 *   1off MultiStar V-Spec 2205-2350kv & 2040:1 25mm gearbox
 *   4off VL53L0X ToF ranger finders
 * 
 */
#include <SPI.h>
#include "AS5048A.h"
#include <Wire.h>
#include "VL53L0X.h"
#include <PWMServo.h>
#include "Command.h"

/** Settings */
#define ARM_ZERO 0
#define SERVO_MIN 1148
#define SERVO_MAX 1832
#define RATE 100
// PID values
#define SEN_TOF_ADDR  0x10 // base address
#define VMON_RATIO    1  // multiply analog reading by this for battery voltage in microvolts


/** Pin Map */
#define I2C_SDA         A4 // I2C data
#define I2C_SCL         A5 // I2C clock
#define I2C_INT         -1 // I2C alert
#define SPI_MOSI        11
#define SPI_MISO        12
#define SPI_SCK         13
#define SPI_CS_0        -1 // left encoder
#define SPI_CS_1        -1 // right encoder
#define SPI_CS_2        -1 // arm encoder
#define SERVO_OUT_0     -1 // left motor
#define SERVO_OUT_1     -1 // right motor
#define SERVO_OUT_2     -1 // arm motor
#define SERVO_OUT_3     -1 // ball catcher
#define SERVO_OUT_4     -1 // ball launcher
static int range_sensor_en[4] = {-1, -1, -1, -1}; // rangefinder enables
#define VBAT_MON     -1

/** Global Variables/Instances */
volatile int countsLeft, countsRights, angleArm;
CommandParser  cmdParse;
VL53L0X range_sensor[4] = {VL53L0X(), VL53L0X(), VL53L0X(), VL53L0X()};
AS5048A encoderLeft(SPI_CS_0);
AS5048A encoderRight(SPI_CS_1);
AS5048A encoderArm(SPI_CS_2);
PWMServo motorLeft;
PWMServo motorRight;
PWMServo motorArm;
PWMServo motorCatcher;
PWMServo motorLauncher;
IntervalTimer timerLoop;

/*********************************************
  Default command handler
 *********************************************/
void unrecognised(void) {
  Serial.println("Message unrecognised.");
}

/**  */
void setup(void) {

  Serial.begin(115200); // serial is already setup
  Wire.begin();
  SPI.begin();
  
  pinMode(VBAT_MON, INPUT);

  Serial.println("Starting FirstLook MCU...");

  // assign motor pins
  motorLeft.attach(SERVO_OUT_0);
  motorRight.attach(SERVO_OUT_1);
  motorArm.attach(SERVO_OUT_2);
  motorCatcher.attach(SERVO_OUT_3);
  motorLauncher.attach(SERVO_OUT_4);

  // set all motors to 0
  motorLeft.write(90);
  motorRight.write(90);
  motorArm.write(90);
  motorCatcher.write(90);
  motorLauncher.write(90);

  // checking for AS5048A
  encoderLeft.getErrors();
  encoderRight.getErrors();
  encoderArms.getErrors();
  
  // reset encoders to 0
  encoderLeft.getCounts();
  encoderRight.getCounts();
  encoderArm.setAngle(ARM_ZERO);

  // turn off all range sensors
  for (int i = 0; i < 4; i++)
  {
    pinMode(range_sensor_en[i], OUTPUT);
    digitalWrite(range_sensor_en[i], LOW);
  }

  // initialise sensors and change address
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(range_sensor_en[i], HIGH);
    range_sensor[i].init();
    range_sensor[i].setAddress(SEN_TOF_ADDR + (2 * i));
    range_sensor[i].setTimeout(500);
    range_sensor[i].startContinuous();
  }
  
  // add commands to parser
  cmdParse.AddDefaultCallback(unrecognised);
  
  // set up motor control loop
  timerLoop.begin(controlLoop, 1000000UL/RATE);

  Serial.println("Completed set up.");  
}

void loop(void) {
  
}

/*********************************************
  Called when data is available to read
 *********************************************/
void serialEvent(void) {

  cmdParse.ReadSerial();

}

/*********************************************
  Motor control loop
 *********************************************/
void controlLoop(void) {

  // grab current positions of motors & arm
  encoderLeft.getCounts();
  encoderRight.getCounts();
  encoderArm.getAngle();

  // get updated setpoints

  // PID calculate new outputs

  // write them out
  //motorLeft.write(90);
  //motorRight.write(90);
  //motorArm.write(90);
  
}

