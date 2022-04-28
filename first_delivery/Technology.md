# Technology

### Main Core Parts
* Environmental Monitoring System
* Ground Server
* Dashboard

### Environmental monitoring System

**Environmental Monitoring System** is the main component of the project. The main purpose of this system is to collect environmantal data from the sensors placed in feasible location of the building and send it through the **Ground Server** to the cloud server and then take actions by sending commands to suitable actuators.

### Ground Server

**Ground Server** acts as a local server that aggregates streams of sensor data from
multiple **Environmental Monitoring Systems** and sends it to the **AWS cloud server** via **MQTT** for
further data processing. Each Environmental Monitoring System will have a unique id for
identification.

### Dashboard

It is the highest level client side component of the project. The **Dashboard** would be
hosted on remote server **(AWS)** with **Node.js** for the server side backend runtime
environment. Backend server side runs using **Express framework** and the frontend is
written using **HTML, Bootstrap, Javascript and EJS View Engine**. All the data
collected from the sensors would be stored in **AWS Dynamo DB**. And finally the
processed data is displayed on **Dashboard** (or possibly on a **mobile app**).

### IoT Architecture

![IotArchitecture](https://user-images.githubusercontent.com/30042823/159380556-12a033e7-b0a5-4973-b486-69c106e3e95b.png)

### System Architecture

![system_architecture](https://user-images.githubusercontent.com/30042823/159380633-c53035a8-05a2-46e0-ab19-4239ae35ea9c.png)

The main purpose of this IoT device is to monitor environmental aspects of the building Workspace occupancy, Parking Space availability and Energy port availability. For workspace occupancy, depending on the noise level the system will determine the crowdedness of the space. For parking spot availability, with light and pressure sensors placed in every spot of the parking lot the sensors will send the light density and prssure level data to the ground server. LED lights will be used as feedback for available space and the available parking spot. 
All the data will be presented in visual form through a web based dashboard which will be hosted on the cloud platform.

### SENSORS
All the sensors are chosen according to the suitability of the project.

* Sound Sensor (& Motion Sensor - under consideration)
* Light Sensor
* Pressure Sensor

### ACTUATORS

* LED - Lights


### COMMUNICATION

* Wifi Module (ESP-01S ESP8266) - Under Consideration 
* LoRaWan - Under Consideration 



## MESSAGE BROKER

### MQTT Broker (AWS Core IOT)

Sensor datas are transmitted through a message broker to the IoT core through publish
method for data preprocessing. Lightweight and is suitable to low bandwidth exchange of data.

### ECLIPSE MOSQUITTO
[Mosquitto](https://mosquitto.org/) is an open source MQTT broker and thus will be the main part of our communication system between the Board and the next part, the Cloud.

### DEVELPOMENT BOARD

### [STM32 Nucleo-64 STM32F401RE](https://www.st.com/en/evaluation-tools/nucleo-f401re.html)
Used as master node to house the sensors

* Microcontroller: STM32F401RET6 (32-bit)
* Architecture: ARM Cortex M4 CPU with FPU
* Power consumption: 2.4uA at standby without RTC
* CPU Frequency: 84 MHz
* Crystal Oscillator Range: 4 to 26 MHz
* MCU Operating Voltage (VDD): 1.7V to 3.6V
* Board Operating Voltage (VIN): 7V to 15V
* Flash Memory: 512KB
* SRAM: 96 KB
* GPIO Pins: 50
* ADC: 12-bit 16Channel
* RTC: In-built 32kHz with calibration
* Timers :
    * 16-bit (6)
    * 32-bit (2)
* Watchdog Timers: 2
* USART/UART Communication: 4
* I2C Communication: 3
* SPI Communication: 3
* USB2.0 Support: Yes
* Internal Crystal Oscillator: Yes, 16MHz
* On Board Debugger: Yes, Serial Wire and JTAG

## CLOUD

### Amazon Web Services
[AWS](https://aws.amazon.com/it/) is an extremely powerful cloud system, it offers different functionalities. One of these is a communcation system with MQTT, supporting both level 0 and level 1 QoS (quality of service)

### AWS Dynamo DB
A database system, able to store all the information coming from the MQTT broker as well as being capable of returning said data.

### AWS SNS
A protocol to communicate with one or more HTTP or HTTPS endpoint. Similar to MQTT, this is also publish/subscribe based.


## DISTRIBUTION

### HTTP ENDPOINT
A communication channel that will be able to request data from the Cloud through the elaboration of the GET requests done by the User

### UBUNTU Server

An Ubuntu server will be hosted on the AWS cloud to run the MQTT broker service and
along with Node js Server for data visualisation.

### JSON rest API

JSON rest API is used as processed dataset for visual representation.

### Web Dashboard

Web dashboard is used as platform to display the dataset in visual form. With Web
dashboard the end user can also send command back to actuators whether to take
action or not.