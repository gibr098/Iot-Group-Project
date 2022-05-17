#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "srf04.h"
#include "srf04_params.h"
#include "thread.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include "periph/i2c.h"
#include "msg.h"
#include "net/emcute.h"
#include "net/ipv6/addr.h"
#include "net/nanocoap_sock.h"
#include "shell.h"




void send(int data){

 printf("FUNCTION SENDD\n\n\n\n");
 char buf[100];
 sprintf(buf,"python3 mqttClient.py %d", data);
 system(buf);

}




//ultrasonic 1
gpio_t trigger_pin = GPIO_PIN(PORT_B, 5); // D4 -> trigger
gpio_t echo_pin = GPIO_PIN(PORT_A, 10); // D2 -> echo

//ultrasonic 2
gpio_t trigger_pin2 = GPIO_PIN(PORT_A, 9); // D8 -> trigger
gpio_t echo_pin2 = GPIO_PIN(PORT_A, 8); // D7 -> echo

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

void echo_cb2(void* arg){ 
	int val = gpio_read(echo_pin2);
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

/*
int read_distance(void){ 
	echo_time = 0;
	gpio_clear(trigger_pin);
	xtimer_usleep(20);
	gpio_set(trigger_pin);
	xtimer_msleep(100);
	return echo_time/58;
}
*/

int read_distance(gpio_t triggerPin){ 
	echo_time = 0;
	gpio_clear(triggerPin);
	xtimer_usleep(20);
	gpio_set(triggerPin);
	xtimer_msleep(100);
	return echo_time/58;
}






int main(void){

   


    // pin sensor initialization
    gpio_init(trigger_pin, GPIO_OUT);
    gpio_init_int(echo_pin, GPIO_IN, GPIO_BOTH, &echo_cb, NULL);

    read_distance(trigger_pin);

    //gpio_init(trigger_pin2, GPIO_OUT);
    //gpio_init_int(echo_pin2, GPIO_IN, GPIO_BOTH, &echo_cb2, NULL);

    //read_distance(trigger_pin2);

    int distance=0;
    distance= read_distance(trigger_pin);
    printf("DISTANCEEEEEEEEEEEEE: %d\n", distance);

   
    send(distance);
    //int distance2=0;

    while(1){

        distance = read_distance(trigger_pin);
        printf("Distance of ultrasonic 1: %d cm\n", distance);
        
        //send(distance);


        //distance2 = read_distance(trigger_pin2);
        //printf("Distance of ultrasonic 2: %d cm\n", distance2);

    
    }


    
    
    return 0;
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
       

