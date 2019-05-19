EESchema Schematic File Version 2
LIBS:Helios-rescue
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
LIBS:Personal library
LIBS:Helios-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 5
Title "Digital to Analog Converter"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L DAC084S085C U5
U 1 1 56B20C0A
P 5250 4800
F 0 "U5" H 5250 5500 60  0000 C CNN
F 1 "DAC084S085C" V 5250 5100 60  0000 C CNN
F 2 "personal:MSOP-10_3x3mm_Pitch0.5mm" H 5250 4800 60  0001 C CNN
F 3 "" H 5250 4800 60  0000 C CNN
	1    5250 4800
	1    0    0    -1  
$EndComp
Text HLabel 4550 4250 0    60   UnSpc ~ 0
3.3V
Text HLabel 5900 4250 2    60   Input ~ 0
SCLK
Text HLabel 5900 4350 2    60   Input ~ 0
!SYNC
Text HLabel 5900 4450 2    60   Input ~ 0
Din
Text HLabel 4550 4650 0    60   Output ~ 0
R
Text HLabel 4550 4550 0    60   Output ~ 0
G
Text HLabel 4550 4450 0    60   Output ~ 0
B
$Comp
L C C10
U 1 1 56B32431
P 4600 3600
F 0 "C10" H 4625 3700 50  0000 L CNN
F 1 "100nF" H 4625 3500 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 4638 3450 50  0001 C CNN
F 3 "" H 4600 3600 50  0000 C CNN
	1    4600 3600
	-1   0    0    1   
$EndComp
Text HLabel 6650 4550 2    60   UnSpc ~ 0
2.5V
Wire Wire Line
	4550 4250 4650 4250
Wire Wire Line
	4550 4350 4650 4350
Wire Wire Line
	4550 4450 4650 4450
Wire Wire Line
	4550 4550 4650 4550
Wire Wire Line
	5800 4250 5900 4250
Wire Wire Line
	5800 4350 5900 4350
Wire Wire Line
	5800 4450 5900 4450
Wire Wire Line
	5800 4650 5900 4650
Wire Wire Line
	5800 4550 6650 4550
Wire Wire Line
	4600 3750 4600 4250
Connection ~ 4600 4250
$Comp
L GND #PWR015
U 1 1 56B430BD
P 4600 3250
F 0 "#PWR015" H 4600 3000 50  0001 C CNN
F 1 "GND" H 4600 3100 50  0000 C CNN
F 2 "" H 4600 3250 50  0000 C CNN
F 3 "" H 4600 3250 50  0000 C CNN
	1    4600 3250
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 3250 4600 3450
Text HLabel 4550 4350 0    60   Output ~ 0
Intensity
Wire Wire Line
	4550 4650 4650 4650
$Comp
L C C11
U 1 1 573A519D
P 4900 3600
F 0 "C11" H 4925 3700 50  0000 L CNN
F 1 "4.7uF" H 4925 3500 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_4x5.3" H 4938 3450 50  0001 C CNN
F 3 "" H 4900 3600 50  0000 C CNN
	1    4900 3600
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 3750 4900 3850
Wire Wire Line
	4900 3850 4600 3850
Connection ~ 4600 3850
Wire Wire Line
	4900 3450 4900 3300
Wire Wire Line
	4900 3300 4600 3300
Connection ~ 4600 3300
$Comp
L C C12
U 1 1 57580D1C
P 6450 4750
F 0 "C12" H 6475 4850 50  0000 L CNN
F 1 "13pF" H 6475 4650 50  0000 L CNN
F 2 "Capacitors_SMD:C_0402" H 6488 4600 50  0001 C CNN
F 3 "" H 6450 4750 50  0000 C CNN
	1    6450 4750
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR016
U 1 1 57580DA3
P 6450 4950
F 0 "#PWR016" H 6450 4700 50  0001 C CNN
F 1 "GND" H 6450 4800 50  0000 C CNN
F 2 "" H 6450 4950 50  0000 C CNN
F 3 "" H 6450 4950 50  0000 C CNN
	1    6450 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 4900 6450 4950
Wire Wire Line
	6450 4600 6450 4550
Connection ~ 6450 4550
$Comp
L GND #PWR017
U 1 1 575A7248
P 5900 4650
F 0 "#PWR017" H 5900 4400 50  0001 C CNN
F 1 "GND" H 5900 4500 50  0000 C CNN
F 2 "" H 5900 4650 50  0000 C CNN
F 3 "" H 5900 4650 50  0000 C CNN
	1    5900 4650
	1    0    0    -1  
$EndComp
$EndSCHEMATC
