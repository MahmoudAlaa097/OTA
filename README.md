# Over The Air<br>
This repository contains an Over The Air (OTA) project.<br>
Here we can flash the microcontroller with a new application with the help of a very simple website to choose which application to be burnt.

<strong><em>This System consists of 3 main parts:</em></strong>

## 1- ECU
STM32 microcontroller containing a UART boatloader to burn the new application.
#### Used Peripherials:
<strong><em>01- RCC</em></strong> => For system's clock.<br>
<strong><em>02- FPEC</em></strong> => For boatloader implementation.<br>
<strong><em>03- UART</em></strong> => To communicate with the ESP32.<br>
<strong><em>04- GPIO</em></strong> => To control some LEDs (Applications purposes).<br>

## 2- ESP32
Used as a gateway to communicate with the server for sending and receiving commands and receiveing application executable file.

## 3- Server
Deveolped a very simple PHP server containing a 3 application executable files that we choose which one to be burnt from them.
Deveolped a very simple Website using HTML only to make a web page to choose a file to be burnt.
