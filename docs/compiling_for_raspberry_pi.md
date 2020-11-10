

Steps to compiling shared library (.so) for Linux RPi based systems
yourself:

Before : install libusb library
```shell
sudo apt-get install libusb-1.0-0-dev
```
and replace
libusb-1.0.so by the installed version
```shell
cp /usr/lib/arm-linux-gnueabihf/libusb-1.0.so
/home/pi/helios_dac/sdk/libusb-1.0.so
```

```shell
g++ -Wall -std=c++14 -fPIC -O2 -c HeliosDacAPI.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c HeliosDac.cpp
g++ -shared -o libHeliosDacAPI.so HeliosDacAPI.o HeliosDac.o libusb-1.0.so
```

So after compiling, copy the library file libHeliosDacAPI.so in the
python directory
```shell
cp libHeliosDacAPI.so  examples/python/libHeliosDacAPI.so
```

To use the device on Linux you either need root privileges or need to
set up udev rules (see pages.bitlasers.com/helios)

i.e. for python example :
```shell
sudo python linux_example.py
```
