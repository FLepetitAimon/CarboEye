EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Amplificateur photodiode"
Date ""
Rev "1.0"
Comp "OMP - INSA"
Comment1 "François LEPETIT-AIMON"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:D_Photo D1
U 1 1 60D5079C
P 2100 1800
F 0 "D1" V 2100 1550 50  0000 C CNN
F 1 "D_Photo" V 2000 1550 50  0000 C CNN
F 2 "SamacSys_Parts:S1223-01" H 2050 1800 50  0001 C CNN
F 3 "~" H 2050 1800 50  0001 C CNN
	1    2100 1800
	0    1    1    0   
$EndComp
$Comp
L Device:D_Photo D2
U 1 1 60D50DC6
P 5850 1800
F 0 "D2" H 5800 2095 50  0000 C CNN
F 1 "D_Photo" H 5800 2004 50  0000 C CNN
F 2 "SamacSys_Parts:S1223-01" H 5800 1800 50  0001 C CNN
F 3 "~" H 5800 1800 50  0001 C CNN
	1    5850 1800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 60D514A1
P 2100 2100
F 0 "#PWR0101" H 2100 1850 50  0001 C CNN
F 1 "GND" V 2105 1972 50  0000 R CNN
F 2 "" H 2100 2100 50  0001 C CNN
F 3 "" H 2100 2100 50  0001 C CNN
	1    2100 2100
	0    1    1    0   
$EndComp
Wire Wire Line
	2100 1600 2450 1600
Wire Wire Line
	2100 1900 2100 2100
$Comp
L power:GND #PWR0102
U 1 1 60D55C4B
P 3300 2950
F 0 "#PWR0102" H 3300 2700 50  0001 C CNN
F 1 "GND" H 3305 2777 50  0000 C CNN
F 2 "" H 3300 2950 50  0001 C CNN
F 3 "" H 3300 2950 50  0001 C CNN
	1    3300 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 60D562AD
P 3300 2650
F 0 "R1" H 3370 2696 50  0000 L CNN
F 1 "280" H 3370 2605 50  0000 L CNN
F 2 "" V 3230 2650 50  0001 C CNN
F 3 "~" H 3300 2650 50  0001 C CNN
	1    3300 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 60D573C8
P 3750 2450
F 0 "R2" V 3543 2450 50  0000 C CNN
F 1 "13.7K" V 3634 2450 50  0000 C CNN
F 2 "" V 3680 2450 50  0001 C CNN
F 3 "~" H 3750 2450 50  0001 C CNN
	1    3750 2450
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 60D57BA4
P 2850 2650
F 0 "C1" H 2965 2696 50  0000 L CNN
F 1 "1u" H 2965 2605 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D8.0mm_W2.5mm_P5.00mm" H 2888 2500 50  0001 C CNN
F 3 "~" H 2850 2650 50  0001 C CNN
	1    2850 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2950 3300 2800
Connection ~ 3300 2800
Wire Wire Line
	3300 2500 3300 2450
Wire Wire Line
	3300 2450 3600 2450
Connection ~ 3300 2500
$Comp
L power:+5V #PWR0103
U 1 1 60D58CDF
P 3900 2450
F 0 "#PWR0103" H 3900 2300 50  0001 C CNN
F 1 "+5V" V 3915 2578 50  0000 L CNN
F 2 "" H 3900 2450 50  0001 C CNN
F 3 "" H 3900 2450 50  0001 C CNN
	1    3900 2450
	0    1    1    0   
$EndComp
Wire Wire Line
	2950 1500 2650 1500
Wire Wire Line
	2650 2500 2850 2500
$Comp
L Device:R R11
U 1 1 60D5D500
P 900 1550
F 0 "R11" H 970 1596 50  0000 L CNN
F 1 "2M" H 970 1505 50  0000 L CNN
F 2 "" V 830 1550 50  0001 C CNN
F 3 "~" H 900 1550 50  0001 C CNN
	1    900  1550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 60D611E4
P 1300 1550
F 0 "C11" H 1415 1596 50  0000 L CNN
F 1 "3.3p" H 1415 1505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D8.0mm_W2.5mm_P5.00mm" H 1338 1400 50  0001 C CNN
F 3 "~" H 1300 1550 50  0001 C CNN
	1    1300 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R21
