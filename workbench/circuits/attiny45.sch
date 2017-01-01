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
LIBS:attiny45-cache
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
	3500 1600 2200 1600
Wire Wire Line
	2200 1600 2200 4100
Wire Wire Line
	4800 2000 6200 2000
Wire Wire Line
	4800 1600 6000 1600
Wire Wire Line
	6000 1600 6000 3700
Wire Wire Line
	6000 3700 5550 3700
$Comp
L ATTINY45-P IC1
U 1 1 58644323
P 4200 3850
F 0 "IC1" H 3050 4250 50  0000 C CNN
F 1 "ATTINY45-P" H 5200 3450 50  0000 C CNN
F 2 "Housings_DIP:DIP-8_W7.62mm" H 5200 3850 50  0000 C CIN
F 3 "" H 4200 3850 50  0000 C CNN
	1    4200 3850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2200 4100 2850 4100
Wire Wire Line
	3500 2000 2500 2000
Wire Wire Line
	2500 2000 2500 3600
Wire Wire Line
	2500 3600 2850 3600
Wire Wire Line
	5600 3600 5550 3600
Wire Wire Line
	5600 3200 5600 3600
Wire Wire Line
	5600 3200 3100 3200
Wire Wire Line
	3100 3200 3100 1800
Wire Wire Line
	3100 1800 3500 1800
Wire Wire Line
	4800 1800 5800 1800
Wire Wire Line
	5800 1800 5800 3800
Wire Wire Line
	5800 3800 5550 3800
Wire Wire Line
	6200 2000 6200 3900
Wire Wire Line
	6200 3900 5550 3900
$EndSCHEMATC
