# FirstLook - PiWars 2018

https://piwars.org/2018-competition/

## Hardware

### Electronics
Parts list:
* [Raspberry Pi 3](https://www.raspberrypi.org/documentation/hardware/raspberrypi/README.md)
  * [Adafruit PiOLED](https://www.adafruit.com/product/3527)
  * [Raspberry Pi Camera](https://www.raspberrypi.org/documentation/hardware/camera/)
* [Teensy 3.2](https://www.pjrc.com/store/teensy32.html)
  * 3x [AS5048A encoders](https://www.aliexpress.com/item/Magnetic-Encoder-AS5048A-for-Alexmos-BaseCam-Electronics-Gimbal-Controller-and-Brushless-Gimbal-Motor/32834461450.html)
  * 3x [ZTW Spider 30A Opto Small](https://hobbyking.com/en_us/ztw-spider-series-30a-small-opto-multi-rotor-esc-2-6s-simonk-firmware.html)
  * 2x [Turnigy XK2445-4700kv](https://hobbyking.com/en_us/turnigy-xk2445-4700kv-brushless-inrunner.html) & 47:1 25mm gearbox
  * 1x [V-Spec 2205-2350kv](https://hobbyking.com/en_us/2205-2350kv-ccw-v-spec-mongoose.html) & 2040:1 25mm gearbox
  * 4x [VL53L0X ToF ranger finders](https://www.pololu.com/product/2490)
 * [Matek PDB-XT60](http://www.mateksys.com/?portfolio=pdb-xt60)
   * Includes 100k & 30k resistor divider for voltage monitoring
 * Lithium Polymer battery, 3 cell 1000mAh

### Chassis
The inspiration for this design came from the [Endevour Robotics FirstLook 110](http://endeavorrobotics.com/products#110-firstlook).

< image? >

Originally prototyped in lasercut plywood at [Cambridge Makespace](http://makespace.org/).

## Firmware
To handle the high powered motors and wheel encoders a microcontroller is required. The Raspberry Pi will communicate with this over (USB) serial.

## Software
To aid development each of the autonomous challenges will have it's own python file which will be called from the main code. They will however will need special functions included in the standard library.

* ./FirstLook.py	    		Robot control function library
* ./PiWars_2018.py			Main program, call this
* ./Challenges/base.py       Base challenge class
* ./Challenges/manual.py     
* ./Challenges/maze.py		Code for solving autonomous maze challenge
* ./Challenges/rainbow.py	Code for solving autonomous vision challenge
* ./Challenges/speed.py 		Code for solving autonomous speed challenge

### Challenges
To make the code robust so as to avoid problems on the day as well as easier to develop on each challenge will be tackled in it's own thread. As each challenge shares some basic features I decided to make a super class that would handle those basics and then each discrete challenge would inherit these basic tasks. This avoids too much dreaded repetition.
