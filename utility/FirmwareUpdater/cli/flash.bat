@echo off

echo Attempting to erase firmware..

ping -n 2 127.0.0.1 > NUL

start FirmwareEraser_VS2013.exe

ping -n 2 127.0.0.1 > NUL

echo Please unplug and replug the DAC from the USB port now. When done, press any key.
PAUSE
echo Attempting to upload new firmware.

ping -n 3 127.0.0.1 > NUL

sam-ba.exe \USBserial\COM1 at91sam4s2-ek script.tcl
sam-ba.exe \USBserial\COM2 at91sam4s2-ek script.tcl
sam-ba.exe \USBserial\COM3 at91sam4s2-ek script.tcl
sam-ba.exe \USBserial\COM4 at91sam4s2-ek script.tcl
sam-ba.exe \USBserial\COM5 at91sam4s2-ek script.tcl
sam-ba.exe \USBserial\COM6 at91sam4s2-ek script.tcl
sam-ba.exe \USBserial\COM7 at91sam4s2-ek script.tcl
sam-ba.exe \USBserial\COM8 at91sam4s2-ek script.tcl
sam-ba.exe \USBserial\COM9 at91sam4s2-ek script.tcl

ping -n 2 127.0.0.1 > NUL

echo Done. Please unplug and replug the DAC again. 

PAUSE