U 1 1 60D66019
P 6550 1750
F 0 "R21" H 6620 1796 50  0000 L CNN
F 1 "2M" H 6620 1705 50  0000 L CNN
F 2 "" V 6480 1750 50  0001 C CNN
F 3 "~" H 6550 1750 50  0001 C CNN
	1    6550 1750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C21
U 1 1 60D66BC6
P 6950 1750
F 0 "C21" H 7065 1796 50  0000 L CNN
F 1 "3.3p" H 7065 1705 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D8.0mm_W2.5mm_P5.00mm" H 6988 1600 50  0001 C CNN
F 3 "~" H 6950 1750 50  0001 C CNN
	1    6950 1750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 60D6AD83
P 5850 1900
F 0 "#PWR0104" H 5850 1650 50  0001 C CNN
F 1 "GND" H 5855 1727 50  0000 C CNN
F 2 "" H 5850 1900 50  0001 C CNN
F 3 "" H 5850 1900 50  0001 C CNN
	1    5850 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1600 6950 1600
Wire Wire Line
	6550 1900 6950 1900
Wire Wire Line
	900  1400 1300 1400
Wire Wire Line
	5850 1600 5350 1600
Wire Wire Line
	1300 1400 2450 1400
Wire Wire Line
	2450 1400 2450 1600
Connection ~ 1300 1400
Connection ~ 2450 1600
Wire Wire Line
	2450 1600 2950 1600
Wire Wire Line
	1600 1700 1600 2300
Wire Wire Line
	1600 2300 2450 2300
Wire Wire Line
	2450 2300 2450 1700
Wire Wire Line
	2450 1700 2950 1700
Wire Wire Line
	1300 1700 1600 1700
Connection ~ 1300 1700
Wire Wire Line
	5850 1600 6550 1600
Connection ~ 5850 1600
Connection ~ 6550 1600
Wire Wire Line
	6550 1900 6550 2100
Wire Wire Line
	6550 2200 5350 2200
Wire Wire Line
	5350 2200 5350 1700
Connection ~ 6550 1900
Wire Wire Line
	2650 1500 2650 2200
Wire Wire Line
	7300 1500 7300 2350
Wire Wire Line
	7300 2350 4150 2350
Wire Wire Line
	4150 2350 4150 2200
Wire Wire Line
	4150 2200 2650 2200
Connection ~ 2650 2200
Wire Wire Line
	2650 2200 2650 2500
$Comp
L power:+5V #PWR0105
U 1 1 60D7A619
P 2950 1400
F 0 "#PWR0105" H 2950 1250 50  0001 C CNN
F 1 "+5V" V 2965 1528 50  0000 L CNN
F 2 "" H 2950 1400 50  0001 C CNN
F 3 "" H 2950 1400 50  0001 C CNN
	1    2950 1400
	0    -1   -1   0   
$EndComp
$Comp
L CircuitPrincipaleCarbonEye-rescue:OPA4227PA-OPA4227PA U1
U 1 1 60D4A1CB
P 2950 1100
F 0 "U1" H 4150 1487 60  0000 C CNN
F 1 "OPA4227PA" H 4150 1381 60  0000 C CNN
F 2 "" H 4150 1340 60  0001 C CNN
F 3 "" H 2950 1100 60  0000 C CNN
	1    2950 1100
	1    0    0    -1  
$EndComp
Connection ~ 2850 2500
Wire Wire Line
	2850 2500 3300 2500
Wire Wire Line
	2850 2800 3300 2800
Wire Wire Line
	2450 2300 2450 3350
Connection ~ 2450 2300
Wire Wire Line
	6550 2100 7650 2100
Connection ~ 6550 2100
Wire Wire Line
	6550 2100 6550 2200
Wire Wire Line
	900  1700 1300 1700
Wire Wire Line
	5350 1500 7300 1500
