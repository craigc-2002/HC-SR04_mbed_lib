#include "hc-sr04.h"

HCSR04::HCSR04(PinName trig_pin, PinName echo_pin){ // Constructor
    trig = new DigitalOut(trig_pin); // Define trigger output pin
    echo = new InterruptIn(echo_pin); // Define echo input pin

    echo -> rise(callback(this, &HCSR04::echo_timer_start));
    echo -> fall(callback(this, &HCSR04::echo_timer_end));
}

HCSR04::~HCSR04(){ // Destructor
    delete(trig);
    delete(echo);
}

void HCSR04::send_pulse(void) // Method to send 100us pulse on output pin
{
    trig -> write(1);
    wait_us(100);
    trig -> write(0);
}

void HCSR04::echo_timer_start(void) // Function to start the timer. Attached to an interrupt when PTA2 goes high
{
    echo_timer.reset();
    echo_timer.start();
}

void HCSR04::echo_timer_end(void) // Function to stop the timer and save value. Attached to an interrupt when PTA2 goes low
{
    echo_timer.stop();
    _time_us = echo_timer.elapsed_time().count();
    time_measured = true;
}

float HCSR04::calculate_distance(int time_us) // Method to calculate the distance from the obstacle in metres
{
    float distance_m = (time_us * 0.000001 * 340) / 2;
    return distance_m;
}

float HCSR04::get_distance(){ //Method to measure, calculate and return distance to an obstacle
    send_pulse();
    while(!time_measured);
    _distance_m = calculate_distance(_time_us);
    time_measured = false;

    return _distance_m;
}

float HCSR04::get_last_distance(){ // Method to return the last measured distance to obstacle
    return _distance_m;
}
