# FirstLook - PiWars 2018

https://piwars.org/2018-competition/

## Hardware



## Firwmare
To handle the high powered motors and wheel encoders a microcontroller is required. The Raspberry Pi will communicate with this over (USB) serial.

## Software
To aid development each of the autonomous challenges will have it's own python file which will be called from the main code. The manual challenges do not require any specific run time code. They will however will need special functions included in the standard library.

* FirstLook.py	    		Robot control function library
* PiWars_2018.py			Main program, call this
* auto_MinimalMaze.py		Code for solving autonomous maze challenge
* auto_Rainbow.py			Code for solving autonomous vision challenge
* auto_SpeedTest.py 		Code for solving autonomous speed challenge

