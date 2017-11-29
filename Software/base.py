#!/usr/bin/env python3

class Challenge:

    """The Base challenge class
        Attributes:
            input_device:   Instance of joystick
            output_device:  Instance of FirstLook
            timeout:        An integer in seconds of the maximum duration of the challenge
    """
    
    def __init__(self, in_device, out_device):
        self.timeout = 10*60
        self.input_device = in_device
        self.output_device = out_device
