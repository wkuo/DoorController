# DoorController

To control door lock/unlock, open/close


Pin Mapping

| ESP8266 | SD Module |
| --- | --- |
| D5 (GPIO14) | SCK |
| D6 (GPIO12) | MISO | 
| D7 (GPIO13) | MOSI |
| D8 (GPIO15) | CS | 
| Vin | Vcc |
| GND | GND |

| ESP8266 | Shift Register 4595 |
| --- | --- |
| D0 (GPIO16) | SER |    
| SD0 (GPIO0) | RCLK |
| SD3 (GPIO10) | SRCLK |
| 3v3 | Vcc & SRCLR (bar) | 
| GND | GND & OE (bar) |


