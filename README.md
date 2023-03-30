# Input-output-and-threads

This code is written in C language for the LPC1768 microcontroller. It contains three functions: LED_caller(), JOY_STICK(), and ANALOG_INPUT(). These functions are called in separate threads using the CMSIS-RTOS2 operating system.

<b><h2>Requirements</b></h2>

The following libraries are required to run this code:

- lpc17xx.h
- uart.h
- stdio.h
- GLCD.h
- cmsis_os2.h
- math.h

<b><h2>Functionality</b></h2>

<h3>LED_caller()</h3>
This function sets the pins' direction to output and toggles the LED connected to pin P1.28 whenever the button connected to pin P2.10 is pressed.

<h3>JOY_STICK()</h3>
This function reads the joystick's input and displays the corresponding direction on the GLCD. It also displays whether the joystick is pressed or not.

<h3>ANALOG_INPUT()</h3>
This function reads the analog input from pin P0.25 and displays the value on the console.

<b><h2>Usage</b></h2>

To run this code, simply compile and flash it onto the LPC1768 microcontroller. The functions will automatically be called in separate threads.