NoConn ~ 2950 1100
NoConn ~ 2950 1200
NoConn ~ 2950 1300
NoConn ~ 5350 1100
NoConn ~ 5350 1200
NoConn ~ 5350 1300
$Comp
L power:GND #PWR0110
U 1 1 60E9028A
P 5350 1400
F 0 "#PWR0110" H 5350 1150 50  0001 C CNN
F 1 "GND" V 5355 1272 50  0000 R CNN
F 2 "" H 5350 1400 50  0001 C CNN
F 3 "" H 5350 1400 50  0001 C CNN
	1    5350 1400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 60E90A7E
P 1550 900
F 0 "#PWR0111" H 1550 650 50  0001 C CNN
F 1 "GND" V 1555 772 50  0000 R CNN
F 2 "" H 1550 900 50  0001 C CNN
F 3 "" H 1550 900 50  0001 C CNN
	1    1550 900 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0112
U 1 1 60E90F99
P 1850 900
F 0 "#PWR0112" H 1850 750 50  0001 C CNN
F 1 "+5V" V 1865 1028 50  0000 L CNN
F 2 "" H 1850 900 50  0001 C CNN
F 3 "" H 1850 900 50  0001 C CNN
	1    1850 900 
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 60E91B93
P 1550 750
F 0 "#FLG0101" H 1550 825 50  0001 C CNN
F 1 "PWR_FLAG" H 1550 923 50  0000 C CNN
F 2 "" H 1550 750 50  0001 C CNN
F 3 "~" H 1550 750 50  0001 C CNN
	1    1550 750 
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 60E91F58
P 1850 750
F 0 "#FLG0102" H 1850 825 50  0001 C CNN
F 1 "PWR_FLAG" H 1850 923 50  0000 C CNN
F 2 "" H 1850 750 50  0001 C CNN
F 3 "~" H 1850 750 50  0001 C CNN
	1    1850 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 750  1850 900 
Wire Wire Line
	1550 750  1550 900 
$Comp
L SamacSys_Parts:AD7714AN-5 IC?
U 1 1 610ACF05
P 8500 2000
F 0 "IC?" H 9350 2265 50  0000 C CNN
F 1 "AD7714AN-5" H 9350 2174 50  0000 C CNN
F 2 "DIP787W50P254L3116H762Q24N" H 10050 2100 50  0001 L CNN
F 3 "https://www.arrow.com/en/products/ad7714an-5/analog-devices" H 10050 2000 50  0001 L CNN
F 4 "Signal Conditioning ADC" H 10050 1900 50  0001 L CNN "Description"
F 5 "7.62" H 10050 1800 50  0001 L CNN "Height"
F 6 "Analog Devices" H 10050 1700 50  0001 L CNN "Manufacturer_Name"
F 7 "AD7714AN-5" H 10050 1600 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "584-AD7714AN-5" H 10050 1500 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.com/Search/Refine.aspx?Keyword=584-AD7714AN-5" H 10050 1400 50  0001 L CNN "Mouser Price/Stock"
F 10 "AD7714AN-5" H 10050 1300 50  0001 L CNN "Arrow Part Number"
F 11 "https://www.arrow.com/en/products/ad7714an-5/analog-devices" H 10050 1200 50  0001 L CNN "Arrow Price/Stock"
	1    8500 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J?
U 1 1 610B18D7
P 8400 1200
F 0 "J?" V 8554 812 50  0000 R CNN
F 1 "Conn_01x06_Male" V 8463 812 50  0000 R CNN
F 2 "" H 8400 1200 50  0001 C CNN
F 3 "~" H 8400 1200 50  0001 C CNN
	1    8400 1200
	0    -1   -1   0   
$EndComp
Text Label 8200 1000 1    50   ~ 0
GND
Text Label 8300 1000 1    50   ~ 0
Vcc
Text Label 8400 1000 1    50   ~ 0
SCLK
Text Label 8500 1000 1    50   ~ 0
MISO
Text Label 8600 1000 1    50   ~ 0
MOSI
Text Label 8700 1000 1    50   ~ 0
RESET
Wire Wire Line
	8500 2000 8500 1400
Wire Wire Line
	8500 1400 8400 1400
Wire Wire Line
	8400 1000 8400 1400
