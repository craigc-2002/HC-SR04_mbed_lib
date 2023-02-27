#ifndef HCSR04_h
#define HCSR04_h

#include "mbed.h"

class HCSR04{
    float _distance_m; // Variable to store the most recently measured distance in m
    int _time_us; // Variable to store the most recently measured time in us
    volatile bool time_measured;

    DigitalOut* trig; // Define pointer to output pin
    InterruptIn* echo; // Define pointer to input pin, used to measure the echo pulse
    Timer echo_timer; // Timer to measure echo length

    void send_pulse(); // Method to send a pulse on the trigger pin
    float calculate_distance(int time_us); // Method to calculate distance from a given time
    void echo_timer_start(void);
    void echo_timer_end(void);

    public:
        HCSR04(PinName trig_pin, PinName echo_pin); // Constructor
        ~HCSR04(); // Destructor
        
        float get_distance(); // Method to send a pulse and calculate distance to an obstacle
        float get_last_distance(); // Method to return the last calculated obstacle distance
};

#endif
