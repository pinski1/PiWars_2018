#!/usr/bin/env python3
import threading
from abc import ABCMeta, abstractmethod

class Challenge(threading.Thread):


    """The Base challenge class
        Attributes:
            input_device:   Instance of joystick
            output_device:  Instance of FirstLook
            timeout:        An integer in seconds of the maximum duration of the challenge
    """
    __metaclass__ = ABCMeta
    
    timeout = 10*60
    
    def __init__(self, input_device, output_device):
        self.input_device = input_device
        self.output_device = output_device
    
    @abstractmethod
    def run(self):
        """ Carry out challenge."""
        pass
