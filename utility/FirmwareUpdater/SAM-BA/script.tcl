
## Flashing binaries

send_file {Flash} lasdac_mainfirmware.bin 0x400000 0

compare_file  {Flash} lasdac_mainfirmware.bin 0x400000 0

FLASH::ScriptGPNMV 2

FLASH::ScriptGPNMV 2

puts "Flash Helios Firmware done"
