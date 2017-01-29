EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:atmega328p-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328-P µC1
U 1 1 583CCC58
P 4100 3900
F 0 "µC1" H 3350 5150 50  0000 L BNN
F 1 "ATMEGA328-P" H 4500 2500 50  0000 L BNN
F 2 "Housings_DIP:DIP-28_W7.62mm" H 4100 3900 50  0001 C CIN
F 3 "" H 4100 3900 50  0000 C CNN
	1    4100 3900
	1    0    0    -1  
$EndComp
$Sheet
S 3500 1400 1300 800 
U 58603D0F
F0 "Mira" 60
F1 "mira.sch" 60
F2 "VCC" I L 3500 2000 60 
F3 "AREF" I L 3500 1800 60 
F4 "GND" I L 3500 1600 60 
F5 "FIRE" I R 4800 2000 60 
F6 "LED" I R 4800 1600 60 
F7 "BUTTON" I R 4800 1800 60 
$EndSheet
Wire Wire Line
	3500 2000 2950 2000
Wire Wire Line
	2950 2000 2950 2800
Wire Wire Line
	2950 2800 2950 3100
Wire Wire Line
	2950 3100 3200 3100
Wire Wire Line
	3200 2800 2950 2800
Connection ~ 2950 2800
Wire Wire Line
	3500 1800 2600 1800
Wire Wire Line
	2600 1800 2600 3400
Wire Wire Line
	2600 3400 3200 3400
Wire Wire Line
	3500 1600 2200 1600
Wire Wire Line
	2200 1600 2200 5100
Wire Wire Line
	2200 5100 2950 5100
Wire Wire Line
	2950 5100 3200 5100
Wire Wire Line
	3200 5000 2950 5000
Wire Wire Line
	2950 5000 2950 5100
Connection ~ 2950 5100
Wire Wire Line
	4800 2000 5300 2000
Wire Wire Line
	5300 2000 5300 2800
Wire Wire Line
	5300 2800 5100 2800
Wire Wire Line
	4800 1600 6000 1600
Wire Wire Line
	6000 1600 6000 5000
Wire Wire Line
	6000 5000 5100 5000
Wire Wire Line
	5100 3100 5600 3100
Wire Wire Line
	5600 3100 5600 1800
Wire Wire Line
	5600 1800 4800 1800
$EndSCHEMATC
