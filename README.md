# HC-SR04_mbed_lib
Library to use the HC-SR04 ultrasonic distance sensor on FRDM-KLZ25 with mbedOS

HCSR04 class is defined in hc-sr04.h and implemented in hc-sr04.cpp.

Public methods in HCSR04:
```
        HCSR04(PinName trig_pin, PinName echo_pin); // Constructor
        ~HCSR04(); // Destructor
        
        float get_distance(); // Method to send a pulse and calculate distance to an obstacle
        float get_last_distance(); // Method to return the last calculated obstacle distance
```

mbed_app.json is needed to compile the code correctly to open a serial port at 9800 baud rate and be able to output floating point numbers. Without this, the basic printf used doesn't support %f.

## Example Program:
Measures distance every 0.5s, changes the onboard rgb LED if an object is less than 30cm away and sends the distance over serial.
```
#include "mbed.h"
#include "hc-sr04.h"

int main(){
    // LED indicators
    DigitalOut redLED(PTB18);
    DigitalOut greenLED(PTB19);

    // HC-SR04 ultrasonic sensor
    HCSR04 sensor(PTD5, PTA13);

    float obstacle_distance;

    while (true) {
        obstacle_distance = sensor.get_distance();

        if(obstacle_distance < 0.3){
            // If object is less than 30cm away
            redLED = 0;
            greenLED = 1;
        }else{
            redLED = 1;
            greenLED = 0;
        }

        printf("Obstacle distance: %f m\n", obstacle_distance); // Send distance over serial
        wait_us(500000); // 0.5s delay
    }
}
```
