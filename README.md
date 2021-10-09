# Linear-Stage-with-Closed-Loop-Control
The purpose of this project was to build an automated system capable of moving carriage to predefined locations along a linear path using a closed-loop control. The project involved
applying the principle operations of a DC motor, programmatically controlling the linear position and pseed, and acquiring the system's performance data.

The previous Open-loop control project incorporated a stepper motor to craft a sequence of pulses that allowed the homing stage to move in one direction or another depending on
the electric polarity in the motor. Using full and half stepping sequences, we were able to programmatically control the displacement and speed of the system. The results of the
homing stage showed that an open-loop control presented some cumbersome delayas and there were no feedback from the system to see if the motor was precisely executing the
control signals. The main difference between an open-loop and closed-loop control is that the latter allows us to measure the response and performance of the system compared to 
the control signals we provide.

![closed loop control](https://user-images.githubusercontent.com/92079163/136640764-6a01d4dd-37e7-4c02-8ffb-8f350ba8c0cc.PNG)

A DC motor was incorporated to model a closed-loop system of the same linear homing stage from the previous project. Unlike the stepper motor, the speed of the DC motor can be 
controlled through vaariable voltage. If the terminals of the motor were to be switched, the motor would rotate in the opposite direction. The two encoders A and B attached at the
bottom provide a mechanism to measure teh actual signal from the system. As the motor rotates clockwise, encoder B detects a slight delay compared to encoder A and the opposite 
is true for counterclockwise. While one encoder can determine the speed and displacement, two encoders allow the determination of which direction the motor rotates. Moreover, this 
project modified the previous linear homing stage and execute the same tasks with a DC motor. 

![DC motor diagram](https://user-images.githubusercontent.com/92079163/136640864-e26d8291-cacd-4191-87ae-34c7c90389f6.PNG)

In the final homing sequence:
1. The carriage is initially placed at a maximum distance away from the button switch. Once the sequence begins, this allows for the motor to precisely and incrementally increase speed and it reach its target RPM of the first step.
2. The user manually presses the switch to begin homing. The carriage moves toward the switch at a defined speed.
3. Once the switch detects contact with the carriage, the carriage will retract 10mm from the switch at a reduced speed.
4. The carriage stops and moves again toward the switch at the lowest speed the motor can reliably move. This is to ensure that the carriage moves and detects the switch with higher precision based on the concepts of half stepping.
5. Once the switch detects contact with the carriage again, the carriage moves 30mm away from the switch at 10mm/s 
6. The motor shuts off and finalizes the homing process.

<img src = "https://user-images.githubusercontent.com/92079163/136640956-15b14ac2-9cea-47da-8b8c-e7279be544fa.jpeg" width="500" height="350">
