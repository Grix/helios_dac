# Helios DAC
> Digital to Analog Converter for laser projectors.

Open source, low cost USB DAC for the ISP-DB25 laser protocol. This repository consists of:
* Hardware (PCB schematic in KiCAD)
* Firmware
* SDK (C++ and Python)
* Extras (firmware update tool, graphics etc.)

## Compiling shared library (.so) for Linux based systems.

```shell
g++ -Wall -fPIC -O2 -c HeliosDacAPI.cpp
g++ -Wall -fPIC -O2 -c HeliosDac.cpp
g++ -shared -o libHeliosDacAPI.so HeliosDacAPI.o HeliosDac.o libusb-1.0.so
```
