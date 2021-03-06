EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L power:GND #PWR03
U 1 1 60391EFB
P 4450 1950
F 0 "#PWR03" H 4450 1700 50  0001 C CNN
F 1 "GND" H 4455 1777 50  0000 C CNN
F 2 "" H 4450 1950 50  0001 C CNN
F 3 "" H 4450 1950 50  0001 C CNN
	1    4450 1950
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR02
U 1 1 603921D6
P 4450 750
F 0 "#PWR02" H 4450 600 50  0001 C CNN
F 1 "+3V3" H 4465 923 50  0000 C CNN
F 2 "" H 4450 750 50  0001 C CNN
F 3 "" H 4450 750 50  0001 C CNN
	1    4450 750 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 60392908
P 3600 1350
F 0 "R2" V 3393 1350 50  0000 C CNN
F 1 "10k" V 3484 1350 50  0000 C CNN
F 2 "" V 3530 1350 50  0001 C CNN
F 3 "~" H 3600 1350 50  0001 C CNN
	1    3600 1350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 60392B3C
P 1850 1700
F 0 "#PWR01" H 1850 1450 50  0001 C CNN
F 1 "GND" H 1855 1527 50  0000 C CNN
F 2 "" H 1850 1700 50  0001 C CNN
F 3 "" H 1850 1700 50  0001 C CNN
	1    1850 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 60393A99
P 1850 1450
F 0 "C1" H 1965 1496 50  0000 L CNN
F 1 "100n" H 1965 1405 50  0000 L CNN
F 2 "" H 1888 1300 50  0001 C CNN
F 3 "~" H 1850 1450 50  0001 C CNN
	1    1850 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1200 1850 1200
Wire Wire Line
	1850 1200 1850 1300
Wire Wire Line
	4250 1350 4450 1350
Wire Wire Line
	4450 1350 4450 1500
Wire Wire Line
	4450 1150 4450 1350
Connection ~ 4450 1350
Wire Wire Line
	3950 1350 3750 1350
Wire Wire Line
	4450 750  4450 850 
Wire Wire Line
	4450 1800 4450 1950
Wire Wire Line
	4450 1350 4850 1350
Wire Wire Line
	3450 1350 3400 1350
Wire Wire Line
	1350 1200 1250 1200
Wire Wire Line
	1850 1200 2150 1200
Connection ~ 1850 1200
Text GLabel 1150 1200 0    50   Input ~ 0
generator
Text GLabel 2150 1200 2    50   Input ~ 0
CH2
Text GLabel 1250 800  1    50   Input ~ 0
CH1
Wire Wire Line
	1250 800  1250 1200
Connection ~ 1250 1200
Wire Wire Line
	1250 1200 1150 1200
Text GLabel 3300 1350 0    50   Input ~ 0
generator
Text GLabel 3400 850  1    50   Input ~ 0
CH1
Wire Wire Line
	3400 850  3400 1350
Connection ~ 3400 1350
Wire Wire Line
	3400 1350 3300 1350
Text GLabel 4850 1350 2    50   Input ~ 0
CH2
$Comp
L Device:R R3
U 1 1 60397639
P 4450 1000
F 0 "R3" H 4380 954 50  0000 R CNN
F 1 "10k" H 4380 1045 50  0000 R CNN
F 2 "" V 4380 1000 50  0001 C CNN
F 3 "~" H 4450 1000 50  0001 C CNN
	1    4450 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:R R4
U 1 1 6039786E
P 4450 1650
F 0 "R4" H 4380 1604 50  0000 R CNN
F 1 "10k" H 4380 1695 50  0000 R CNN
F 2 "" V 4380 1650 50  0001 C CNN
F 3 "~" H 4450 1650 50  0001 C CNN
	1    4450 1650
	-1   0    0    1   
$EndComp
$Comp
L Device:R R1
U 1 1 60397AC7
P 1500 1200
F 0 "R1" V 1707 1200 50  0000 C CNN
F 1 "10k" V 1616 1200 50  0000 C CNN
F 2 "" V 1430 1200 50  0001 C CNN
F 3 "~" H 1500 1200 50  0001 C CNN
	1    1500 1200
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C2
U 1 1 60397FA9
P 4100 1350
F 0 "C2" V 3848 1350 50  0000 C CNN
F 1 "100n" V 3939 1350 50  0000 C CNN
F 2 "" H 4138 1200 50  0001 C CNN
F 3 "~" H 4100 1350 50  0001 C CNN
	1    4100 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	1850 1600 1850 1700
Text Notes 1450 850  0    50   ~ 0
Integrační článek
Text Notes 3700 950  0    50   ~ 0
Derivační článek
$EndSCHEMATC
