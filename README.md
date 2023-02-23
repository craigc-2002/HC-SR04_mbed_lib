# HC-SR04_mbed_lib
Library to use the HC-SR04 ultrasonic distance sensor on FRDM-KLZ25 with mbedOS

HCSR04 class is defined in hc-sr04.h and implemented in hc-sr04.cpp.

Public methods in HCSR04:
        HCSR04(PinName trig_pin, PinName echo_pin); // Constructor
        ~HCSR04(); // Destructor
        
        float get_distance(); // Method to send a pulse and calculate distance to an obstacle
        float get_last_distance(); // Method to return the last calculated obstacle distance

Main.cpp is a basic program to test the sensor and output the measured distance over serial.

mbed_app.json is needed to compile the code correctly to open a serial port at 9800 baud rate and be able to output floating point numbers. Without this, the basic printf used doesn't support %f.
