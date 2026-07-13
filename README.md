ESP32 Air Mouse using MPU6050
Project Documentation
1. Project Overview

The ESP32 Air Mouse is a wireless motion-controlled mouse that uses the MPU6050 6-axis IMU sensor and an ESP32 Development Board. The MPU6050 detects the hand's rotational movement, and the ESP32 converts this motion into mouse cursor movement using Bluetooth HID (Human Interface Device).

The project eliminates the need for a traditional mouse and enables cursor control by simply moving the device in the air. Two push buttons provide left-click and right-click functionality.

2. Components Required
Component	Quantity	Description
ESP32 DevKit V1	1	Main microcontroller with Bluetooth
MPU6050 Gyroscope + Accelerometer	1	Motion sensing module
Push Button	2	Left and Right mouse click
Breadboard	1	Circuit assembly
Jumper Wires	8–10	Connections
USB Cable	1	Programming and Power
3.7V Li-ion Battery (Optional)	1	Portable power source
Battery Charging Module TP4056 (Optional)	1	Battery charging
3. Hardware Specifications
ESP32
Parameter	Value
CPU	Dual-Core Xtensa LX6
Clock Speed	Up to 240 MHz
Flash	4 MB
Bluetooth	BLE 4.2
Operating Voltage	3.3V
GPIO Pins	34
MPU6050
Parameter	Value
Sensor Type	6-Axis IMU
Accelerometer	±2g, ±4g, ±8g, ±16g
Gyroscope	±250, ±500, ±1000, ±2000 °/s
Communication	I2C
Operating Voltage	3.3V–5V
4. Circuit Connections
MPU6050 to ESP32
MPU6050 Pin	ESP32 Pin
VCC	3.3V
GND	GND
SDA	GPIO21
SCL	GPIO22
Button Connections
Left Click
Button Pin	ESP32
One Terminal	GPIO18
Other Terminal	GND
Right Click
Button Pin	ESP32
One Terminal	GPIO19
Other Terminal	GND

The ESP32 uses INPUT_PULLUP, so no external resistors are required.

5. Software Libraries

Install the following libraries using the Arduino IDE Library Manager:

Required Libraries
Wire
MPU6050
ESP32 BLE Mouse
6. Working Principle

The project works in four major stages:

Step 1: Motion Detection

The MPU6050 continuously measures:

Angular velocity (Gyroscope)
Linear acceleration (Accelerometer)

Although the MPU6050 provides both acceleration and gyroscope data, this project primarily uses the gyroscope to control cursor movement.

Step 2: Reading Sensor Data

The ESP32 reads:

gx
gy
gz

using

mpu.getMotion6()

These values represent rotational speeds along the X, Y, and Z axes.

Step 3: Convert Motion into Cursor Movement

The gyroscope values are converted into mouse movement:

moveX = (-gz + gy) / gyroSensitivity;
moveY = -gx / gyroSensitivity;

Where:

gx = Rotation about X-axis
gy = Rotation about Y-axis
gz = Rotation about Z-axis

The variable

gyroSensitivity

controls cursor speed.

Lower values produce faster cursor movement, while higher values make the cursor move more slowly and smoothly.

Step 4: Bluetooth Mouse

The ESP32 sends cursor movement to the paired computer using Bluetooth HID:

bleMouse.move(dx, dy);

The computer recognizes the ESP32 as a standard Bluetooth mouse, requiring no additional drivers.

7. Button Operation
Left Button

When GPIO18 is pressed:

bleMouse.press(MOUSE_LEFT);

When released:

bleMouse.release(MOUSE_LEFT);
Right Button

When GPIO19 is pressed:

bleMouse.press(MOUSE_RIGHT);

When released:

bleMouse.release(MOUSE_RIGHT);
8. Program Flow
Power ON
    │
    ▼
Initialize ESP32
    │
    ▼
Initialize MPU6050
    │
    ▼
Start Bluetooth HID
    │
    ▼
Wait for Bluetooth Pairing
    │
    ▼
Read Gyroscope Values
    │
    ▼
Convert Motion to Cursor Movement
    │
    ▼
Check Button States
    │
    ▼
Send Mouse Movement via BLE
    │
    ▼
Repeat Every 5 ms
9. Bluetooth Pairing
Upload the program to the ESP32.
Power the board.
Open Bluetooth settings on your computer.
Search for:
ESP32_AirMouse
Pair and connect.
The ESP32 is now ready to function as a Bluetooth mouse.
10. Cursor Sensitivity

The cursor speed is controlled by:

float gyroSensitivity = 1200.0;
Value	Cursor Speed
600	Very Fast
800	Fast
1200	Medium (Recommended)
1600	Slow
2000	Very Slow
11. Advantages
Wireless operation
Low-cost implementation
Plug-and-play Bluetooth HID
No additional drivers required
Portable and battery-powered
Simple hardware design
Easy to customize
12. Applications
Air mouse for presentations
Smart TV control
Media player navigation
Interactive classroom demonstrations
Virtual reality interfaces
Human-computer interaction projects
Assistive technology
DIY and educational robotics
13. Limitations
Gyroscope drift over time
No automatic calibration
No scrolling functionality
No gesture recognition
Basic cursor smoothing only
14. Future Enhancements
Automatic gyroscope calibration
Cursor smoothing using a Kalman or complementary filter
Scroll wheel functionality
Double-click gesture
Drag-and-drop mode
Adjustable sensitivity via buttons
Battery level monitoring
OLED display for status
Deep sleep mode for power saving
15. Troubleshooting
Problem	Solution
MPU6050 not detected	Check SDA/SCL wiring and power connections
Bluetooth device not visible	Restart the ESP32 and enable Bluetooth on the host device
Cursor drifts	Keep the device stationary during startup or calibrate the gyroscope
Cursor moves too slowly	Decrease gyroSensitivity
Cursor moves too fast	Increase gyroSensitivity
Buttons not working	Verify GPIO18 and GPIO19 wiring and ensure INPUT_PULLUP is used
16. Project Directory Structure
ESP32-AirMouse/
│
├── ESP32_AirMouse.ino
├── README.md
├── LICENSE
├── docs/
│   ├── Circuit_Diagram.png
│   ├── Breadboard_View.jpg
│   ├── Working_Flow.png
│   └── Demo.gif
├── images/
│   ├── esp32.jpg
│   ├── mpu6050.jpg
│   └── setup.jpg
└── libraries.md
17. Authors

kiran Y Alur
SaiKiran R Baddi
Omkar I angadi
Omkareshwar M Kamblimath

Project: ESP32 Air Mouse using MPU6050
Platform: ESP32 DevKit V1
Programming Language: Arduino (C++)
Communication Protocol: Bluetooth Low Energy (BLE HID)
Sensor Interface: I²C (GPIO21 & GPIO22)
