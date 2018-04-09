@echo off

echo Attempting to upload new firmware.

ping -n 3 127.0.0.1 > NUL

bossac.exe -u -w -v -b lasdac_mainfirmware.bin

ping -n 2 127.0.0.1 > NUL

echo Done. Please unplug and replug the DAC again. 

PAUSE