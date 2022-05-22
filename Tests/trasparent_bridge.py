from ast import parse
from operator import le
import paho.mqtt.client as mqtt
from AWSIoTPythonSDK.MQTTLib import AWSIoTMQTTClient
import json


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc)) 
    client.subscribe("rom_data") 

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    message = str(msg.payload)[2:len(str(msg.payload))-1]
    aws_publish(AWSclient, message)

def mqtt_publish(mqtt_client, topic, message):
    mqtt_client.publish(topic, message)


def aws_publish(aws_client, message):
    aws_client.publish("rom_data", message, 1)



#can be found as parameter '-e' in the last line of the file start.sh
awshost = "a1s6jz3t5uc3yt-ats.iot.us-east-1.amazonaws.com" 
awsport = 8883

clientId = "testVir1"

caPath = "certificates/AmazonRootCA1.crt"
certPath = "certificates/certificate.pem"
keyPath = "certificates/private.pem"
    


AWSclient = None
AWSclient = AWSIoTMQTTClient(clientId)
AWSclient.configureEndpoint(awshost, awsport)
AWSclient.configureCredentials(caPath, keyPath, certPath)
AWSclient.connect() 


mqttClient = None
mqttClient = mqtt.Client()
mqttClient.on_connect = on_connect
mqttClient.on_message = on_message
mqttClient.connect("localhost", 1886, 60) #connection to broker (subscription is done in the on_connect function)
mqttClient.loop_forever()

