#!/usr/bin/env python3

from base import Challenge

class Maze_Challenge(Challenge):
    
    def run(self):
        print("Maze")
        print("Input device is" + self.input_device)
        
        """
        steps:
        drive forward
            distance ?? mm from left wall
            until ?? mm from forward wall
        drive 90degree right
        drive foward
            distance ?? mm from left wall
            until ?? mm from forward wall
        drive 180degree right
        drive forward
            distance ?? mm from left wall
            until ?? mm from forward wall
        drive 180degree left
        drive forward
            distance ?? mm from left wall
            until ?? mm from forward wall
        drive 90degree left
        drive foward
            distance ?? mm from left wall
            when left wall disappears, continue for 200mm
        stop
        """
        
        #return
        pass

if __name__ == "__main__":
    print("Running maze challenge class")
