
# 2nd Delivery


This document is about the changes made to the project, and rather than the state of the project as of now, is meant to identify what work has been done and what work is left to do.

## Addressing the comments:
SBIM

    clear goal, but only qualitative, pleas provide quantitative goal and requirements
    time consuming: people spend 30min to go from A to B we aim at reducing 20%
    wifi make sense in this case, but then you need power plugs and the installation costs are significant
    start from the problem, define the metrics (e.g. room occupied), select the sensors, evaluate the performance 
    availability is mentioned only at the end
    negligible with respect to the power consumption of the whole building ... make sense but it is almost obvious
    metrics are very generic
    
In order to cover this issues, we decided to put more focus on our goal, concentrating mainly on one problem: the amount of people inside a room.

We also put a special effort into an intial performance evaluation, giving several reason to why it is best to attach the system to the electrical grid, the amount of precision that we want to achieve with this system and quantitavie reasons in our goal explanation
## Changes made:

The changes made to the concept are pretty significant, and with them there were also changes to the evaluation method. However, the overall infrastructure of the technology remained pretty similar. The main goal now is to measure and to present different configurations of people counting in order to provide the most effective results possible.

## Technical work:

We managed to experiment with a first demo of a basic configuration, that sent the data to the mqtt broker and then the iot core, to correctly identify a person entering or leaving the room.

![1st config.jpg](https://github.com/gibr098/Iot-Group-Project/blob/main/second_delivery/1st%20config.jpg)

##Functionalities missing:
A configuration capable of working with people that do not come in in a straigh line

## Evaluation done:
* We calculated the energy consumtpion
* We made sure that the bandwith is high enough to send the data when we want
* We calculated how much the sampling rate should be (overestimation)

## Evaluation left:
The most imporant thing is to evaluate the system in a real-life situation with all possible configurations.
We also have to compute the amount of time that the map needs to update.
