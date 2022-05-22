/*
INSTRUCTIONS:

1. Run the local broker in mosquitto.rsmb/rsmb launch "./src/broker_mqtts config.conf"

2. Create interafaces with sudo ./RIOT/dist/tools/tapsetup/tapsetup -c 2

3. In the same directory run "sudo ip a a 2000:2::1 dev tapbr0"

4. Launch the application with "make all flash term"

5. In /RIOT/dist/tools/tapsetup/tapsetup run "sudo ip a a 2000:2::1 dev tapbr0""

6. Push the reset button on the nucleo board

*/


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

#ifndef EMCUTE_ID
#define EMCUTE_ID ("whisky")
#endif
#define EMCUTE_PORT 1885
#define EMCUTE_PRIO (THREAD_PRIORITY_MAIN - 1)
#define BROKER_ADDRESS      "2000:2::1"

static char stack[THREAD_STACKSIZE_DEFAULT];
static msg_t queue[8];

extern int _gnrc_netif_config(int argc, char **argv);

static void *emcute_thread(void *arg){
    (void)arg;
    emcute_run(EMCUTE_PORT, EMCUTE_ID);
    return NULL; /* should never be reached */
}

// function that disconnects from the mqttsn gateway
static int discon(void){
    int res = emcute_discon();
    if (res == EMCUTE_NOGW) {
        puts("error: not connected to any broker");
        return 1;
    }
    else if (res != EMCUTE_OK) {
        puts("error: unable to disconnect");
        return 1;
    }
    puts("Disconnect successful");
    return 0;
}

// function that publish messages to the topic
// it takes as input the topic, the message to send and
// the value of qos
static int pub(char* topic, char* data, int qos){
  emcute_topic_t t;
  unsigned flags = EMCUTE_QOS_0;

  switch (qos) {
      case 1:
        flags |= EMCUTE_QOS_1;
        break;
      case 2:
        flags |= EMCUTE_QOS_2;
        break;
      default:
        flags |= EMCUTE_QOS_0;
        break;
  }



  /* step 1: get topic id */
  t.name = topic;
  if (emcute_reg(&t) != EMCUTE_OK) {
      puts("error: unable to obtain topic ID");
      return 1;
  }

  /* step 2: publish data */
  if (emcute_pub(&t, data, strlen(data), flags) != EMCUTE_OK) {
      printf("error: unable to publish data to topic '%s [%i]'\n",
              t.name, (int)t.id);
      return 1;
  }

  printf("published %s on topic %s\n", data, topic);

  return 0;
}

// function that connects to the mqtt gateway
// it takes as input the ip address and the port
static int con(char* addr, int port){
  sock_udp_ep_t gw = { .family = AF_INET6, .port = EMCUTE_PORT };
  gw.port = port;

  /* parse address */
  if (ipv6_addr_from_str((ipv6_addr_t *)&gw.addr.ipv6, addr) == NULL) {
      printf("error parsing IPv6 address\n");
      return 1;
  }

  if (emcute_con(&gw, true, NULL, NULL, 0, 0) != EMCUTE_OK) {
      printf("error: unable to connect to [%s]:%i\n", addr, port);
      return 1;
  }
  printf("Successfully connected to gateway at [%s]:%i\n", addr, port);
  return 0;
}

static int send(int data){
  printf("Send Function\n");
 

  // name of the topic
  char topic[32];
  
  // json that it will published
  char json[128];
  
 
    //connect to the gateway
    con( BROKER_ADDRESS, 1885);
    
    sprintf(json, "{\"distance\": \"%d\"}", data);

    // publish to the topic
    //pub(topic, json, 0);
    pub("rom_data", json, 0);

    // it disconnects from the gateway
    discon();

    xtimer_sleep(3);


  return 0;
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


int read_distance(gpio_t triggerPin){ 
	echo_time = 0;
	gpio_clear(triggerPin);
	xtimer_usleep(20);
	gpio_set(triggerPin);
	xtimer_msleep(100);
	return echo_time/58;
}


*/
int main(void){

    /* the main thread needs a msg queue to be able to run `ping6`*/
    msg_init_queue(queue, ARRAY_SIZE(queue));

    /* start the emcute thread */
    thread_create(stack, sizeof(stack), EMCUTE_PRIO, 0, emcute_thread, NULL, "emcute");
    printf("HELLO WORLD\n");

    char * arg[] = {"ifconfig", "4", "add", "2000:2::2"};
    //_gnrc_netif_config(2, arg);
    _gnrc_netif_config(4, arg);



    // pin sensor initialization
    gpio_init(trigger_pin, GPIO_OUT);
    gpio_init_int(echo_pin, GPIO_IN, GPIO_BOTH, &echo_cb, NULL);

    read_distance(trigger_pin);

    gpio_init(trigger_pin2, GPIO_OUT);
    gpio_init_int(echo_pin2, GPIO_IN, GPIO_BOTH, &echo_cb2, NULL);

    read_distance(trigger_pin2);

    int distance=0;
    distance= read_distance(trigger_pin);

    int distance2=0;
    distance2= read_distance(trigger_pin2);

    //int distance=45;
    

    while(1){

        distance = read_distance(trigger_pin);
        printf("Distance of ultrasonic 1: %d cm\n", distance);
        send(distance);


        distance2 = read_distance(trigger_pin2);
        printf("Distance of ultrasonic 2: %d cm\n", distance2);
        send(distance2);
    
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
       

