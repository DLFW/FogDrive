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
Sheet 2 2
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
L R R2
U 1 1 583CCC74
P 3700 5000
F 0 "R2" V 3600 5000 50  0000 C CNN
F 1 "100Ω" V 3800 5000 50  0000 C CNN
F 2 "Resistors_THT:Resistor_Horizontal_RM10mm" V 3630 5000 50  0001 C CNN
F 3 "" H 3700 5000 50  0000 C CNN
	1    3700 5000
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 583CCC75
P 3700 4500
F 0 "D1" H 3700 4400 50  0000 C CNN
F 1 "low current LED" H 3700 4650 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 3700 4500 50  0001 C CNN
F 3 "" H 3700 4500 50  0000 C CNN
	1    3700 4500
	0    -1   1    0   
$EndComp
Wire Wire Line
	3700 4850 3700 4650
$Comp
L +BATT #PWR1
U 1 1 58603FE1
P 1600 2700
F 0 "#PWR1" H 1600 2550 50  0001 C CNN
F 1 "+BATT" H 1600 2840 50  0000 C CNN
F 2 "" H 1600 2700 50  0000 C CNN
F 3 "" H 1600 2700 50  0000 C CNN
	1    1600 2700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 586044F3
P 1600 4300
F 0 "#PWR2" H 1600 4050 50  0001 C CNN
F 1 "GND" H 1600 4150 50  0000 C CNN
F 2 "" H 1600 4300 50  0000 C CNN
F 3 "" H 1600 4300 50  0000 C CNN
	1    1600 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 4050 4500 4050
Wire Wire Line
	1600 3950 1600 4300
Connection ~ 1600 4050
$Comp
L C C2
U 1 1 58604591
P 1600 3800
F 0 "C2" H 1625 3900 50  0000 L CNN
F 1 "10nF" H 1625 3700 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3_P2.5" H 1638 3650 50  0001 C CNN
F 3 "" H 1600 3800 50  0000 C CNN
	1    1600 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 3650 1600 3600
Wire Wire Line
	1600 3600 1200 3600
Wire Wire Line
	1200 3200 5100 3200
$Comp
L C C1
U 1 1 5860485C
P 2050 3800
F 0 "C1" H 2075 3900 50  0000 L CNN
F 1 "10nF" H 2075 3700 50  0000 L CNN
F 2 "Capacitors_THT:C_Disc_D3_P2.5" H 2088 3650 50  0001 C CNN
F 3 "" H 2050 3800 50  0000 C CNN
	1    2050 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 3650 2050 3200
Connection ~ 2050 3200
Wire Wire Line
	2050 3950 2050 4050
Connection ~ 2050 4050
Wire Wire Line
	1600 2700 1600 3200
Connection ~ 1600 3200
$Comp
L Q_NMOS_DGS Q1
U 1 1 58604A0A
P 4700 4150
F 0 "Q1" V 5000 4200 50  0000 R CNN
F 1 "RLB3034" V 4900 4300 50  0000 R CNN
F 2 "TO_SOT_Packages_SMD:SOT-23_Handsoldering" V 4600 3900 50  0001 C CNN
F 3 "" H 4700 4150 50  0000 C CNN
	1    4700 4150
	0    1    -1   0   
$EndComp
$Comp
L GS2 CON1
U 1 1 586055FF
P 5100 3550
F 0 "CON1" H 5200 3700 50  0000 C CNN
F 1 "Vaporizer" H 5200 3401 50  0000 C CNN
F 2 "Connectors:GS2" V 5174 3550 50  0000 C CNN
F 3 "" H 5100 3550 50  0000 C CNN
	1    5100 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 3200 5100 3350
Wire Wire Line
	4900 4050 5100 4050
Wire Wire Line
	5100 4050 5100 3750
Wire Wire Line
	4700 4350 4700 5300
Wire Wire Line
	4700 4400 4500 4400
Connection ~ 4700 4400
$Comp
L R R1
U 1 1 58605B36
P 4350 4400
F 0 "R1" V 4250 4400 50  0000 C CNN
F 1 "22kΩ" V 4450 4400 50  0000 C CNN
F 2 "Resistors_THT:Resistor_Horizontal_RM10mm" V 4280 4400 50  0001 C CNN
F 3 "" H 4350 4400 50  0000 C CNN
	1    4350 4400
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 4400 4050 4400
Wire Wire Line
	4050 4400 4050 4050
Connection ~ 4050 4050
Wire Wire Line
	3700 4350 3700 4050
Connection ~ 3700 4050
Wire Wire Line
	3700 5300 3700 5150
Text HLabel 1200 3200 0    60   Input ~ 0
VCC
Text HLabel 1200 3600 0    60   Input ~ 0
AREF
Text HLabel 1200 4050 0    60   Input ~ 0
GND
Text HLabel 4700 5300 3    60   Input ~ 0
FIRE
Text HLabel 3700 5300 3    60   Input ~ 0
LED
$Comp
L GS2 CON2
U 1 1 5860804E
P 2800 4600
F 0 "CON2" H 2900 4750 50  0000 C CNN
F 1 "Button" H 2900 4451 50  0000 C CNN
F 2 "Connectors:GS2" V 2874 4600 50  0000 C CNN
F 3 "" H 2800 4600 50  0000 C CNN
	1    2800 4600
	1    0    0    -1  
$EndComp
Text HLabel 2800 5300 3    60   Input ~ 0
BUTTON
Wire Wire Line
	2800 5300 2800 4800
Wire Wire Line
	2800 4400 2800 4050
Connection ~ 2800 4050
$EndSCHEMATC
