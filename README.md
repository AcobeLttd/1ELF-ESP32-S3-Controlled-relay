# 1ELF Rud Videregående Skole project.
This is a project from class 1ELF at Rud Videregående Skole (Rud High School). 
I have tried to document as many thing as possible, the code may be a bit harder to understand due to the lack of comments.

I hope this helps maintain this project for future students!

## ESP32-Web-Server-Controlled-Relay
In this project we control a relay using an ESP32-S3 running a modified version of the webserver code forked from [Enjoy-Mechatronics](https://github.com/Enjoy-Mechatronics/ESP32-Web-Server) ESP32 webserver code. 

The main modifications of this code is adding the 128x64 0.96" I<sup>2</sup>C OLED screen support. 

Please fork this project if you plan on changing the code or components.

## Component List
This should be a list of all the components used in this project.

The component list is split up between **High Voltage** and **Low Voltage** components.

### **Low Voltage**
> XIAO ESP32-S3
> 
> 128x64 0.96" I<sup>2</sup>C OLED screen

### **High Voltage**
> Relay
>
> Terminal junction box with at least 4 terminals.
>
> Power bar with the wall connector cut off.
>
> E14 light bulb socket.
>
> E14 light bulb.
>
> USB Power brick.

### **Aquiring components**

The XIAO ESP32-S3 was bought from the offical Seedstudio store on Aliexpress.com. 

The 128x64 0.96" I<sup>2</sup>C OLED screen was aquired from and old Arduino starter kit. 

The relay was given to me by a teacher, but it was originally bought from kjell and company.

The terminal junction box was given to me by a teacher.

The E14 Light bulb socket was found in the back room of the Makerspace.

The E14 light bulb was given to me by a teacher.

The USB power brick was found in the back room of the makerspace while the USB-C cable i already had in my backpack.

## Schematics
Here are the schematics
There are the original schematics and a PCB version.

### Original Schematic
https://github.com/AcobeLttd/1ELF-ESP32-S3-Controlled-relay/blob/321e7b3ae2a83e93db54c75e7673907372022ccd/Schematics/Original/Original%20Schematic.png

