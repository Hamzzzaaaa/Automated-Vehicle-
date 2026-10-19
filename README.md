Automated Vehicle Using Arduino UNO

Project Overview

The Automated Vehicle Using Arduino UNO is an electronics and automation project developed using Tinkercad Circuits. It demonstrates an intelligent vehicle system that uses sensors, motor control, and manual inputs to control vehicle movement and respond to nearby obstacles.

The system combines an ultrasonic sensor, a PIR motion sensor, an L293D motor driver, and DC motors to simulate automated vehicle behavior.

Objectives

- Develop a sensor-based automated vehicle simulation.
- Detect obstacles using an ultrasonic sensor.
- Implement motion detection using a PIR sensor.
- Control vehicle speed based on measured obstacle distance.
- Implement stopping and reversing behavior.
- Enable manual left and right turns using push buttons.

 Hardware Components

| Component | Purpose |
|---|---|
| Arduino UNO | Main controller |
| HC-SR04 Ultrasonic Sensor | Measures obstacle distance |
| PIR Motion Sensor | Detects movement |
| L293D Motor Driver | Controls the DC motors |
| 2 DC Motors | Drive the vehicle |
| 2 Push Buttons | Manual turning controls |
| Breadboard and Jumper Wires | Circuit connections |
| Tinkercad Circuits | Circuit design and simulation |
 ⚙️ Working Principle

1. Obstacle Detection: The HC-SR04 ultrasonic sensor measures the distance between the vehicle and an obstacle.
2. Speed Control: The Arduino selects a speed level according to the measured distance.
3. Motion Detection: When the PIR sensor detects motion, the programmed stop-and-reverse behavior is activated.
4. Manual Turning: Push buttons allow the user to trigger left and right turns.
5. Motor Control: The Arduino sends control signals to the L293D motor driver, which operates the DC motors.

Distance-Based Speed Control

The vehicle uses the following planned distance thresholds for speed selection:

| Obstacle Distance | Vehicle Response |
|---|---|
| Above 300 cm | Gear 5 |
| 250–300 cm | Gear 4 |
| 200–250 cm | Gear 3 |
| 150–200 cm | Gear 2 |
| 100–150 cm | Gear 1 |
| 100 cm or less | Stop |

*Note: These are the configured distance ranges. Actual motor speed depends on the PWM values and the behavior implemented in the Arduino code.*

🔌 Technologies Used

- Arduino C/C++
- Arduino UNO
- Tinkercad Circuits
- Ultrasonic sensing
- PIR motion sensing
- DC motor control
- Embedded systems and automation

🖥️ Simulation

The project was designed and tested in the Tinkercad Circuits simulation environment.

Tinkercad Project Link: https://www.tinkercad.com/things/kGFayXuSt4a-automated-vehicle?sharecode=0DlyOnYI3nyTnuWKW9CMrs5ThhsvW6rA5J0D-uRHQLw 


📚 What I Learned

- Designing electronic circuits using Tinkercad.
- Interfacing sensors with Arduino UNO.
- Controlling DC motors through a motor driver.
- Implementing conditional logic for automated movement.
- Using sensor readings for distance-based control.
- Integrating hardware components into an automation project.


👨‍💻 Author

Syed Hamza Noor
Computer Science and Engineering Student  

