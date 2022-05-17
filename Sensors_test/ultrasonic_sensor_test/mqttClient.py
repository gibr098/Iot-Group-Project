# run: pip install paho-mqtt 
# paho mqtt
from operator import index
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

# sample cmd input
# python3 mqttClient.py {a,b,c}
# 3 input args for 3 sensors
# input arg syntax {data1, data2, date3}
# actual output ['mqttClient.py', 'data1', 'data2','data3']
# expected output ['sensor1','sensor2',''sonsor3]
# expected formated string : {
#     "sensor1": "data1",,
#     "sesor2": "data2",
#     "sensor3": "data3" 
# }

inputArg = sys.argv

formatedString='{'

for index,val in enumerate(inputArg):
    if index == 1:
        formatedString += '"sensor1":'+'"'+str(val)+'"}'
    
# print(formatedString)
        

# formattedInput = '{'+'"sensor_data":'+'"'+inputData+'"'+'}'

# # print(inputData)
while True:
    if connflag == True:
        mqttc.publish("rom_data", formatedString, qos=1)
        print("Msg sent: Sensor data -> "+ formatedString)
        sleep(0.5)
        break
    else:
        print("Waiting for connection..")