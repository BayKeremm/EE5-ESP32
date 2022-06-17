# EE5-ESP32

Code for the microcontroller to communicate with the database and to manage the sensors for the smartpot project.\

run '. $HOME/esp/esp-idf/export.sh' in the directory you want to build. This will make the tools available in the directory you want to work with.\
\
Then find the port esp32 is attached to with 'ls /dev/cu.*' (for macos).\
\
then 'idf.py -p THE_PORT_NAME -b BAUD_RATE flash' command will build and flash the code to the esp32.\
\
'screen /dev/cu.PORT_NAME BAUD_RATE' command will open the output window of the esp32.\
\
BAUD_RATE = 115200.



moisture sensor:\
completely immersed in water --> 1.2V output.
Air -> 2.5V output.



![flow_chart](https://user-images.githubusercontent.com/82160210/174259056-ed6fb63c-0c60-48f1-9c7e-b34064213166.png)
