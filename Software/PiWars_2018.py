#!/usr/bin/env python3
"""
something
"""
import time
import threading
import FirstLook
from approxeng.input.selectbinder import ControllerResource
# logging stuff?
# challenges
import maze
import speed
import rainbow



def mixer(yaw, throttle, max_power=100):
    """
    https://approxeng.github.io/approxeng.input/examples/tiny4wd.html
    Mix a pair of joystick axes, returning a pair of wheel speeds. This is where the mapping from
    joystick positions to wheel powers is defined, so any changes to how the robot drives should
    be made here, everything else is really just plumbing.
    
    :param yaw: 
        Yaw axis value, ranges from -1.0 to 1.0
    :param throttle: 
        Throttle axis value, ranges from -1.0 to 1.0
    :param max_power: 
        Maximum speed that should be returned from the mixer, defaults to 100
    :return: 
        A pair of power_left, power_right values to send to the motor driver
    """
    left = throttle + yaw
    right = throttle - yaw
    scale = float(max_power) / max(1, abs(left), abs(right))
    return left * scale, right * scale











threads = []



"""

[dleft, dright, dup, ddown] for menu navigation
rx, ry for drive

"""


first_look = FirstLook.FirstLook()


while True:
    try:
        with ControllerResource(dead_zone=0.05, hot_zone=0.05) as joystick:
            print('Found a joystick and connected')
            print(joystick.controls)
            while joystick.connected:
                # Do stuff with your joystick here!
                
                
                left, right = mixer(joystick.rx, joystick.ry, 1)
                first_look.set_speed(left, right)
                
                
                
                
                
                
                
                time.sleep(0.1)
        # Joystick disconnected...
        print('Connection to joystick lost')
    except IOError:
        # No joystick found, wait for a bit before trying again
        print('Unable to find any joysticks')
        time.sleep(1.0)


"""
for i in range(5):
    t = threading.Thread(target=worker)
    threads.append(t)
    t.start()
"""
