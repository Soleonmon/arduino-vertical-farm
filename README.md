
///Upload date 1/4/24
This is the basic vertical farm for Arduino Uno R4 Wifi

Sensors included:
1) DHT11 x2 for temperature and humidity
2) pH sensor x1
3) BH1750 x1 for light intensity
4) SGP30 x1 for CO2 sensor

***important notes:
1) DHT11 for temperature and humidity sensors should define separately, even though there were some libraries provided
   temperature and humdity code in the same .ino file, however it was not working properly in my case.
2) There is no wifi connectivity source code. The user can go to Arduino IoT hub to create an account, then setup your own wifi ssid and password.
3) The user can either use Arduino IoT hub for the wireless connection or download the file that I uploaded here for your desktop development
   Arduino IDE instead of using Arduino IoT hub, this method is more convenient.
4) By connecting to Arduino IoT hub, you can donwload the android app "Arduino IoT" for wireless control and monitor.
