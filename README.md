# tecknetwifi
## Arduino WiFi Notifier for Tecknet Doorbell

The purpose of this project is to implement the function of receiving notifications from the doorbell Tecknet receiver on our PC or SmartPhone in case we are far away from the receiver, or to help people with reduced hearing.

![Alt text](images/tecknet.jpg?raw=true)
![Alt text](images/tecknet1.jpg?raw=true)
![Alt text](images/tecknet2.jpg?raw=true)

## Materials:
- NodeMCU ESP8266 (or any Arduino with wifi)
- Photodiode
- Resistor 50KOhms

## How it works
The principle of operation is very simple. It consists of monitoring one of the blue leds of the Tecknet receiver using a photodiode and in case of detecting the activation of the LED a message is sent by wifi to the server. The advantage of this system is that no soldering is required on the receiver board and it's compatible with any doorbell with visual alert (the majority).

![Alt text](images/circuito.png?raw=true)