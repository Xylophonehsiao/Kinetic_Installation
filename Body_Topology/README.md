# Memo for myself
意外的這個裝置做了一年多...  
從硬體、電路、軟體都不斷的更新，只能說做功德了......  

## 2023 version
### Hareware
Using Hall effect sensor(A3144) to make a feedback system to replace the original one (touching limit switch)  
REMEMBER Hall effect sensor detact on the SMALL SIDE !!!   

### Electronic
Add another Arduino to receieve the MIDI ?!   
And the Computer side need an Arduino to send MIDI Signal or using long USB wire to contect?  

1 黃
2 綠
3 藍
4紫
5 (紅)
6 (黑)
7 黑 12-
8 紅 12+

Wire
1 black
2 white
3 red
4 green
5 yellow
6 blue 
7 brown
8 oringe
  
### Software 
Add MIDI Control for final performance  
Need to test QLab MIDI control!  
Need  reset step in Arduino code ~~~


## 2022 version (Hands and Wireless)
### Hardware 
Change DC Motor 
Replace quick release system, and use 
### Electronic
First, wireless control by RX480E-4 module  
Second, power up by three 18650 battary
### Software 
Similar to the Original one.  


## 2021 version (Original)
### Hardware
All made by 3D printing and some metal~  
#### Hands  
LED strip and a dc motor, mechanical is like a little winch.  
the limit switch is made by touching, use the metal tape.  
#### Foots  
LED strip and a dc motor, mechanical is  
#### Head  
LED strip and a air pump.  

### Electronic
Each part of dc motor and LED control with Arduino Nano and L298N Module, 
and four control set control by another Arduino Nano (Master) by switching the switch.  

### Software
see the Arduino Code in Old version folder   
