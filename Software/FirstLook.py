#!/usr/bin/env python3
""" FirstLook
    This code will drive the accessories needed to control a FirstLook robot. IT does not require an external microcontroller.

"""

#import Adafruit_SSD1306 # https://github.com/adafruit/Adafruit_Python_SSD1306
import Adafruit_PCA9685 # https://github.com/adafruit/Adafruit_Python_PCA9685
import VL53L0X # https://github.com/johnbryanmoore/VL53L0X_rasp_python
#from ina219 import INA219, DeviceRangeError # https://github.com/chrisb2/pi_ina219
# # AS5048A library
# think people use RPI.GPIO

# Pin Map
PIN_I2C_SDA = 2
PIN_I2C_SCL = 3
PIN_SPI_SCK = 11
PIN_SPI_MOSI = 10
PIN_SPI_MISO = 9
PIN_SPI_CE0 = 8 # UNUSED
PIN_SPI_CE1 = 7 # UNUSED
PIN_STATUS_LED = 18
PIN_XSHUT1 = 0
PIN_XSHUT2 = 0
PIN_XSHUT3 = 0
PIN_CS_ENC1 = 0
PIN_CS_ENC2 = 0
PIN_CS_ENC3 = 0
PIN_GPIO1 = 0
PIN_GPIO2 = 0
PIN_GPIO3 = 0
PIN_GPIO4 = 0

# OLED Settings
RST = None     # on the PiOLED this pin isn't used
ADDRESS_OLED = 0x00
# INA219 Settings
SHUNT_OHMS = 0.02
MAX_EXPECTED_AMPS = 150.0
MAX_EXPECTED_VOLTS = 16.0
ADDRESS_INA219 = 0x40
# Servo Settings
MIN_SERVO = 1000 # us
MAX_SERVO = 2000 # us
UPDATE_FREQ = 50.0 # Hz
ADDRESS_SERVO = 0x40
SERVO_DRIVE_LEFT = 0
SERVO_DRIVE_RIGHT = 1
SERVO_DRIVE_ARM = 2
# Range Sensor Settings
ADDRESS_VL53L0X = 0x29
ADDRESS_VL53L0X_ALL = [0x2B, 0x2D, 0x2F]
# Encoder Settings

# Class

class FirstLook:

    def __init__(self):
        
        # OLED initialisation
        """
        # 128x32 display with hardware I2C:
        self.display = Adafruit_SSD1306.SSD1306_128_32(rst=RST)
        # self.display = Adafruit_SSD1306.SSD1306_128_64(rst=RST)
        
        # Initialize library.
        self.display.begin()
        
        # Clear display.
        self.display.clear()
        self.display.display()
        """
        
        # Servo initialisation
        self.servos = Adafruit_PCA9685.PCA9685(address=ADDRESS_SERVO)
        self.servos.set_pwm_freq(UPDATE_FREQ)
        self.us_per_tick = ((1 / UPDATE_FREQ)/4095) * 1000000
        self.half_range = (MAX_SERVO - MIN_SERVO) / 2
        
                # AS5048A initialisation
        # things
        
        # VL53L0X initialisation
        GPIO.setwarnings(False)
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(PIN_XSHUT1, GPIO.OUT) # set all to be outputs
        GPIO.setup(PIN_XSHUT2, GPIO.OUT)
        GPIO.setup(PIN_XSHUT3, GPIO.OUT)
        GPIO.output(PIN_XSHUT1, GPIO.LOW) # now set all to be low
        GPIO.output(PIN_XSHUT2, GPIO.LOW)
        GPIO.output(PIN_XSHUT3, GPIO.LOW)
        time.sleep(0.25); # to ensure they're all low
        self.distance_shutdown = [PIN_XSHUT1, PIN_XSHUT2, PIN_XSHUT3]
        self.distance_sensors = [VL53L0X.VL53L0X(address=0x2B), VL53L0X.VL53L0X(address=0x2D), VL53L0X.VL53L0X(address=0x2F)]
        for i in range(0, 3):
            GPIO.output(self.distance_shutdown[i], GPIO.HIGH)
            time.sleep(0.05)
            distance_sensors[i].start_ranging(VL53L0X.VL53L0X_BETTER_ACCURACY_MODE)
            # alternatively VL53L0X_HIGH_SPEED_MODE
    
    """
    takes values between -1 and 1 for drive.
    Converts to servo drive
    """
    def set_speed(self, left, right):
    # check for & clamp excessive values
        if(abs(left) > 1 or abs(right) > 1):
            print ("Error!")

            if(left > 1):
                left = 1
            elif (left < -1):
                left = -1

            if(right > 1):
                right = 1
            elif(right < -1):
                right = -1

        # map left/right where MIN_SERVO = -1 and MAX_SERVO = 1
        servo_left = int((left * self.half_range + (MIN_SERVO + self.half_range)) / self.us_per_tick)
        servo_right = int((right * self.half_range + (MIN_SERVO + self.half_range)) / self.us_per_tick)

        # write out to PCA9685
        self.servos.set_pwm(SERVO_DRIVE_LEFT, 0, servo_left)
        self.servos.set_pwm(SERVO_DRIVE_RIGHT, 0, servo_right)

        return

    # future expansion:
        # internal method for OLED writing
        # internal method for PCA9685 writing
        # internal method for AS5048A reading
        # internal method for VL53L0X reading
        # internal method for INA219 reading




if __name__ == "__main__":
    print("Running FirstLook interface library self-test")

