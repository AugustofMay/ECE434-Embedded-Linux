#!/usr/bin/env python3
# From: https://adafruit-beaglebone-io-python.readthedocs.io/en/latest/Encoder.html

from Adafruit_BBIO.Encoder import RotaryEncoder, eQEP2, eQEP1
import smbus
import time

bus = smbus.SMBus(2)
matrix = 0x70
tmp101_1 = 0x4a
tmp101_0 = 0x48

# Instantiate the class to access channel eQEP2, and initialize that channel

Vertical = RotaryEncoder(eQEP2)
Horizontal = RotaryEncoder(eQEP1)
Vertical.setAbsolute()
Horizontal.setAbsolute()
Vertical.enable()
Horizontal.enable()

cursorX = 1
cursorY = 0x80

# The first byte is GREEN, the second is RED
clear = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]

state = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]

# Start oscillator (p10)
bus.write_byte_data(matrix, 0x21, 0)
# Disp on, blink off (p11)
bus.write_byte_data(matrix, 0x81, 0)
# Full brightness (p15)
bus.write_byte_data(matrix, 0xe7, 0)

# time.sleep(5)
# bus.read_byte_data(tmp101_0, 0)

bus.write_i2c_block_data(matrix, 0, clear)
bus.write_i2c_block_data(matrix, 0, state)

while True:
    # Get the current position
    print("Vertical: " + str(Vertical.position))
    print("Horizontal: " + str(Horizontal.position))

    temp = bus.read_byte_data(tmp101_0, 0)
    print("Temperature: " + str(temp))
    if(temp > 0x1c):
        bus.write_i2c_block_data(matrix, 0, clear)
        state = [0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00]

    if(Vertical.position > 0):
        if(cursorY < 0x80):
            cursorY = cursorY << 1
    elif(Vertical.position < 0):
        if(cursorY > 0x01):
            cursorY = cursorY >> 1
    Vertical.position = 0

    if(Horizontal.position > 0):
        if(cursorX < 15):
            cursorX = cursorX + 2
    elif(Horizontal.position < 0):
        if(cursorX > 1):
            cursorX = cursorX - 2
    Horizontal.position = 0

    state[cursorX] = state[cursorX] | cursorY
    bus.write_i2c_block_data(matrix, 0, state)
    print("cursorX: " + str(cursorX))
    print("cursorY: " + str(cursorY))

    time.sleep(0.25)
