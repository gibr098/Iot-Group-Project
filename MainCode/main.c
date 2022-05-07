#include <stdio.h>

//#include "srf08.h"
//#include "srf08_params.h"

#include "srf04.h"
#include "srf04_params.h"
#include "thread.h"
#include "periph/gpio.h"
#include "pir.h"
#include "pir_params.h"

char stack[THREAD_STACKSIZE_MAIN];
char stack1[THREAD_STACKSIZE_MAIN];
char stackp[THREAD_STACKSIZE_MAIN];

//Ultrasonic sensor 1
void *thread_handler1(void *arg){
    (void) arg;
    puts("I'm in \"thread1\" now");
    //printf("hello fucking world thread 0\n");
    //SRF04

    srf04_params_t my_params1;
    my_params1.trigger = GPIO_PIN(PORT_A, 8); // D7
    my_params1.echo = GPIO_PIN(PORT_A, 9); // D8
    

    srf04_t dev1;
    if (srf04_init(&dev1, &my_params1) == 0) {
        printf("SRF04 sensor1 connected\n");
        }
        else {
        printf("Failed to connect to SRF04 sensor1, GPIO init failure\n");
        return NULL;
        //break;
        }
        
        //srf04_trigger(&dev);
        //printf("Distance read: %d\n", srf04_read(&dev));
        
       while(1){
        printf("Distance get from sensor 1: %d mm\n", srf04_get_distance(&dev1));
        //srf04_trigger(&dev);
        xtimer_sleep(1);
        //printf("Distance read: %d\n", srf04_read(&dev));
       }

   return NULL;
}

//Ultrasonic sensor 0
void *thread_handler(void *arg){
    (void) arg;
    puts("I'm in \"thread0\" now");
    //printf("hello fucking world thread 0\n");
    //SRF04

    srf04_params_t my_params;
    my_params.trigger = GPIO_PIN(PORT_B, 5); // D4 -> trigger
    my_params.echo = GPIO_PIN(PORT_A, 10); // D2 -> echo
    

    srf04_t dev;
    //int distance=0;
    if (srf04_init(&dev, &my_params) == 0) {
        printf("SRF04 sensor0 connected\n");
        }
        else {
        printf("Failed to connect to SRF04 sensor0, GPIO init failure\n");
        return NULL;
        //break;
        }
        
        //srf04_trigger(&dev);
        //printf("Distance read: %d\n", srf04_read(&dev));
        
       while(1){
        //distance=srf04_get_distance(&dev);
        printf("Distance get from sensor 0: %d mm\n", srf04_get_distance(&dev));
        //srf04_trigger(&dev);
        xtimer_sleep(1);
        //printf("Distance read: %d\n", srf04_read(&dev));
       }

   return NULL;
}


//PIR sensor
void *thread_handlerp(void *arg){
    (void) arg;
    puts("I'm in \"threadp\" now");

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
        return NULL;
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
    
   return NULL;
}

int main(void){

thread_create(stack, sizeof(stack),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_STACKTEST,
                    thread_handler,
                    NULL, "thread0");

thread_create(stack1, sizeof(stack1),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_STACKTEST,
                    thread_handler1,
                    NULL, "thread1");

thread_create(stackp, sizeof(stackp),
                    THREAD_PRIORITY_MAIN - 1,
                    THREAD_CREATE_STACKTEST,
                    thread_handlerp,
                    NULL, "threadp");




    return 0;
}


