

Steps to compiling shared library (.so) for Linux RPi based systems
yourself:

Before : install libusb library
```shell
sudo apt-get install libusb-1.0-0-dev
```
and replace
libusb-1.0.so by the installed version
```shell
cp /usr/lib/arm-linux-gnueabihf/libusb-1.0.so ./helios_dac/sdk/libusb-1.0.so
```
(In case of ubuntu 20.04 with RPi)
```shell
cp /usr/lib/aarch64-linux-gnu/libusb-1.0.so ./helios_dac/sdk/libusb-1.0.so

```

Compile
```shell
g++ -Wall -std=c++14 -fPIC -O2 -c HeliosDacAPI.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c HeliosDac.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c idn/idn.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c idn/idnServerList.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c idn/plt-posix.cpp
g++ -shared -o libHeliosDacAPI.so HeliosDacAPI.o HeliosDac.o plt-posix.o idn.o idnServerList.o libusb-1.0.so
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
