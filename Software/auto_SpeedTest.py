#!/usr/bin/env python3
import FirstLook

"""
http://piwars.org/2018-competition/challenges/straight-line-speed-test/
The track is ~7.3 meters long, 53.4cm wide with 6.4cm high walls on each side
Course will be run 3 times and the times will be added together to get final time

Robot goals:
target maximum wheel velocity
but keep wheel velocity the same between left & right
check left & right distance sensors to ensure we're in the middle +-20%
once front distance sensor or length counter trigger, all stop
"""
