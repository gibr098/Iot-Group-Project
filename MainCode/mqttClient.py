# run: pip install paho-mqtt 
# paho mqtt
from operator import index
import paho.mqtt.client as paho
import paho.mqtt.publish as publish
import os
import json
import ssl
from time import sleep
from random import uniform
import sys


def on_connect(client, userdata, flags, rc):
    print("Connection returned result:" + str(rc))
    client.subscribe("rom_data")

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    mqttc.publish("rom_data", str(msg.payload), qos=1)

def callback(client, userdata, message):
    jsonmessage = json.loads(message.payload)
    publish.single("rom_data", jsonmessage["message"], hostname="localhost", port=1886, client_id="2")


mqttc = paho.Client()
mqttc.on_connect = on_connect
mqttc.on_message = on_message

awshost = "a1s6jz3t5uc3yt-ats.iot.us-east-1.amazonaws.com"
awsport = 8883

clientId = "testVir1"
thingNmae = "testVir1"

caPath = 'certificates/AmazonRootCA1.crt'
certPath = 'certificates/certificate.pem'
keyPath = 'certificates/private.pem'

mqttc.subscribe("rom_data", 1, callback)

mqttc.tls_set(caPath, certfile=certPath, keyfile=keyPath,tls_version=ssl.PROTOCOL_TLSv1_2, ciphers=None)
mqttc.connect(awshost, awsport, keepalive=60)

mqttc.loop_start()
