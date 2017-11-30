#!/usr/bin/env python3

from base import Challenge

class Speed_Challenge(Challenge):
    
    def run(self):
        print("Speed run")
        
        """
        steps:
            wait for go
            full speed
            keep motors even
            keep centered between left & right sensors
            
            once > 8500mm traveled stop motors
        """
    


if __name__ == "__main__":
    print("Running speed challenge class")
