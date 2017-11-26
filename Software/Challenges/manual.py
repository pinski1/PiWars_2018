#!/usr/bin/env python3

from base import Challenge

class Manual_Challenge(Challenge):
    """Allow user to manually drive the robot around. For both practice and manual challenges."""
    
    self.timeout = 0 # never times out
        
    def run(self):
        print("Manual Mode")
        
        #while True:
            
            # check to see timeout flag hasn't elapsed
            # check to see emergency stop hasn't been triggered
            
            # accept joystick commands
            
            # forward onto FirstLook instance
            


if __name__ == "__main__":
    print("Running manual class")

