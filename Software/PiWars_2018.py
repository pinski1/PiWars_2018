#!/usr/bin/env python3
from time import sleep

import FirstLook
# import autonomous challenge specific code, no need to import remote controlled challenges
import auto_MinimalMaze
import auto_Rainbow
import auto_SpeedTest

from approxeng.input.selectbinder import ControllerResource # joystick cotrol code
#import OLED display code
# set up basic controls
# allow for menu navigation via joystick

with ControllerResource() as joystick:
    while joystick.connected:
        # do stuff
		print("Stuff")