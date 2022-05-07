#include <stdio.h>

#include "srf04.h"
#include "srf04_params.h"
#include "thread.h"
#include "periph/gpio.h"
#include "periph/i2c.h"



gpio_t trigger_pin = GPIO_PIN(PORT_B, 5); // D4 -> trigger
gpio_t echo_pin = GPIO_PIN(PORT_A, 10); // D2 -> echo
uint32_t echo_time;
uint32_t echo_time_start;


//callback function
void echo_cb(void* arg){ 
	int val = gpio_read(echo_pin);
	uint32_t echo_time_stop;

    (void) arg;

	if(val){
		echo_time_start = xtimer_now_usec();
	}
    else{
		echo_time_stop = xtimer_now_usec();
		echo_time = echo_time_stop - echo_time_start;
	}
}

int read_distance(void){ 
	echo_time = 0;
	gpio_clear(trigger_pin);
	xtimer_usleep(20);
	gpio_set(trigger_pin);
	xtimer_msleep(100);
	return echo_time/58;
}


int main(void){

    // pin initialization

    gpio_init(trigger_pin, GPIO_OUT);
    gpio_init_int(echo_pin, GPIO_IN, GPIO_BOTH, &echo_cb, NULL);

    read_distance();

    int distance=0;

    while(1){
        distance = read_distance();
        printf("Distance: %d cm\n", distance);
        xtimer_msleep(1);
    }




/*
    //RIOT documentation method
    srf04_params_t my_params;
    my_params.trigger = GPIO_PIN(PORT_B, 5); // D4
    my_params.echo = GPIO_PIN(PORT_A, 10); // D2
    
    srf04_t dev;

    if (srf04_init(&dev, &my_params) == 0) {
        printf("SRF04 sensor0 connected\n");
        }
    else{
        printf("Failed to connect to SRF04 sensor0, GPIO init failure\n");
        return 1;
        }
        
        //srf04_trigger(&dev);
        //printf("Distance read: %d\n", srf04_read(&dev));
        
       while(1){
           int distance=srf04_get_distance(&dev);
           printf("Distance get from sensor 0: %d mm\n", distance);
           xtimer_sleep(1);
       }
*/
       
       return 0;
}