$Comp
L power:GND #PWR?
U 1 1 610B7067
P 8500 2300
F 0 "#PWR?" H 8500 2050 50  0001 C CNN
F 1 "GND" V 8505 2172 50  0000 R CNN
F 2 "" H 8500 2300 50  0001 C CNN
F 3 "" H 8500 2300 50  0001 C CNN
	1    8500 2300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610BAD23
P 10200 3000
F 0 "#PWR?" H 10200 2750 50  0001 C CNN
F 1 "GND" V 10205 2872 50  0000 R CNN
F 2 "" H 10200 3000 50  0001 C CNN
F 3 "" H 10200 3000 50  0001 C CNN
	1    10200 3000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610BB1D8
P 10200 2000
F 0 "#PWR?" H 10200 1750 50  0001 C CNN
F 1 "GND" V 10205 1872 50  0000 R CNN
F 2 "" H 10200 2000 50  0001 C CNN
F 3 "" H 10200 2000 50  0001 C CNN
	1    10200 2000
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610BBD8D
P 10200 2600
F 0 "#PWR?" H 10200 2350 50  0001 C CNN
F 1 "GND" V 10205 2472 50  0000 R CNN
F 2 "" H 10200 2600 50  0001 C CNN
F 3 "" H 10200 2600 50  0001 C CNN
	1    10200 2600
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 610BE47D
P 10200 2100
F 0 "#PWR?" H 10200 1950 50  0001 C CNN
F 1 "+5V" V 10215 2228 50  0000 L CNN
F 2 "" H 10200 2100 50  0001 C CNN
F 3 "" H 10200 2100 50  0001 C CNN
	1    10200 2100
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 610BF636
P 8500 3100
F 0 "#PWR?" H 8500 2950 50  0001 C CNN
F 1 "+5V" V 8515 3228 50  0000 L CNN
F 2 "" H 8500 3100 50  0001 C CNN
F 3 "" H 8500 3100 50  0001 C CNN
	1    8500 3100
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 610C1C0A
P 8500 2400
F 0 "#PWR?" H 8500 2250 50  0001 C CNN
F 1 "+5V" V 8515 2528 50  0000 L CNN
F 2 "" H 8500 2400 50  0001 C CNN
F 3 "" H 8500 2400 50  0001 C CNN
	1    8500 2400
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 610C2756
P 8500 3000
F 0 "#PWR?" H 8500 2850 50  0001 C CNN
F 1 "+5V" V 8515 3128 50  0000 L CNN
F 2 "" H 8500 3000 50  0001 C CNN
F 3 "" H 8500 3000 50  0001 C CNN
	1    8500 3000
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 610C2E99
P 10200 2900
F 0 "#PWR?" H 10200 2750 50  0001 C CNN
F 1 "+5V" V 10215 3028 50  0000 L CNN
F 2 "" H 10200 2900 50  0001 C CNN
F 3 "" H 10200 2900 50  0001 C CNN
	1    10200 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	8500 2500 8050 2500
Wire Wire Line
	8050 2500 8050 1450
Wire Wire Line
	8050 1450 8700 1450
Wire Wire Line
	8700 1450 8700 1000
Wire Wire Line
	10200 2200 10550 2200
Wire Wire Line
	10550 2200 10550 1550
Wire Wire Line
	10550 1550 8600 1550
Wire Wire Line
	8600 1550 8600 1000
Wire Wire Line
	10200 2300 10600 2300
Wire Wire Line
	10600 2300 10600 1500
Wire Wire Line
	10600 1500 8550 1500
Wire Wire Line
	8550 1500 8550 1250
Wire Wire Line
	8550 1250 8500 1250
Wire Wire Line
	8500 1250 8500 1000
$Comp
L power:+5V #PWR?
U 1 1 610C9919
P 8300 1000
F 0 "#PWR?" H 8300 850 50  0001 C CNN
F 1 "+5V" V 8315 1128 50  0000 L CNN
F 2 "" H 8300 1000 50  0001 C CNN
F 3 "" H 8300 1000 50  0001 C CNN
	1    8300 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610CA52F
