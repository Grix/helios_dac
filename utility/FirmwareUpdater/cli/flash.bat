@echo off

echo Attempting to erase firmware..

ping -n 2 127.0.0.1 > NUL

FirmwareEraser_VS2013.exe

ping -n 2 127.0.0.1 > NUL

echo Please unplug and replug the DAC from the USB port now. When done, press any key.
PAUSE
echo Attempting to upload new firmware.

ping -n 3 127.0.0.1 > NUL

bossac.exe -u -w -v -b lasdac_mainfirmware.bin

ping -n 2 127.0.0.1 > NUL

echo Done. Please unplug and replug the DAC again. 

PAUSE