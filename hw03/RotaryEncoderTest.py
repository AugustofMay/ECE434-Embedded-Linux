#!/usr/bin/env python3
# From: https://adafruit-beaglebone-io-python.readthedocs.io/en/latest/Encoder.html

from Adafruit_BBIO.Encoder import RotaryEncoder, eQEP2, eQEP1
import time

# Instantiate the class to access channel eQEP2, and initialize that channel

myEncoder = RotaryEncoder(eQEP2)
myEncoder.setAbsolute()
myEncoder.enable()

# Get the current position
for i in range(1,50) :
    print(myEncoder.position)
    time.sleep(0.1)