P 8200 1000
F 0 "#PWR?" H 8200 750 50  0001 C CNN
F 1 "GND" H 8205 827 50  0000 C CNN
F 2 "" H 8200 1000 50  0001 C CNN
F 3 "" H 8200 1000 50  0001 C CNN
	1    8200 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	7650 2100 7650 2800
Wire Wire Line
	7650 2800 8500 2800
Wire Wire Line
	2450 3350 8100 3350
Wire Wire Line
	8100 3350 8100 2900
Wire Wire Line
	8100 2900 8500 2900
$Comp
L Device:R R?
U 1 1 610CE7D0
P 9050 4100
F 0 "R?" H 9120 4146 50  0000 L CNN
F 1 "100k" H 9120 4055 50  0000 L CNN
F 2 "" V 8980 4100 50  0001 C CNN
F 3 "~" H 9050 4100 50  0001 C CNN
	1    9050 4100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 610CF573
P 9050 4600
F 0 "R?" H 9120 4646 50  0000 L CNN
F 1 "100k" H 9120 4555 50  0000 L CNN
F 2 "" V 8980 4600 50  0001 C CNN
F 3 "~" H 9050 4600 50  0001 C CNN
	1    9050 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 4250 9050 4350
$Comp
L power:+5V #PWR?
U 1 1 610D143A
P 9050 3950
F 0 "#PWR?" H 9050 3800 50  0001 C CNN
F 1 "+5V" V 9065 4078 50  0000 L CNN
F 2 "" H 9050 3950 50  0001 C CNN
F 3 "" H 9050 3950 50  0001 C CNN
	1    9050 3950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 610D1AF8
P 9050 4750
F 0 "#PWR?" H 9050 4500 50  0001 C CNN
F 1 "GND" H 9055 4577 50  0000 C CNN
F 2 "" H 9050 4750 50  0001 C CNN
F 3 "" H 9050 4750 50  0001 C CNN
	1    9050 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 2700 10700 2700
Wire Wire Line
	10700 2700 10700 4350
Wire Wire Line
	10700 4350 9550 4350
Connection ~ 9050 4350
Wire Wire Line
	9050 4350 9050 4450
$Comp
L Connector:Conn_01x02_Male J?
U 1 1 610D67FD
P 10600 900
F 0 "J?" V 10662 944 50  0000 L CNN
F 1 "Conn_01x02_Male" V 10753 944 50  0000 L CNN
F 2 "" H 10600 900 50  0001 C CNN
F 3 "~" H 10600 900 50  0001 C CNN
	1    10600 900 
	0    1    1    0   
$EndComp
Wire Wire Line
	10500 1100 10500 1600
Wire Wire Line
	10500 1600 8400 1600
Wire Wire Line
	8400 1600 8400 2100
Wire Wire Line
	8400 2100 8500 2100
Wire Wire Line
	10200 2500 10700 2500
Wire Wire Line
	10700 2500 10700 1250
Wire Wire Line
	10700 1250 10600 1250
Wire Wire Line
	10600 1250 10600 1100
NoConn ~ 8500 2200
NoConn ~ 10200 2400
NoConn ~ 10200 2800
$Comp
L power:GND #PWR?
U 1 1 610E22F9
P 10200 3100
F 0 "#PWR?" H 10200 2850 50  0001 C CNN
F 1 "GND" V 10205 2972 50  0000 R CNN
F 2 "" H 10200 3100 50  0001 C CNN
F 3 "" H 10200 3100 50  0001 C CNN
	1    10200 3100
	0    -1   -1   0   
$EndComp
NoConn ~ 8500 2600
NoConn ~ 8500 2700
$Comp
L Device:C C?
U 1 1 610F0E50
P 9550 4600
F 0 "C?" H 9665 4646 50  0000 L CNN
F 1 "1u" H 9665 4555 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D8.0mm_W2.5mm_P5.00mm" H 9588 4450 50  0001 C CNN
F 3 "~" H 9550 4600 50  0001 C CNN
	1    9550 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 4800 9550 4800
Wire Wire Line
	9550 4800 9550 4750
Wire Wire Line
	9550 4450 9550 4350
Connection ~ 9550 4350
Wire Wire Line
	9550 4350 9050 4350
$EndSCHEMATC
