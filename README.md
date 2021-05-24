# House 2.0 

---
This is a **C++17** project that incorporates HTTP (primarily) and MQT (secondary) technologies to learn about new possibilities with Internet of Things (IoT).

### Requirements
All packages that must be installed in order to be able to compile and run.

### [**Pistache**](https://github.com/pistacheio/pistache) on Linux
Used for managing the **HTTP** protocol.
```shell
sudo add-apt-repository ppa:pistache+team/unstable
sudo apt update
sudo apt install libpistache-dev
```
or local download and install using git and meson (if the above installation does not work).
```shell
git clone https://github.com/pistacheio/pistache.git
cd pistache
meson setup build
meson install -C build
```



### [**Mosquitto**](https://github.com/eclipse/mosquitto) on Linux
Used for managing the **MQTT** protocol.
```shell
sudo apt-get install mosquitto
sudo apt-get install mosquitto-clients
sudo apt-get install -y libmosquitto-dev
```



### [**CrossGuid**](https://github.com/graeme-hill/crossguid)
In order to use this library, we need to install ```libuuid```.
```shell
sudo apt-get install uuid-dev
```



### [**nlohmann/json**](https://github.com/nlohmann/json)
Used to format json. The library is used as a static library in the lib folder.



### **pkg-config**
**pkg-config** is a system for managing library compile and link flags that works with automake and autoconf. manage compile and link flags for libraries
```shell
sudo apt-get update -y
sudo apt-get install -y pkg-config
```



### [**Postman**](https://www.postman.com/) (_optional_)
**Postman** is optional, but recommended facilitating HTTP requests. 

---
## Compile and run
**Be sure** that you have installed **C++17** on your Linux system in order to compile and run.
This application was compiled and run using [CLion IDE](https://www.jetbrains.com/clion/). 

---

## HTTP Requests
Http requests use ```localhost:9080```.
Instead of Postman, you can use linux ```curl``` command to make requests to the server:
* ```curl localhost:9080/curtains/open``` for HTTP GET request;
* ```curl -X POST localhost:9080/curtains/open/15.5``` for HTTP POST requests.
### _Curtains_ functionality:
1. Fully open curtains automatically: ```POST /curtains/open```;
2. Open curtains by a given percentage: ```POST /curtains/open/12```;
3. Fully close curtains automatically: ```POST /curtains/close```.


### _Secret Door_ functionality:
1. Close secret door: ```POST /secretDoor/close```;
2. Open secret door: ```POST /secretDoor/open```;

This request expects values from the POST request's body with the following format:
```json
{
    "pinCode": 1234
}
```
* _**pinCode**_ is the primary pin needed to open the door.
3. Change the secret door's PIN: ```POST /secretDoor/changePin```.
This request expects values from the POST request's body with the following format:
```json
{
  "pinCode": 1234,
  "changePinCode": 1234,
  "newPinCode": 5555
}
```
* _**pinCode**_ is the primary pin needed to open the door.
* _**changePinCode**_ is a secondary pin needed to change the door pin.
* _**newPinCode**_ is the new pin to be swapped with the old one.

### _Windows_ functionality:
1. Open windows: ```POST /windowsLock/openWindows```;
2. Close windows: ```POST /windowsLock/closeWindows```;
3. Close windows if it is raining outside: ```POST /windowsLock/:rain```;
* _rain_ can be ```"true"```, ```"isRaining"``` or ```"rain"```.
4. Choose at what interior house temperature should the windows open: ```POST /windowsLock/:temp/:tempMax/:scale```;
* _scale_ can be ```"F"``` or ```"C"```;
5. Get windows personal user settings: ```GET /windowsLock/userSettings```.

### _Morning alarm_ functionality:
1. Get informations on how to use the morning alarm: ```GET /morningAlarm/info```;
2. Set if the alarms are dismissable: ```POST /morningAlarm/setDismissable/:dismissable```;
3. Set the alarm's time and duration when to ring:```POST /morningAlarm/addAlarm/:hour/:minutes/:duration```;
4. Remove an alarm: ```POST /morningAlarm/removeAlarm/hour/minutes```.

### _Automatic Entrance Door Lock_ functionality:
1. Lock entrance door: ```POST /doorLock/lock```;
2. Unlock entrance door: ```POST /doorLock/unlock```;
3. Automatically lock entrance door at a given time: ```POST /doorLock/setLockTime/hour/minutes```;
4. Get informations on how to use the entrance door lock: ```GET /doorLock/info```;
5. Reset entrance door lock: ```POST /doorLock/reset```.


### _Automatic lights_ functionality:
1. Turn on lights: ```POST /lights/turnOn```;
2. Turn off lights: ```POST /lights/turnOff```;
3. Change ligths color: ```POST /lights/color```;
* light colors can only be: ```"white"```, ```"red"```, ```"green"``` or ```"blue"```.
---


## MQTT
To use [MQTT](https://en.wikipedia.org/wiki/MQTT) requests we need a _broker_ and some _publishers_ and _subscribers_. Everything is managed using _Mosquitto_ package (click [here](https://mosquitto.org/documentation/) for library documentation).

## Topics (interacting with the device):
1. Get user curtains current settings: ```curtains/currentUserSettings```;
2. Check if the secret door is open: ```secretDoor/isSecretDoorOpen```;
3. Check if the entrance door is open: ```automaticDoorLock/isLocked```.

### Run instructions
First we need to make sure that we have the _Mosquitto_ service is running in the background:
```shell
sudo service mosquitto stop
sudo service mosquitto start
```
Start the _broker_:
```shell
mosquitto -v
```
Open a new shell (ctrl+shift+T) and start a _broker_ at one of the given topics above:
```shell
mosquitto_sub -t curtains/currentUserSettings -C 1
```
Run the server/application from CLion and then check the terminal for the server response. As well, check the output from CLion to see the changes that have been made on the maximum temperature inside the room before opening the windows.

---

## Team members: 

* **Dumitrescu Teodor** 
* **Maftei Ioan Alexandru**
* **Predescu Eduard Alexandru**
* **Toderica Bogdan Mihai**
* **Iliescu Andrei Catalin**

---
