# Ultrasonic Distance Measurement using HC-SR04 and AT89C51 Microcontroller

This project demonstrates the interfacing of an HC-SR04 ultrasonic distance sensor with the AT89C51 microcontroller. The system calculates the distance to an object using the time-of-flight principle and displays the result on a 16x2 LCD.

The microcontroller sends a 10 microsecond trigger pulse to the sensor, waits for the echo signal, and measures the duration using Timer 0. The measured time is converted to distance in centimeters and shown on the LCD. The project is programmed in embedded C and compiled using Keil µVision IDE.

---

## Features

- Sends a 10 microsecond trigger pulse to the sensor
- Measures echo pulse using Timer 0
- Converts time to distance using the formula: distance = time / 58
- Displays result on 16x2 character LCD
- Shows "Out of range!" if no valid signal is received

---

## Components Used

- AT89C51 microcontroller
- HC-SR04 ultrasonic distance sensor
- 16x2 LCD display (HD44780-compatible)
- 10k ohm potentiometer (for LCD contrast)
- Breadboard and jumper wires
- 5V regulated power supply
- Crystal oscillator (typically 11.0592 MHz)

---

## Pin Configuration

| Component           | Microcontroller Pin |
|--------------------|---------------------|
| Trigger (HC-SR04)  | P3.5                |
| Echo (HC-SR04)     | P3.2                |
| LCD RS             | P3.1                |
| LCD RW             | P3.3                |
| LCD E              | P3.4                |
| LCD Data (D0-D7)   | P2.0 - P2.7         |

---

## File Structure

ultrasonic-distance-8051/
│
├── ultrasonic_8051.c              Main source code (Embedded C)
├── ultrasonic_report.pdf          Optional report with diagrams and explanation
├── schematic.png                  Optional circuit diagram
├── README.md                      This file

---

## How to Compile and Run

1. Open Keil µVision IDE
2. Create a new project and select the AT89C51 microcontroller
3. Add ultrasonic_8051.c to the project
4. Build the project to generate the .hex file
5. Upload the .hex file to the AT89C51 using a suitable programmer
6. Connect the components as per the circuit
7. Power on the circuit and observe the LCD output

---

## Applications

- Obstacle detection in robotics
- Smart parking systems
- Security alarms
- Industrial automation

---

## Author

Divyanshu Kalal  
Roll No: 23BEC053  
Nirma University  
Department of Electronics and Communication Engineering

---

## License

This project is intended for academic and educational use only.
