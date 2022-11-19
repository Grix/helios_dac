# Helios Laser DAC
Digital to Analog Converter for laser projectors.

* https://bitlasers.com/helios-laser-dac/

Open source, low cost USB DAC for the ISP-DB25 (ILDA) laser protocol. Allows you to control an ILDA laser projector via computer over USB. Supports lots of third party software (see link above). This repository consists of:
* SDK (with examples in C++, Python and C#/.NET)
* Hardware (PCB schematic in KiCAD)
* Firmware (Atmel Studio project)
* Extras (firmware update tool, media etc.)

## Developer guide

#### Third party software integration

Navigate to the folder "sdk" to find the relevant code for interfacing with the Helios DAC in your software. The core SDK is written in C++, documented in HeliosDac.h. But libraries with exported functions that you can call from many languages such as python or C# are available, documented in HeliosDacAPI.h. You can also find examples of usage in the examples folder.

The C++ code depends on libusb. You can use the included libusb binary libraries for Win32, Mac or Linux, or you can build your own. You can find the libusb source on libusb.info, or binaries on https://sourceforge.net/projects/libusb/files/libusb-1.0/

If you wish to use the shared library, there are ready-made builds for Win32 (.dll) and 64-bit linux (.so) in the sdk folder. NB: Only the Windows binary is guaranteed to be up to date. For Mac and Linux it is recommended to build your own or use the C++ classes.

New: There is a native .NET library with example code in sdk/dotnet.

If you are adding support for the Helios in your program, let me know and I can link it on the Helios' home page.

Steps to compiling shared library (.so) for Linux based systems yourself is below. For macOS, try replacing ".so" with ".dylib". For Windows, there is a Visual Studio project in the sdk source directory.

```shell
g++ -Wall -std=c++14 -fPIC -O2 -c HeliosDacAPI.cpp
g++ -Wall -std=c++14 -fPIC -O2 -c HeliosDac.cpp
g++ -shared -o libHeliosDacAPI.so HeliosDacAPI.o HeliosDac.o libusb-1.0.so
```
To use the device on Linux you either need root privileges or need to set up udev rules (see https://bitlasers.com/helios-laser-dac/)

A more detailed guide for compiling for Raspberry Pi (Linux ARM) is also available in the docs folder.

#### Hardware and firmware modification

The PCB is drawn in Kicad. The firmware is written and built with Atmel Studio for the ATSAM4S2B microcontroller.
New firmware can be uploaded to the device over USB. To do this, you must reset the "GPNVM1" bit in the flash memory, which will make the microcontroller boot to the SAM-BA bootloader. You can do this by sending a special interrupt packet to the DAC. You can then access the flash using Atmel's SAM-BA software or BOSSA. There is an automatic tool for firmware updating:

* Download the firmware updating tool (only for Windows as of now, Mac/Linux partially done): utility/FirmwareUpdater/cli/firmwareupdater_script.zip
* Unzip, plug in the DAC and run the file "flash.bat".
* Follow the instructions on the screen (you may need to unplug and replug the device a couple of times as instructed).
