#!/usr/bin/env python3
import time
import threading
import Adafruit_SSD1306 # import OLED display
from approxeng.input.selectbinder import ControllerResource # import approx eng's joystick code

# import communications library
import FirstLook

# import challenge classes
from manual import Manual_Challenge
from rainbow import Rainbow_Challenge
from speed import Speed_Challenge
from maze import Maze_Challenge



def start_challenge(new_challenge):
    """ start a challenge
        first check to make sure there are no other challenges running
        start challenge"""
    
    


def stop_challenge(self, running_challenge):
    """ stop the running challenge
        make sure there are no other challenges running"""

# 128x32 display with hardware I2C:
disp = Adafruit_SSD1306.SSD1306_128_32(rst=None)

disp.begin()

disp.clear()
disp.display()



while True:
    try:
        with ControllerResource() as joystick:
            print('Found a joystick and connected')
            while joystick.connected:
                # Do stuff with your joystick here!
                # ....
                # ....
        # Joystick disconnected...
        print('Connection to joystick lost')
    except IOError:
        # No joystick found, wait for a bit before trying again
        print('Unable to find any joysticks')
        sleep(1.0)
        





""" to do:
        GUI management
        thread management
        joystick management
        FirstLook management
        error handling
        

