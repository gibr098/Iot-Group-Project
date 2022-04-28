# Evaluation
Our system is a real time dynamic map of a building, highliting several crucial information. In this document we will show how we intend to evaluate said system, as well as what are the main constraints of our project

## Network point of view
### How we intend to evaluate the network capabilities

Due to the nature of our system, we should evaluate the maximum load that our communication channel can handle while still mantaining a lenient real-time constraint

* **MQTT** How many incoming messages can MQTT mosquitto handle?
   * This is crucial due to the heay amount of people inside a building and so, the more inputs we can handle the more accurate will be our product

* **CLOUD** What is the message rate at which messages can be sent at the AWS cloud?
   * As our constraint are mainly time based, this statistic is very important to ensure the correct funcionality of our system 

* **HTTP** What is the amount of GET request that our endpoint can handle?
   * This is heavily related to the user experience, mainly because it would avoid problems such as slow loading or outright freezing of the website

## Power and efficiency point of view
### How we intend to evaluate the power management

Our system is entirely located within an already built place and so is natural to think that the energy supply of the building will also power up our system.
* **GOAL** What is ultimately our objective?
   * While it is not the biggest constraint, our desired objective would be having a power consumption low enough to be negligible in respect to the energy consumption of the building 

## End-user point of view
### How we intend to evaluate the user experience

The user experience is mainly tied to the responsiveness and the accuracy of the http endpoint.

* **ACCURACY** How to achieve accuracy?
   * In order to achieve a good accuracy we must impose a (altough lenient) real time constraint on our system, so that the information received are not outdated

* **RESPONSIVENESS** How to achieve responsiveness?
   * To achieve it we must look at the load of the data exchanged and through several testing understand the limit of our system 
