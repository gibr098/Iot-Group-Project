# run: pip install paho-mqtt 
# paho mqtt
import paho.mqtt.client as paho
import os
import ssl
from time import sleep
from random import uniform
import sys

connflag = False

def on_connect(client, userdata, flags, rc):
    global connflag
    connflag = True
    print("Connection returned result:" + str(rc))

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))


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

mqttc.tls_set(caPath, certfile=certPath, keyfile=keyPath,tls_version=ssl.PROTOCOL_TLSv1_2, ciphers=None)
mqttc.connect(awshost, awsport, keepalive=60)

mqttc.loop_start()

# TODO: update the data reading: take input data from command promt

inputData = str(sys.argv[1])
formattedInput = '{'+'"sensor_data":'+'"'+inputData+'"'+'}'

# print(inputData)

while 1==1:
    sleep(0.5)
    if connflag == True:
        mqttc.publish("rom_data", formattedInput, qos=1)
        print("Msg sent: Sensor data -> "+ formattedInput)
    else:
        print("Waiting for connection..")