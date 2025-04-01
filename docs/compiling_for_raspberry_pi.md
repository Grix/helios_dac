

Steps to compiling shared library (.so) for Linux RPi based systems
yourself:

Before : install libusb library
```shell
sudo apt-get install libusb-1.0-0-dev
```

Make sure you are in the sdk/cpp/shared_library folder in the terminal.

Compile
```shell
g++ -Wall -std=c++14 -fPIC -O2 -c HeliosDacAPI.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c ../HeliosDac.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c ../idn/idn.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c ../idn/idnServerList.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c ../idn/plt-posix.cpp
g++ -shared -o libHeliosDacAPI.so -lusb-1.0 HeliosDacAPI.o HeliosDac.o plt-posix.o idn.o idnServerList.o libusb-1.0.so
```


NB: To use the USB device on Linux you either need to run your app as sudo, or need to
set up udev rules (see https://github.com/Grix/helios_dac/blob/master/docs/udev_rules_for_linux.md )
