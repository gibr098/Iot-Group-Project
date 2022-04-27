#include <stdio.h>
#include "xtimer.h"
#include "periph/gpio.h"
#include "pir.h"
#include "pir_params.h"


int main(void)
{

    printf("PIR motion sensor Test");

    /* Fix port parameter for Ultrasonic sensor */
    pir_params_t my_params;
    my_params.gpio = GPIO_PIN(PORT_A, 8);
    my_params.active_high = true;

    pir_t dev;

    /* Initialize gpio and interrupt */
    if (pir_init(&dev, &my_params) == 0)
    {
        printf("PIR motion sensor connected initialized.\n");
    }
    else
    {
        printf("PIR initialization failure.\n");
        return 1;
    }
    int16_t occup;
    while(1){
         
         if(pir_get_status(&dev) == PIR_STATUS_ACTIVE){
             printf("Motion detected.\n");
         }else{
             printf("No motion detected.\n");
         }
         pir_get_occupancy(&dev,&occup);
        printf("Occupancy: %d \n", occup/100);
         xtimer_sleep(1);
        //  printf("Status: %d \n", pir_get_status(&dev));
        //  xtimer_sleep(1);
    }



    return 0;
}