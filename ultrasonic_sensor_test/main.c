#include <stdio.h>

//#include "srf08.h"
//#include "srf08_params.h"

#include "srf04.h"
#include "srf04_params.h"


int main(void){

    printf("hello fucking world\n");

    //SRF04
    //params inizialization
    srf04_params_t my_params;
    my_params.trigger = GPIO_PIN(PORT_B, 5);
    my_params.echo = GPIO_PIN(PORT_A, 8);
    

    srf04_t dev;
    //inizialize gpio and interrupt
    if (srf04_init(&dev, &my_params) == 0) {
        printf("SRF04 sensor connected\n");
        }
        else {
        printf("Failed to connect to SRF04 sensor, GPIO init failure\n");
        return 1;
        }
        
        //srf04_trigger(&dev);
        //printf("Distance read: %d\n", srf04_read(&dev));

       //loop
       while(1){
        //trigger a measurement and returns the distance
        //printf("Distance get: %d\n", srf04_get_distance(&dev));

        //trigger measurement
        srf04_trigger(&dev);

        xtimer_sleep(1);

        //returns time of flight in ms (should not be invoked within 50ms after triggering)
        printf("Distance read: %d\n", srf04_read(&dev));
       }


    //SRF08
     /*
    srf08_params_t my_params;
    my_params.i2c = SRF08_PARAM_I2C;
    my_params.addr = SRF08_PARAM_ADDR;
    

    srf08_t dev;
    if (srf08_init(&dev, &my_params) == 0) {f
        printf("SRF08 sensor connected\n");
        }
    else {
        printf("Failed to connect to SRF08 sensor\n");
        return 1;
        }f

    uint16_t range_array;
    if (srf08_get_distances (&dev, &range_array, 0, SRF08_MODE_CM )!=0) {
        printf("Error reading values\n");
        }
    */

    return 0;
}


