# Etch-A-Sketch

## Setup
The I2C bus used is bus 2. The rotary encoders are coded to use eQEP modules 1 and 2, which may require pins
P8_33, P8_35, P8_41, and P8_42 be configured for eQEP.

## Control
Each rotary encoder controls either vertical or horizontal movement. A TMP101 temperature sensor is used to clear
the Etch-A-Sketch above 28 degrees Celsius.

## Other Deliverables
The temperature on the two TMP101 sensors can simply be read with the i2c.sh script.
