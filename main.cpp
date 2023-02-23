#include "mbed.h"
#include "hc-sr04.h"

int main(){
    // LED indicators
    DigitalOut redLED(PTB18);
    DigitalOut greenLED(PTB19);

    HCSR04 sensor(PTD5, PTA13); // HC-SR04 ultrasonic sensor
    DigitalOut obs_LED(PTD0);


    float obstacle_distance;

    redLED=0;
    greenLED=0;

    while (true) {
        obstacle_distance = sensor.get_distance();

        if(obstacle_distance < 0.3){
            redLED = 0;
            greenLED = 1;
            obs_LED = 1;
        }else{
            redLED = 1;
            greenLED = 0;
            obs_LED = 0;
        }

        printf("Obstacle distance: %f m\n", obstacle_distance);
        wait_us(500000); // 1s delay
    }
    return 0;
}

