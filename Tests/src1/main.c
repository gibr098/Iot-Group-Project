// Local broker:
// in mosquitto.rsmb/rsmb launch "./src/broker_mqtts config.conf"
//
// Transparent bridge:
// Launch "python3 transparent_bridge.py"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msg.h"
#include "net/emcute.h"
#include "net/ipv6/addr.h"
#include "periph/gpio.h"
#include "xtimer.h"
#include "thread.h"
#include "periph/adc.h"
#include "main.h"

#define RES ADC_RES_8BIT
#define INTERVAL 10*1000000 //usec
#define EMCUTE_PRIO         (THREAD_PRIORITY_MAIN - 1)
#define _IPV6_DEFAULT_PREFIX_LEN        (64U)
#define BROKER_PORT         1885
#define BROKER_ADDRESS      "2000:2::1"
#define TOPIC_RECEIVE       "topic_in"
#define TOPIC_SEND          "topic_out"

//to add addresses to board interface
extern int _gnrc_netif_config(int argc, char **argv);

static char stack[THREAD_STACKSIZE_DEFAULT];
static msg_t queue[8];
static emcute_sub_t subscriptions[1];
static char topics[1][64U];
// *** \/ MQTTS \/ ***

static void *emcute_thread(void *arg){
    (void)arg;
    emcute_run(BROKER_PORT, "board");
    return NULL;
}

static int con(void){
    sock_udp_ep_t gw = { .family = AF_INET6, .port = BROKER_PORT };
    char *topic = NULL;
    char *message = NULL;
    size_t len = 0;

    ipv6_addr_from_str((ipv6_addr_t *)&gw.addr.ipv6, BROKER_ADDRESS);
    emcute_con(&gw, true, topic, message, len, 0);

    return 0;
}

static int pub(char* msg){
    emcute_topic_t t;
    unsigned flags = EMCUTE_QOS_0;
    t.name = TOPIC_SEND;

    emcute_reg(&t);
    emcute_pub(&t, msg, strlen(msg), flags);

    return 0;
}

static void on_pub(const emcute_topic_t *topic, void *data, size_t len){
    (void)topic;

    char *in = (char *)data;
    char msg[len+1];
    strncpy(msg, in, len);
    msg[len] = '\0';
}

static int sub(void){
    unsigned flags = EMCUTE_QOS_0;
    subscriptions[0].cb = on_pub;
    strcpy(topics[0], TOPIC_RECEIVE);
    subscriptions[0].topic.name = topics[0];
    
    emcute_sub(&subscriptions[0], flags);

    return 0;
}

static int add_address(char* addr){
    char * arg[] = {"ifconfig", "4", "add", addr};
    return _gnrc_netif_config(4, arg);
}

// *** /\ MQTTS /\ ***  




void mqtts_init(void){ //initializes the connection with the MQTT-SN broker
    msg_init_queue(queue, ARRAY_SIZE(queue));
    memset(subscriptions, 0, (1 * sizeof(emcute_sub_t)));
    thread_create(stack, sizeof(stack), EMCUTE_PRIO, 0, emcute_thread, NULL, "emcute");
    
    char * addr1 = "2000:2::2";
    add_address(addr1);
    char * addr2 = "ff02::1:ff1c:3fba";
    add_address(addr2);
    char * addr3 = "ff02::1:ff00:2";
    add_address(addr3);

    con();
    sub();
}

int main(void){
    xtimer_sleep(3);
    mqtts_init();

   int distance=45;
    
    while (true) { 
      
    distance += 1;
    char msg[4];
    sprintf(msg, "%d", distance);
    pub(msg);
    
    }
           
        
    xtimer_sleep(1);
    

    return 0;
}
