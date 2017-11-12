/** FirstLook, a Raspberry Pi Wars robot
 * 
 * 
 * Parts list:
 *   1off Teensy 3.2
 *   1off QTR-8RC sensor array (upgrade to QTR-8A?)
 *   3off AS5048A encoder
 *   2off ZTW Spider 30A Opto Small
 *   2off Turnigy XK2445-4700kv & 47:1 25mm gearbox
 *   1off ??? brushed ESC
 *   1off ??? & 2040:1 25mm gearbox
 *   4off VL53L0X ToF ranger finders
 * 
 */
#include <SPI.h>
#include "AS5048A.h"
#include <Wire.h>
#include "PCA9546.h"
#include "VL53L0X.h"
#include <PWMServo.h>
#include "Command.h"

/** Settings */
#define ARM_ZERO 0
#define SERVO_MIN 1148
#define SERVO_MAX 1832
#define RATE 100
// PID values


/** Pin Map */
#define I2C_SDA         A4 // I2C clock
#define I2C_SCL         A5 // I2C clock
#define I2C_RST         -1 // reset all I2C mux devices
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
#define LINE_SEN_0      -1 // line sensors
#define LINE_SEN_1      -1
#define LINE_SEN_2      -1
#define LINE_SEN_3      -1
#define LINE_SEN_4      -1
#define LINE_SEN_5      -1
#define LINE_SEN_6      -1
#define LINE_SEN_7      -1


/** Global Variables/Instances */
volatile int countsLeft, countsRights, angleArm;
PCA9546 rangeMux;
VL53L0X rangeSen;
AS5048A encoderLeft(SPI_CS_0);
AS5048A encoderRight(SPI_CS_1);
AS5048A encoderArm(SPI_CS_2);
PWMServo motorLeft;
PWMServo motorRight;
PWMServo motorArm;
PWMServo motorCatcher;
PWMServo motorLauncher;
IntervalTimer timerLoop;

/** */
void setup(void) {

  // serial is already setup
  Wire.begin();
  SPI.begin();

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

  // reset encoders to 0
  encoderLeft.getCounts();
  encoderRight.getCounts();
  encoderArm.setAngle(ARM_ZERO);

  // Set up VL53L0Xs
  rangeMux.selChannel(CHAN_1 || CHAN_2 || CHAN_3 || CHAN_4); // set PCA9546A to all
  rangeSen.init(); // set up VL53L0X, continuous ranging
  rangeSen.setTimeout(500);
  rangeSen.startContinuous();
  rangeMux.selChannel(0);
  
  // Set up line sensors

  // set up motor control loop
  timerLoop.begin(controlLoop, 1000000UL/RATE);

  Serial.println("Completed set up.");  
}

void loop(void) {
  
}

/** motor control loop */
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

/* Mux handler */

