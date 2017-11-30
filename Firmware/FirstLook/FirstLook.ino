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
#include <PWMServo.h>
#include <SPI.h>
#include <AS5048A.h>
#include <Wire.h>
#include <VL53L0X.h>
#include <PID_v1.h>
#include <SerialCommand.h> // https://github.com/kroimon/Arduino-SerialCommand

/** Settings */
#define ARM_ZERO 0
#define SERVO_MIN 1148 // oneshot125 = 125us to 250us high pulse, 2ms period
#define SERVO_MAX 1832 // oneshot42 = 42us to 84us high pulse, 666us period
#define RATE 100 // in ms
#define SEN_TOF_NUM   4
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define SEN_TOF_ADDR  0x8A+2 // base address
#define VMON_RATIO    3492  // multiply analog reading by this for battery voltage in microvolts
// 3.3 * (13/3) / (2^12 -1) = 3.492e-3
// PID Values


/** Pin map */
#define I2C_SDA      18 // rangefinder & IMU
#define I2C_SCL      19
#define I2C_INT      -1
#define MOTOR_L_PIN  6 // servo signal outputs
#define MOTOR_R_PIN  7
#define MOTOR_A_PIN  8
#define SPI_MOSI     11 // encoders
#define SPI_MISO     12
#define SPI_SCK      13
#define SPI_L_CS_PIN -1 // chip selects for encoders
#define SPI_R_CS_PIN -1
#define SPI_A_CS_PIN -1
static int range_sensor_en[SEN_TOF_NUM] = { -1, -1, -1, -1}; // rangefinder enables
#define VBAT_MON     -1
// total: 17, dig: 16, ana: 1

/** Classes & Function Prototypes */
PWMServo motorLeft;
PWMServo motorRight;
PWMServo motorArms;
AS5048A encoderLeft(ENC_L_CS_PIN);
AS5048A encoderRight(ENC_R_CS_PIN);
AS5048A encoderArms(ENC_A_CS_PIN);
PID controlLeft();
PID controlRight();
PID controlArm();
VL53L0X range_sensor[SEN_TOF_NUM] = {VL53L0X(), VL53L0X(), VL53L0X(), VL53L0X()};
SerialCommand sCmd;

/** Globals */
volatile int countsLeft, countsRights, angleArm;


/*********************************************
  Set up the Teensy and define supported commands
 *********************************************/
void setup(void) {

  Serial.begin(115200);

  pinMode(VBAT_MON, INPUT);

  Serial.println("Starting set-up...");

  SPI.begin();

  Wire.begin();
  Wire.setClock(400000L);

  // assign motor pins
  motorLeft.attach(MOTOR_L_PIN, SERVO_MIN, SERVO_MAX);
  motorRight.attach(MOTOR_R_PIN, SERVO_MIN, SERVO_MAX);
  motorArms.attach(MOTOR_A_PIN, SERVO_MIN, SERVO_MAX);

  // set all motors to 0
  motorLeft.write(90);
  motorRight.write(90);
  motorArms.write(90);

  // checking for AS5048A
  encoderLeft.getErrors();
  encoderRight.getErrors();
  encoderArms.getErrors();

  // reset encoders to 0
  encoderLeft.getCounts();
  encoderRight.getCounts();
  encoderArm.setAngle(ARM_ZERO);

  // turn off all range sensors
  for (int i = 0; i < SEN_TOF_NUM; i++)
  {
    pinMode(range_sensor_en[i], OUTPUT);
    digitalWrite(range_sensor_en[i], LOW);
  }

  // initialise sensors and change address
  for (int i = 0; i < SEN_TOF_NUM; i++)
  {
    digitalWrite(range_sensor_en[i], HIGH);
    range_sensor[i].init();
    range_sensor[i].setAddress(SEN_TOF_ADDR + (2 * i));
    range_sensor[i].setTimeout(500);
    range_sensor[i].startContinuous();
    // now all setup with unique addresses
  }

  // add commands to parser
  sCmd.setDefaultHandler(unrecognised);
  sCmd.addCommand("S", get_status);
  sCmd.addCommand("R", get_sensors);
  sCmd.addCommand("M", set_speed);
  sCmd.addCommand("G", set_distance);
  
  // set up motor control loop
  timerLoop.begin(controlLoop, 1000000UL/RATE);
  
  // Finished set up.

}

/*********************************************

 *********************************************/
void loop(void) {

  Serial.println("Hi");
  delay(RATE);
  // y = map (x, 1000, 2000, 0, 180);

  
}


/*********************************************
  Called when data is available to read
 *********************************************/
void serialEvent(void) {

  sCmd.readSerial();

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

/*********************************************
  Reads battery voltage
 *********************************************/
unsigned int get_battery_voltage(void) {
  unsigned int voltage = 0x00;

  voltage = analogRead(VBAT_MON);
  voltage *= VMON_RATIO; // in microvolts
  voltage /= 1000;
  return voltage; // in millivolts
}

/*********************************************
  Default command handler
 *********************************************/
void unrecognised(void) {
  Serial.println("Message unrecognised.");
}

/*********************************************
  get status command handler
 *********************************************/
void get_status(void) {
  Serial.println("getting status");



  // output status values
  Serial.print("S:");
  // serial print values
  
  Serial.print(get_battery_voltage, DEC);
  
  Serial.println();

  return;
}

/*********************************************
  Default command handler
 *********************************************/
void get_sensors(void) {
  Serial.println("getting sensors");

  unsigned int range_values[SEN_TOF_NUM];

  for(int i = 0; i < SEN_TOF_NUM; i++) 
  {
    range_values[i] = range_sensor[i].readRangeContinuousMillimeters();
    if (range_sensor[i].timeoutOccurred()) range_values[i] = 0xFFFFFFFF;    
  }

  // output range values
  Serial.print("R:");
  for(int i = 0; i < SEN_TOF_NUM; i++)
  {
    Serial.print(range_values[i], DEC);
    if(i < 3) Serial.print(',');
  }
  Serial.println();

  return;

}

/*********************************************
  Default command handler
 *********************************************/
void set_speed(void) {
  int aNumber;
  char *arg;
  Serial.println("setting travel speed");
}

/*********************************************
  Default command handler
 *********************************************/
void set_distance(void) {
  int aNumber;
  char *arg;

  arg = sCmd.next();
  if(arg != NULL)
  {
    // whey
  }
  Serial.println("setting travel distance");
}
