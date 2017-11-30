#!/usr/bin/env python3

from base import Challenge

class Rainbow_Challenge(Challenge):
    
    def run(self):
        print("Rainbow Road")
        
        """
        steps:
            turn 45degrees
            drive to one corner
                keep ?? mm from side wall
                until ?? mm from front wall
            turn 135degrees
            drive to next corner
                keep ?? mm from side wall
                until ?? mm from front wall
            turn 90 degrees
            drive to next corner
                keep ?? mm from side wall
                until ?? mm from front wall
            turn 90 degrees
            drive to next corner
                keep ?? mm from side wall
                until ?? mm from front wall
            turn 45 degrees
            drive to center
                until ?? mm traveled
            turn 45 degrees
        """
    

if __name__ == "__main__":
    print("Running rainbow challenge class")

